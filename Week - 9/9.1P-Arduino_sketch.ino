#include <Arduino_LSM6DS3.h>
#include <DHT.h>

#define DHTPIN 2
#define DHTTYPE DHT22
DHT dht(DHTPIN, DHTTYPE);

const int WINDOW = 15;
float ring[WINDOW];
int idx = 0, filled = 0;

unsigned long lastPrint = 0;
const unsigned long PRINT_MS = 500;

bool imu_ok = false;

void setup() {
  Serial.begin(115200);
  delay(2000);
  
  dht.begin();

  unsigned long t0 = millis();
  while (millis() - t0 < 1500) {
    if (IMU.begin()) { imu_ok = true; break; }
    delay(50);
  }

  Serial.println("ms_since_start,tempC,humidity,accel_rms");
}

void loop() {
 
  float t = dht.readTemperature();
  float h = dht.readHumidity();

  float accel_rms = 0.0f;
  if (imu_ok && IMU.accelerationAvailable()) {
    float ax, ay, az;
    IMU.readAcceleration(ax, ay, az);
    float mag = sqrt(ax*ax + ay*ay + az*az);
    float vib = fabs(mag - 1.0f);

    ring[idx] = vib;
    idx = (idx + 1) % WINDOW;
    if (filled < WINDOW) filled++;

    float sumsq = 0.0f;
    int n = (filled > 0) ? filled : 1;
    for (int i = 0; i < n; i++) sumsq += ring[i] * ring[i];
    accel_rms = sqrt(sumsq / n);           // g
  }

  unsigned long now = millis();
  if (now - lastPrint >= PRINT_MS) {
    lastPrint = now;

    if (isnan(t) || isnan(h)) { t = -99.0f; h = -1.0f; }

    Serial.print(now);         Serial.print(",");
    Serial.print(t, 1);        Serial.print(",");
    Serial.print(h, 1);        Serial.print(",");
    Serial.println(accel_rms, 4);
  }
}

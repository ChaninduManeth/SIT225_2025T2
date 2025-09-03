#include <Arduino_LSM6DS3.h>

const unsigned long SAMPLE_PERIOD_MS = 10;  // ~50 Hz

void setup() {
  Serial.begin(115200);
  while (!Serial) {;}
  if (!IMU.begin()) {
    Serial.println("ERR: IMU init failed");
    while (1) { delay(15000); }
  }
  // CSV header for sanity checks
  Serial.println("ts_ms,gx_dps,gy_dps,gz_dps");
}

void loop() {
  static unsigned long last = 0;
  unsigned long now = millis();

  if (now - last >= SAMPLE_PERIOD_MS) {
    last = now;
    float x, y, z;
    if (IMU.gyroscopeAvailable()) {
      IMU.readGyroscope(x, y, z); // units: degrees/second
      Serial.print(now);
      Serial.print(',');
      Serial.print(x, 6);
      Serial.print(',');
      Serial.print(y, 6);
      Serial.print(',');
      Serial.println(z, 6);
    }
  }
}

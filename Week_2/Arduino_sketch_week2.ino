#include <Arduino.h>
#include <DHT.h>

#define DHTPIN 2
#define DHTTYPE DHT22
DHT dht(DHTPIN, DHTTYPE);

const unsigned long SAMPLE_MS = 30*1000;

unsigned long lastSample = 0;

void setup() {
    Serial.begin(9600);
    while (!Serial) { delay(10); }

  dht.begin();

  delay(15*1000);
}

void loop() {
  unsigned long now = millis();
  if (now - lastSample >= SAMPLE_MS) {
    lastSample = now;

    float t = dht.readTemperature();
    float h = dht.readHumidity();

    if (!isnan(t) && !isnan(h)) {
      Serial.print(t, 1);
      Serial.print(",");
      Serial.println(h, 1);
    }
  }
}

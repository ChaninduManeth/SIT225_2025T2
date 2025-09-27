#include "arduino_secrets.h"
#include "thingProperties.h"
#include <Arduino_LSM6DS3.h>   // IMU library for Nano 33 IoT

void setup() {
  // ----- DO NOT put code before setup() -----
  Serial.begin(9600);
  delay(1500);

  // Cloud init
  initProperties();
  ArduinoCloud.begin(ArduinoIoTPreferredConnection);
  setDebugMessageLevel(2);
  ArduinoCloud.printDebugInfo();

  // IMU init
  if (!IMU.begin()) {
    Serial.println("ERROR: IMU not found (LSM6DS3).");
    while (1) { delay(1000); }
  }
  Serial.println("IMU ready. Starting gyroscope streaming...");
}

void loop() {
  ArduinoCloud.update();

  float gx, gy, gz;
  if (IMU.gyroscopeAvailable()) {
    IMU.readGyroscope(gx, gy, gz);   // deg/s
    // These variables must exist in your Thing (float, READ ONLY)
    gyroX = gx;
    gyroY = gy;
    gyroZ = gz;

    Serial.print("gx: "); Serial.print(gx, 2);
    Serial.print("  gy: "); Serial.print(gy, 2);
    Serial.print("  gz: "); Serial.println(gz, 2);
  }

  delay(100); // ~10 Hz
}

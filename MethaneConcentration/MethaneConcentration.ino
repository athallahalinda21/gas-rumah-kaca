#include <Arduino.h>
#include <Wire.h>
#define TGS2600 A0 // Analog pin for TGS2600 sensor
int sensorValue; // Variable to store the sensor value

void setup() {
  Wire.begin();
  Serial.begin(9600);
}

void loop() {
  float Vc = 5.0;  // input voltage to the sensor circuit
  float Rl = 1000.0;  // load resistance
  float Vout = analogRead(A0);  // read analog voltage from sensor
  float Rs = (Vc * Rl / Vout) - Rl;  // calculate sensor resistance in air

  float R0 = Rs / (0.4 * 0.95 * 10);  // calculate R0 with assumptions of F_gas=0.4, H=0.05, and C_gas=10

  float mV = (Vout / 1023.0) * 5000;  // convert analog voltage to mV
  float mC1 = (mV * 30) / 1024.0;  // convert mV to concentration in ppm

  float methane_ppm = mC1 * (Rs / R0);  // calculate methane concentration in ppm based on sensor resistance in air and R0

  Serial.print("Methane concentration (ppm): ");
  Serial.println(methane_ppm);
  delay(10000); // Wait for 1 second

}

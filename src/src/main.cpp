#include <Arduino.h>
#include "ButtonManager.h"

#include "TemperatureManager.h"
#include "MenuManager.h"

#include "Pins.h"
#include "Setpoints.h"

Setpoints setpoints;

TemperatureManager tm(ONE_WIRE_BUS);
MenuManager mm(tm, setpoints);

unsigned long lastBlinkTime = 0;
bool ledState = false;

void setup() {
  pinMode(STATUS_LED, OUTPUT);
  Serial.begin(115200);

  tm.findSensors();
}

void loop() {
  tm.update();
  mm.update();

  // if (millis() - lastBlinkTime >= 5000)
  // {
  //   lastBlinkTime = millis();
  //   ledState = !ledState;
  //   digitalWrite(STATUS_LED, HIGH);

  //   Serial.println("Temperatures:");
  //   for (int i = 0; i < tempManager.getSensorCount(); i++) {
  //     Serial.print("Sensor ");
  //     Serial.print(i);
  //     Serial.print(": ");
  //     Serial.print(tempManager.getTemperature(i));
  //     Serial.println(" °C");
  //   } 
  // }

  delay(5);
}

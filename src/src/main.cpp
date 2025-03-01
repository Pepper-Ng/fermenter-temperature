#include <Arduino.h>

#include "ButtonManager.h"
#include "MenuManager.h"
#include "RelayController.h"
#include "StatusController.h"
#include "TemperatureManager.h"

#include "Pins.h"
#include "Setpoints.h"

Setpoints setpoints;

StatusController sc;

TemperatureManager tm(ONE_WIRE_BUS, sc);
MenuManager mm(tm, setpoints);
RelayController rc(tm, sc, setpoints);

unsigned long lastBlinkTime = 0;
bool ledState = false;

void setup() {
  pinMode(STATUS_LED, OUTPUT);
  Serial.begin(115200);

  // TODO setup wifi.
  sc.setState(StatusController::NORMAL_WIFI_NOT_CONFIGURED);

  tm.findSensors();
}

void loop() {
  tm.update();
  sc.update();
  mm.update();
  rc.update();

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

#include <Arduino.h>

#include "ButtonManager.h"
#include "MenuManager.h"
#include "RelayController.h"
#include "StatusController.h"
#include "TemperatureManager.h"

#include "Pins.h"
#include "Configurations.h"

Configurations configurations;

StatusController sc;

TemperatureManager tm(ONE_WIRE_BUS, sc);
MenuManager mm(tm, configurations);
RelayController rc(tm, sc, configurations);

unsigned long lastBlinkTime = 0;
bool ledState = false;

void setup() {
  pinMode(STATUS_LED, OUTPUT);
  Serial.begin(115200);

  // TODO setup wifi.
  sc.setState(StatusController::NORMAL_WIFI_NOT_CONFIGURED);
  delay(50);

  tm.findSensors();
  tm.setTemperatureUnit(configurations.temperatureUnit);
}

void loop() {
  // Update all components.
  tm.update();
  sc.update();
  mm.update();
  rc.update();

  delay(5);
}

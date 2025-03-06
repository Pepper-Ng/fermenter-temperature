#include <Arduino.h>

#include "ButtonManager.h"
#include "MenuManager.h"
#include "RelayController.h"
#include "StatusController.h"
#include "TemperatureManager.h"

#include "Pins.h"
#include "Configurations.h"

#include <WiFiManager.h>

Configurations configurations;

StatusController sc;

TemperatureManager tm(ONE_WIRE_BUS, sc);
MenuManager mm(tm, configurations);
RelayController rc(tm, sc, configurations);

unsigned long lastBlinkTime = 0;
bool ledState = false;
bool wifiState = false;

WiFiManager wm;

void setup() {
  pinMode(STATUS_LED, OUTPUT);
  Serial.begin(115200);

  Serial.println("Starting WiFiManager...");
  wm.setConfigPortalBlocking(false);
  wm.setConfigPortalTimeout(120);
  if(wm.autoConnect("TempController-Setup"))
  {
    Serial.println("Wifi connected.");
    sc.setState(StatusController::NORMAL_WIFI_CONNECTED);
    wifiState = true;
  }
  else
  {
    Serial.println("Configportal running.");
    sc.setState(StatusController::NORMAL_WIFI_NOT_CONFIGURED);
  }

  if (!configurations.begin())
    Serial.println("Failed to load config, using defaults.");
  else
    Serial.println("Config loaded.");

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

  wm.process();

  if (WiFi.status() == WL_CONNECTED && !wifiState) {
    wifiState = true;
    sc.setState(StatusController::NORMAL_WIFI_CONNECTED);
    Serial.println("WiFi connected!");
  }

  delay(5);
}

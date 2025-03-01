#include "RelayController.h"
#include "Pins.h"
#include "Configurations.h"

RelayController::RelayController(TemperatureManager& tm, StatusController& sc, Configurations& cfg)
  : tempManager(tm)
  , statusController(sc)
  , cfg(cfg)
{
  pinMode(RELAY_1, OUTPUT);
  pinMode(RELAY_2, OUTPUT);
  digitalWrite(RELAY_1, LOW);
  digitalWrite(RELAY_2, LOW);
}

void RelayController::update() {
  controlRelays();
}

void RelayController::controlRelays() {
  float currentTemp = tempManager.getTemperature(0);

  // Heating control.
  if (currentTemp < cfg.temperatureSetpoint - cfg.heatingDifferential)
    heatingOn = true;
  else if (currentTemp >= cfg.temperatureSetpoint)
    heatingOn = false;
   
  // Cooling control with compressor delay.
  if (currentTemp > cfg.temperatureSetpoint + cfg.coolingDifferential)
  {
    unsigned long now = millis();
    if (!coolingOn)
    {
      if (lastCoolingOffTime != 0 && now - lastCoolingOffTime >= cfg.compressorDelay * 60000)
        coolingOn = true;
    }
  }
  else if (currentTemp <= cfg.temperatureSetpoint)
  {
    coolingOn = false;
    lastCoolingOffTime = millis();
  }

  // Make sure heating and cooling can never be on at the same time.
  if (heatingOn && coolingOn )
  {
    statusController.setState(StatusController::CRITICAL_FAILURE);
  }
  else if (!statusController.inError())
  {
    // Apply relay states.
    digitalWrite(RELAY_1, heatingOn ? HIGH : LOW);
    digitalWrite(RELAY_2, coolingOn ? HIGH : LOW);
  }
}

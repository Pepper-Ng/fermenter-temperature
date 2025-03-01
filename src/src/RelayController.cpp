#include "RelayController.h"
#include "Pins.h"
#include "Setpoints.h"

RelayController::RelayController(TemperatureManager& tm, StatusController& sc, Setpoints& sp) 
  : tempManager(tm)
  , statusController(sc)
  , setpoints(sp)
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
  if (currentTemp < setpoints.temperatureSetpoint - setpoints.heatingDifferential)
    heatingOn = true;
  else if (currentTemp >= setpoints.temperatureSetpoint)
    heatingOn = false;
   
  // Cooling control with compressor delay.
  if (currentTemp > setpoints.temperatureSetpoint + setpoints.coolingDifferential)
  {
    unsigned long now = millis();
    if (!coolingOn && (now - lastCoolingOffTime >= setpoints.compressorDelay * 60000))
      coolingOn = true;
  }
  else if (currentTemp <= setpoints.temperatureSetpoint)
  {
    coolingOn = false;
    lastCoolingOffTime = millis();
  }

  // Make sure heating and cooling can never be on at the same time.
  if (heatingOn && coolingOn)
  {
    statusController.setState(StatusController::CRITICAL_FAILURE);
  }
  else
  {
    // Apply relay states.
    digitalWrite(RELAY_1, heatingOn ? HIGH : LOW);
    digitalWrite(RELAY_2, coolingOn ? HIGH : LOW);
  }
}

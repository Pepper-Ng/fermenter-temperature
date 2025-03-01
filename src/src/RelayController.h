#ifndef RELAY_CONTROLLER_H
#define RELAY_CONTROLLER_H

#include "Setpoints.h"
#include "TemperatureManager.h"
#include "StatusController.h"
#include "Pins.h"
#include <Arduino.h>

class RelayController {
public:
  RelayController(TemperatureManager& tm, StatusController& sc, Setpoints& sp);
  void update(); // Call this regularly in loop()
    
private:
  TemperatureManager& tempManager;
  StatusController& statusController;
  Setpoints& setpoints;

  unsigned long lastCoolingOffTime = 0; // Track compressor delay
  bool heatingOn = false;
  bool coolingOn = false;
  
  void controlRelays();
};

#endif

#ifndef RELAY_CONTROLLER_H
#define RELAY_CONTROLLER_H

#include "Configurations.h"
#include "TemperatureManager.h"
#include "StatusController.h"
#include "Pins.h"
#include <Arduino.h>

class RelayController {
public:
  RelayController(TemperatureManager& tm, StatusController& sc, Configurations& cfg);
  void update(); // Call this regularly in loop()
    
private:
  TemperatureManager& tempManager;
  StatusController& statusController;
  Configurations& cfg;

  unsigned long lastCoolingOffTime = 0; // Track compressor delay
  bool heatingOn = false;
  bool coolingOn = false;
  
  void controlRelays();
};

#endif

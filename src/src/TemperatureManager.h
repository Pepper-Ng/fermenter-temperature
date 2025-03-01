#ifndef TEMPERATURE_MANAGER_H
#define TEMPERATURE_MANAGER_H

#include <Arduino.h>
#include <OneWire.h>
#include <DallasTemperature.h>

#include "StatusController.h"

class TemperatureManager {
public:
  TemperatureManager(uint8_t oneWirePin, StatusController& sc);
  void findSensors();
  int getSensorCount();
  void update();

  float getTemperature(uint8_t index);
  char getTemperatureUnit();
  void setTemperatureUnit(char unit);
  String getAddress(uint8_t index);
    
private:
  static const int MAX_SENSORS = 4;

  OneWire oneWire;
  DallasTemperature sensors;
  DeviceAddress deviceAddresses[MAX_SENSORS];
  uint8_t sensorResolution = 11; // 11-bit sensor resolution.

  StatusController& statusController;

  int deviceCount = 0;
  unsigned long lastReadTime = 0;
  const unsigned long readInterval = 1000;

  char temperatureUnit;
};

#endif
#include "TemperatureManager.h"

TemperatureManager::TemperatureManager(uint8_t oneWirePin) 
  : oneWire(oneWirePin)
  , sensors(&oneWire)
{}

void TemperatureManager::findSensors()
{
  sensors.begin();
  Serial.println("Scanning for OneWire devices...");
  
  oneWire.reset_search();
  deviceCount = 0;
  while (deviceCount < MAX_SENSORS && oneWire.search(deviceAddresses[deviceCount])) {
    sensors.setResolution(deviceAddresses[deviceCount], sensorResolution, true);
    deviceCount++;
    Serial.println("Found Device " + String(deviceCount) + ": " + getAddress(deviceCount-1));
  }

  sensors.setWaitForConversion(false);

  if (deviceCount == 0) 
    Serial.println("No sensors found!");
}

void TemperatureManager::update()
{
  if (millis() - lastReadTime >= readInterval && sensors.isConversionComplete()) {
    lastReadTime = millis();
    sensors.requestTemperatures();
  }
}

float TemperatureManager::getTemperature(uint8_t index)
{
  if (index >= deviceCount) return DEVICE_DISCONNECTED_C;
  if (temperatureUnit == 'F')
    return sensors.getTempF(deviceAddresses[index]);
  else
    return sensors.getTempC(deviceAddresses[index]);
}

char TemperatureManager::getTemperatureUnit()
{
  return temperatureUnit;
}

void TemperatureManager::setTemperatureUnit(char unit)
{
  temperatureUnit = unit;
}

int TemperatureManager::getSensorCount()
{
  return deviceCount;
}

String TemperatureManager::getAddress(uint8_t index)
{
  if (index < 0 || index >= deviceCount) return "Invalid Index";

  String addressStr = "";
  for (uint8_t i = 0; i < 8; i++) {
      if (deviceAddresses[index][i] < 16) addressStr += "0"; // Add leading zero if needed
      addressStr += String(deviceAddresses[index][i], HEX);
      if (i < 7) addressStr += ":"; // Separate bytes with ':'
  }
  return addressStr;
}
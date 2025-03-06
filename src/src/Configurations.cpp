#include "Configurations.h"

Configurations::Configurations() {}

bool Configurations::begin() {
    if (!LittleFS.begin()) {
        Serial.println("LittleFS mount failed!");
        return false;
    }
    return load();
}

bool Configurations::load() {
  if (!LittleFS.exists("/config.json")) return false;
  File file = LittleFS.open("/config.json", "r");
  if (!file) return false;

  JsonDocument doc;  // Correct usage, no size needed
  DeserializationError error = deserializeJson(doc, file);
  if (error) return false;

  temperatureSetpoint = doc["temperatureSetpoint"] | 20.0;
  heatingDifferential = doc["heatingDifferential"] | 2.0;
  coolingDifferential = doc["coolingDifferential"] | 2.0;
  compressorDelay = doc["compressorDelay"] | 1.0;
  calibration = doc["calibration"] | 0.0;

  // Fix: Convert to String first
  String tempUnit = doc["temperatureUnit"] | "C";  
  temperatureUnit = tempUnit[0];  // Take first character

  return true;
}

bool Configurations::save() {
  File file = LittleFS.open("/config.json", "w");
  if (!file) return false;

  JsonDocument doc;
  doc["temperatureSetpoint"] = temperatureSetpoint;
  doc["heatingDifferential"] = heatingDifferential;
  doc["coolingDifferential"] = coolingDifferential;
  doc["compressorDelay"] = compressorDelay;
  doc["calibration"] = calibration;
  
  // Fix: Store as a String
  doc["temperatureUnit"] = String(temperatureUnit);  

  return serializeJson(doc, file) > 0;
}
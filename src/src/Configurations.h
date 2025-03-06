#ifndef CONFIGURATIONS_H
#define CONFIGURATIONS_H

#include <LittleFS.h>
#include <ArduinoJson.h>

class Configurations {
public:
    float temperatureSetpoint = 20.0;
    float heatingDifferential = 2.0;
    float coolingDifferential = 2.0;
    float compressorDelay = 1.0;
    float calibration = 0.0;
    char temperatureUnit = 'C';

    Configurations(); // Constructor
    bool begin();     // Initialize storage and load config
    bool load();      // Load from storage
    bool save();      // Save to storage
};

#endif
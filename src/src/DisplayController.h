#ifndef DISPLAY_CONTROLLER_H
#define DISPLAY_CONTROLLER_H

#include <Arduino.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_LEDBackpack.h>

class DisplayController {
public:
  DisplayController(uint8_t sda, uint8_t scl);

  void showText(const char* text);
  void showTemperature(float temp, char unit='C');

private:
    uint8_t _sda, _scl;  // Store SDA and SCL pin values
    Adafruit_AlphaNum4 display;  // Object for the 14-segment display
};

#endif

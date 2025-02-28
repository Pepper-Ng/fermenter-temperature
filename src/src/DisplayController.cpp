#include "DisplayController.h"

DisplayController::DisplayController(uint8_t sda, uint8_t scl) : _sda(sda), _scl(scl)
{
  Wire.begin(_sda, _scl);

  // Initialize the 14-segment display (address 0x70 by default)
  if (!display.begin(0x70)) {
      Serial.println("Couldn't find the 14-segment display.");
      return;
  }
  display.clear();
  display.writeDisplay();
}

void DisplayController::showText(const char* text) {
  display.clear();
  
  int digit = 0;
  for (int i = 0; text[i] != '\0' && digit < 4; i++) {  
      bool hasDot = (text[i] != '.' && text[i + 1] == '.');  

      display.writeDigitAscii(digit++, text[i], hasDot);

      // If we processed a dot, skip it in the loop.
      if (hasDot) i++;  
  }

  display.setBrightness(2);
  display.writeDisplay();
}

void DisplayController::showTemperature(float temp, char unit) {
  char buffer[6];  // "-9.9C" or "99.9C" + null terminator

  if (temp < -9.9) temp = -9.9;  // Prevent going below -9.9°C
  if (temp > 99.9) temp = 99.9;  // Prevent going above 99.9°C

  snprintf(buffer, sizeof(buffer), "%.1f%c", temp, unit);
  showText(buffer);
}
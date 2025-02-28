#ifndef BUTTON_MANAGER_H
#define BUTTON_MANAGER_H

#include "Button.h"

#include <Arduino.h>
#include <vector>
#include <functional>

class ButtonManager {
public:
  static ButtonManager& getInstance();

  Button* getButton(uint8_t pin);
  std::vector<Button*>& getButtons();

  Button* button(uint8_t pin, bool activeLow);

  void update();

private:
  std::vector<Button*> buttons;

  ButtonManager();
  ~ButtonManager();
  ButtonManager(const ButtonManager&) = delete;
  ButtonManager& operator=(const ButtonManager&) = delete;
};

#endif

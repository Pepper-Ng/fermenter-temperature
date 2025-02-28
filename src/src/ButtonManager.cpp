#include "ButtonManager.h"

#define DEBOUNCE_TIME 10
#define LONG_PRESS_TIME 1000  // 1 second

// Singleton instance retrieval.
ButtonManager& ButtonManager::getInstance() {
  static ButtonManager instance;  // Static ensures it’s created only once
  return instance;
}

// Private constructor to prevent multiple instances
ButtonManager::ButtonManager() {}

ButtonManager::~ButtonManager() {
  for (auto button: getButtons())
  {
    button->reset();
    delete button;
  }
}

Button* ButtonManager::button(uint8_t pin, bool activeLow)
{
  auto button = getButton(pin);
  if (button != nullptr)
    return button;

  auto newButton = new Button(pin, activeLow, false);
  buttons.push_back(newButton);
  return newButton;
}

std::vector<Button*>& ButtonManager::getButtons()
{
  return this->buttons;
}

// Find a button by pin. Returns nullptr if not found.
Button* ButtonManager::getButton(uint8_t pin)
{
  for (auto button : buttons)
  {
    if (button->pin() == pin)
    return button;
  }
  return nullptr;
}

void ButtonManager::update()
{
  for (auto button : buttons)
    button->tick();
}
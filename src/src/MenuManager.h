#ifndef MENU_MANAGER_H
#define MENU_MANAGER_H

#include <map>
#include <vector>
#include <functional>
#include <string>

#include "ButtonManager.h"
#include "DisplayController.h"
#include "SetPoints.h"
#include "TemperatureManager.h"

// Menu
#include "menu/MenuNode.h"

class MenuManager {
public:
  MenuManager(TemperatureManager& temperatureManager, Setpoints& setpoints);
  ~MenuManager();

  void update();

  void transitionTo(MenuNode* newNode);

  float getTemperature();

  void toggleCF();

private:
  DisplayController dc;
  ButtonManager& bm;
  TemperatureManager& tm;

  Setpoints& setpoints;

  MenuNode* currentNode;
  //std::vector<MenuNode*> nodes;
};

#endif // MENU_MANAGER_H

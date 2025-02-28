#ifndef TEMPERATURE_NODE_H
#define TEMPERATURE_NODE_H

#include "MenuNode.h"
#include "../DisplayController.h"
#include "../TemperatureManager.h"

class TemperatureNode : public MenuNode {
public:
  TemperatureNode(std::string name, MenuNode* parent, ButtonManager& bm, TemperatureManager& tm, MenuManager& mm);
  void display(DisplayController& dc) override;
  void select() override;
  void cancel() override;
private:
  TemperatureManager& tm;
};

#endif
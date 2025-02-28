#ifndef CF_NODE_H
#define CF_NODE_H

#include "MenuNode.h"
#include "../DisplayController.h"
#include "../TemperatureManager.h"

class CFNode : public MenuNode {
public:
  CFNode(std::string name, MenuNode* parent, ButtonManager& bm, TemperatureManager& tm, MenuManager& mm);
  void display(DisplayController& dc) override;
  void prev() override;
  void next() override;
  void select() override;
  void cancel() override;
private:
  TemperatureManager& tm;
};

#endif
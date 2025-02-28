#ifndef VALUESET_NODE_H
#define VALUESET_NODE_H

#include "MenuNode.h"
#include "../DisplayController.h"

struct ValueConfig {
  float minValue;
  float maxValue;
  float step;
  char unit;
  float* value;
};

class ValueSetNode : public MenuNode {
public:
  ValueSetNode(std::string name, MenuNode* parent, ValueConfig vc, ButtonManager& bm, MenuManager& mm);
  void display(DisplayController& dc) override;
  void prev() override;
  void next() override;
  void select() override;
  void cancel() override;
private:
  ValueConfig config;
};

#endif
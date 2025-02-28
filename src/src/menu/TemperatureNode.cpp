#include "TemperatureNode.h"

#include "../DisplayController.h"
#include "../MenuManager.h"

TemperatureNode::TemperatureNode(std::string name, MenuNode* parent, ButtonManager& bm, TemperatureManager& tm, MenuManager& mm)
  : MenuNode(name, parent, bm, mm)
  , tm(tm)
{}

void TemperatureNode::display(DisplayController& dc)
{
  float temp = tm.getTemperature(0);
  dc.showTemperature(temp, tm.getTemperatureUnit());
}

void TemperatureNode::cancel()
{
  if (!children.empty())
    mm.transitionTo(children[selectedChild]);
}

void TemperatureNode::select()
{
  return;
}

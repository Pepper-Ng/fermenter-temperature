#include "ValueSetNode.h"

#include <iomanip>
#include <sstream>

#include "../DisplayController.h"
#include "../MenuManager.h"

ValueSetNode::ValueSetNode(std::string name, MenuNode* parent, ValueConfig vc, ButtonManager& bm, MenuManager& mm)
  : MenuNode(name, parent, bm, mm)
  , config(vc)
{
}

void ValueSetNode::display(DisplayController& dc)
{
  float value = *config.value;
  if (tolower(config.unit) == 'c' || tolower(config.unit) == 'f')
  {
    dc.showTemperature(value, config.unit);
  }
  else
  {
    std::ostringstream stream;
    stream << std::fixed << std::setprecision(1) << value << config.unit;
    std::string text = stream.str();

    if (text.length() > 5)
      text = text.substr(0, 5);

    dc.showText(text.c_str());
  }
}

void ValueSetNode::prev()
{
  if (*config.value - config.step >= config.minValue)
    *config.value -= config.step;
  else
    *config.value = config.minValue;
}

void ValueSetNode::next()
{
  if (*config.value + config.step <= config.maxValue)
    *config.value += config.step;
  else
    *config.value = config.maxValue;
}

void ValueSetNode::cancel()
{
  if (parent != nullptr)
    mm.transitionTo(parent);
}

void ValueSetNode::select()
{
  if (parent != nullptr)
    mm.transitionTo(parent);
}

#include "CFNode.h"

#include <iomanip>
#include <sstream>

#include "../DisplayController.h"
#include "../MenuManager.h"

CFNode::CFNode(std::string name, MenuNode* parent, ButtonManager& bm, TemperatureManager& tm, MenuManager& mm)
  : MenuNode(name, parent, bm, mm)
  , tm(tm)
{
}

void CFNode::display(DisplayController& dc)
{
  if (tm.getTemperatureUnit() == 'F')
  {
    char temperatureUnitStr[6] = "--.-F";
    dc.showText(temperatureUnitStr);
  }
  else
  {
    char temperatureUnitStr[6] = "--.-C";
    dc.showText(temperatureUnitStr);
  }
}

void CFNode::prev()
{
  if (tm.getTemperatureUnit() == 'F')
    tm.setTemperatureUnit('C');
  else
    tm.setTemperatureUnit('F');
}

void CFNode::next()
{
  if (tm.getTemperatureUnit() == 'F')
    tm.setTemperatureUnit('C');
  else
    tm.setTemperatureUnit('F');
}

void CFNode::cancel()
{
  if (parent != nullptr)
    mm.transitionTo(parent);
}

void CFNode::select()
{
  if (parent != nullptr)
    mm.transitionTo(parent);
}

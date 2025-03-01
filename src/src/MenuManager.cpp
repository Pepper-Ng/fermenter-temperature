#include "MenuManager.h"
#include "Pins.h"

#include "menu/TemperatureNode.h"
#include "menu/ValueSetNode.h"
#include "menu/CFNode.h"

// Constructor initializes menu structure
MenuManager::MenuManager(TemperatureManager& temperatureManager, Configurations& configurations)
  : dc(I2C_SDA, I2C_SCL)
  , bm(ButtonManager::getInstance())
  , tm(temperatureManager)
  , cfg(configurations)
{
  Serial.println("Menu initializing...");

  // Create a root node.
  MenuNode* rootNode = new TemperatureNode("ROOT", nullptr, bm, tm, *this);
  MenuNode* menuNode = new MenuNode("MENU", rootNode, bm, *this);
  rootNode->addChild(menuNode);

  // TODO Future : Setpoints are all in celcius.
  // Setpoints should be updated to be possible in celcius as well as fahrenheit.
  menuNode->addChild(new ValueSetNode("TS", menuNode, { -50, 120, 0.2, 'C', &cfg.temperatureSetpoint }, bm, *this));
  menuNode->addChild(new ValueSetNode("HD", menuNode, { 0.3, 15, 0.1, 'C', &cfg.heatingDifferential }, bm, *this));
  menuNode->addChild(new ValueSetNode("CD", menuNode, { 0.3, 15, 0.1, 'C', &cfg.coolingDifferential }, bm, *this));
  menuNode->addChild(new ValueSetNode("PT", menuNode, { 0, 10, 0.1, 'm', &cfg.compressorDelay }, bm, *this));
  menuNode->addChild(new ValueSetNode("CAL", menuNode, { -15, 15, 0.1, 'C', &cfg.calibration }, bm, *this));
  menuNode->addChild(new CFNode("CF", menuNode, bm, tm, *this));

  currentNode = rootNode;
  currentNode->enter();

  Serial.println("Menu initialized.");
}

MenuManager::~MenuManager()
{
}

void MenuManager::update()
{
  bm.update();
  currentNode->display(dc);
}

void MenuManager::transitionTo(MenuNode* node)
{
  Serial.println("Setpoints:");
  Serial.print("TS: ");
  Serial.println(cfg.temperatureSetpoint);
  Serial.print("HD: ");
  Serial.println(cfg.heatingDifferential);
  Serial.print("CD: ");
  Serial.println(cfg.coolingDifferential);
  Serial.print("PT: ");
  Serial.println(cfg.compressorDelay);
  Serial.println();
  Serial.print("Transition ");
  Serial.print(currentNode->getName().c_str());
  Serial.print("->");
  Serial.println(node->getName().c_str());

  if (!node || node == currentNode) return;
  if (currentNode) currentNode->exit();
  currentNode = node;
  currentNode->enter();
  currentNode->display(dc);
}

float MenuManager::getTemperature()
{
  // TODO: Might implement getting temperature from a different sensor?
  // Might configure that through the menu?
  return tm.getTemperature(0);
}

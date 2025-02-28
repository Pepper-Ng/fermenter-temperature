#ifndef MENU_NODE_H
#define MENU_NODE_H

#include <vector>
#include <functional>
#include <string>

#include "../ButtonManager.h"
#include "../DisplayController.h"

// Forward declaration of the menu manager to prevent circular dependencies.
class MenuManager;

class MenuNode {
public:
  using TransitionCallback = std::function<void(MenuNode*)>;

  MenuNode(std::string name, MenuNode* parent, ButtonManager& buttonManager, MenuManager& menuManager)
  : name(name)
  , parent(parent)
  , selectedChild(0)
  , bm(buttonManager)
  , mm(menuManager)
  {}

  // Called when state becomes active: Upon entering state.
  // Should register any event handlers it may need.
  virtual void enter();

  // Called when state becomes inactive: Upon transitioning to different state.
  // Should unregister anything registered in enter.
  virtual void exit();

  virtual void prev();
  virtual void next();
  virtual void select();
  virtual void cancel();

  // Display function. Called by MenuManager to ask the state to update the display.
  virtual void display(DisplayController& dc);

  void addChild(MenuNode* child) {
    children.push_back(child);
  }

  std::string getName() { return name; }

protected:
  std::string name;
  MenuNode* parent;
  std::vector<MenuNode*> children;

  int selectedChild;

  ButtonManager& bm;
  MenuManager& mm;
};

#endif

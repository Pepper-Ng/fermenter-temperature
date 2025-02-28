#include "MenuNode.h"
#include "../Pins.h"
#include "../MenuManager.h"

void MenuNode::enter()
{
  Serial.print("enter ");
  Serial.println(name.c_str());
  bm.button(BUTTON_1, true)->attachClick([](void *mn) { ((MenuNode *) mn)->prev();}, this);
  bm.button(BUTTON_2, false)->attachClick([](void *mn) { ((MenuNode *) mn)->next();}, this);
  bm.button(BUTTON_OK, true)->attachClick([](void *mn) { ((MenuNode *) mn)->select();}, this);
  bm.button(BUTTON_OK, true)->attachLongPressStart([](void *mn) { ((MenuNode *) mn)->cancel();}, this);
}

void MenuNode::exit()
{
  Serial.print("exit ");
  Serial.println(name.c_str());
  bm.button(BUTTON_1, true)->attachClick([](void *mn) { ((MenuNode *) mn)->prev();}, this);
  bm.button(BUTTON_2, false)->attachClick([](void *mn) { ((MenuNode *) mn)->next();}, this);
  bm.button(BUTTON_OK, true)->attachClick([](void *mn) { ((MenuNode *) mn)->select();}, this);
  bm.button(BUTTON_OK, true)->attachLongPressStart([](void *mn) { ((MenuNode *) mn)->cancel();}, this);
}

void MenuNode::next() {
  Serial.println("next");
  if (!children.empty()) {
    selectedChild = (selectedChild + 1 + children.size()) % children.size();
  }
}

void MenuNode::prev() {
  Serial.println("prev");
  if (!children.empty()) {
    selectedChild = (selectedChild - 1 + children.size()) % children.size();
  }
}

void MenuNode::select() {
  Serial.println("select");
  if (!children.empty())
    mm.transitionTo(children[selectedChild]);
}

void MenuNode::cancel() {
  Serial.println("cancel");
  if (parent != nullptr)
    mm.transitionTo(parent);
  else
    select();
}

void MenuNode::display(DisplayController& dc)
{
  if (!children.empty() && static_cast<unsigned int>(selectedChild) < children.size())
    dc.showText(children.at(selectedChild)->getName().c_str());
  else
    dc.showText(name.c_str());
}
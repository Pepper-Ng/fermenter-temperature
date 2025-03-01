#ifndef STATUSCONTROLLER_H
#define STATUSCONTROLLER_H

#include <Arduino.h>

class StatusController {
public:
  enum State {
    NORMAL_WIFI_CONNECTED,
    NORMAL_WIFI_NOT_CONFIGURED,
    WIFI_ERROR,
    SENSOR_ERROR,
    RELAY_ERROR,
    CRITICAL_FAILURE
  };

  StatusController();
    
  void setState(State state);
  State getState();
  void update();

  bool inError();

private:
  State currentState;
  unsigned long lastBlinkTime;
  bool blinkState;
  int blinkCount;

  void resetBlinking();
  void blinkPattern(unsigned long now, int blinkDuration, int cycleDuration, int numBlinks);
};

#endif

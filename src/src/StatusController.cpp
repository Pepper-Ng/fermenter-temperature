#include "StatusController.h"
#include "Pins.h"

StatusController::StatusController()
  : currentState(NORMAL_WIFI_CONNECTED)
  , lastBlinkTime(0)
  , blinkState(false)
  , blinkCount(0)
{
  pinMode(STATUS_LED, OUTPUT);
  update();
}

void StatusController::setState(State state) {
  if (state > currentState) {
    currentState = state;
    resetBlinking();
  }
}

StatusController::State StatusController::getState() {
  return currentState;
}

void StatusController::update() {
  unsigned long now = millis();

  switch (currentState) {
    case NORMAL_WIFI_CONNECTED:
      digitalWrite(STATUS_LED, HIGH);
      break;
    case NORMAL_WIFI_NOT_CONFIGURED:
      blinkPattern(now, 200, 2000, 1);
      break;
    case WIFI_ERROR:
      blinkPattern(now, 200, 2000, 2);
      break;
    case SENSOR_ERROR:
      blinkPattern(now, 200, 2000, 3);
      break;
    case RELAY_ERROR:
      blinkPattern(now, 100, 200, -1);
      break;
    case CRITICAL_FAILURE:
      digitalWrite(STATUS_LED, LOW);
      break;
  }
}

void StatusController::resetBlinking() {
  lastBlinkTime = millis();
  blinkState = false;
  blinkCount = 0;
}

void StatusController::blinkPattern(unsigned long now, int blinkDuration, int cycleDuration, int numBlinks) {
  if (numBlinks == -1 || blinkCount < numBlinks * 2) {
    if (now - lastBlinkTime >= (unsigned long)blinkDuration) {
      lastBlinkTime = now;
      blinkState = !blinkState;
      digitalWrite(STATUS_LED, blinkState ? HIGH : LOW);
      if (!blinkState) blinkCount++;
    }
  } else if (now - lastBlinkTime >= (unsigned long)cycleDuration) {
    resetBlinking();
  }
}

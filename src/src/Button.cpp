 #include "Button.h"

 // ----- Initialization and Default Values -----
 
 /**
  * @brief Construct a new Button object but not (yet) initialize the IO pin.
  */
 Button::Button() {
   _pin = -1;
   // further initialization has moved to Button.h
 }
 
 // Initialize the Button library.
 Button::Button(const uint8_t pin, const bool activeLow, const bool pullupActive) {
   setup(pin, pullupActive ? INPUT_PULLUP : INPUT, activeLow);
 }  // Button
 
 
 // initialize or re-initialize the input pin
 void Button::setup(const uint8_t pin, const uint8_t mode, const bool activeLow) {
   _pin = pin;
 
   if (activeLow) {
     // the button connects the input pin to GND when pressed.
     _buttonPressed = LOW;
 
   } else {
     // the button connects the input pin to VCC when pressed.
     _buttonPressed = HIGH;
   }
 
   pinMode(pin, mode);
 }
 
 
 // explicitly set the number of millisec that have to pass by before a click is assumed stable.
 void Button::setDebounceMs(const int ms) {
   _debounce_ms = ms;
 }  // setDebounceMs
 
 
 // explicitly set the number of millisec that have to pass by before a click is detected.
 void Button::setClickMs(const unsigned int ms) {
   _click_ms = ms;
 }  // setClickMs
 
 
 // explicitly set the number of millisec that have to pass by before a long button press is detected.
 void Button::setPressMs(const unsigned int ms) {
   _press_ms = ms;
 }  // setPressMs
 
 // explicitly set the number of millisec that have to pass by before button idle is detected.
 void Button::setIdleMs(const unsigned int ms) {
   _idle_ms = ms;
 }  // setIdleMs
 
 // save function for click event
 void Button::attachPress(callbackFunction newFunction) {
   _pressFunc = newFunction;
 }  // attachPress
 
 
 // save function for parameterized click event
 void Button::attachPress(parameterizedCallbackFunction newFunction, void *parameter) {
   _paramPressFunc = newFunction;
   _pressFuncParam = parameter;
 }  // attachPress
 
 // save function for click event
 void Button::attachClick(callbackFunction newFunction) {
   _clickFunc = newFunction;
 }  // attachClick
 
 
 // save function for parameterized click event
 void Button::attachClick(parameterizedCallbackFunction newFunction, void *parameter) {
   _paramClickFunc = newFunction;
   _clickFuncParam = parameter;
 }  // attachClick
 
 
 // save function for doubleClick event
 void Button::attachDoubleClick(callbackFunction newFunction) {
   _doubleClickFunc = newFunction;
   _maxClicks = max(_maxClicks, 2);
 }  // attachDoubleClick
 
 
 // save function for parameterized doubleClick event
 void Button::attachDoubleClick(parameterizedCallbackFunction newFunction, void *parameter) {
   _paramDoubleClickFunc = newFunction;
   _doubleClickFuncParam = parameter;
   _maxClicks = max(_maxClicks, 2);
 }  // attachDoubleClick
 
 
 // save function for multiClick event
 void Button::attachMultiClick(callbackFunction newFunction) {
   _multiClickFunc = newFunction;
   _maxClicks = max(_maxClicks, 100);
 }  // attachMultiClick
 
 
 // save function for parameterized MultiClick event
 void Button::attachMultiClick(parameterizedCallbackFunction newFunction, void *parameter) {
   _paramMultiClickFunc = newFunction;
   _multiClickFuncParam = parameter;
   _maxClicks = max(_maxClicks, 100);
 }  // attachMultiClick
 
 
 // save function for longPressStart event
 void Button::attachLongPressStart(callbackFunction newFunction) {
   _longPressStartFunc = newFunction;
 }  // attachLongPressStart
 
 
 // save function for parameterized longPressStart event
 void Button::attachLongPressStart(parameterizedCallbackFunction newFunction, void *parameter) {
   _paramLongPressStartFunc = newFunction;
   _longPressStartFuncParam = parameter;
 }  // attachLongPressStart
 
 
 // save function for longPressStop event
 void Button::attachLongPressStop(callbackFunction newFunction) {
   _longPressStopFunc = newFunction;
 }  // attachLongPressStop
 
 
 // save function for parameterized longPressStop event
 void Button::attachLongPressStop(parameterizedCallbackFunction newFunction, void *parameter) {
   _paramLongPressStopFunc = newFunction;
   _longPressStopFuncParam = parameter;
 }  // attachLongPressStop
 
 
 // save function for during longPress event
 void Button::attachDuringLongPress(callbackFunction newFunction) {
   _duringLongPressFunc = newFunction;
 }  // attachDuringLongPress
 
 
 // save function for parameterized during longPress event
 void Button::attachDuringLongPress(parameterizedCallbackFunction newFunction, void *parameter) {
   _paramDuringLongPressFunc = newFunction;
   _duringLongPressFuncParam = parameter;
 }  // attachDuringLongPress
 
 
 // save function for idle button event
 void Button::attachIdle(callbackFunction newFunction) {
   _idleFunc = newFunction;
 }  // attachIdle
 
 
 void Button::reset(void) {
   _state = Button::OCS_INIT;
   _nClicks = 0;
   _startTime = millis();
   _idleState = false;
 }
 
 
 // ShaggyDog ---- return number of clicks in any case: single or multiple clicks
 int Button::getNumberClicks(void) {
   return _nClicks;
 }
 
 
 /**
  * @brief Debounce input pin level for use in SpesialInput.
  */
 bool Button::debounce(const bool value) {
   now = millis();  // current (relative) time in msecs.
 
   // Don't debounce going into active state, if _debounce_ms is negative
   if (value && _debounce_ms < 0)
     debouncedLevel = value;
 
   if (_lastDebounceLevel == value) {
     if (now - _lastDebounceTime >= abs(_debounce_ms))
       debouncedLevel = value;
   } else {
     _lastDebounceTime = now;
     _lastDebounceLevel = value;
   }
   return debouncedLevel;
 };
 
 
 /**
  * @brief Check input of the configured pin,
  * debounce button state and then
  * advance the finite state machine (FSM).
  */
 void Button::tick(void) {
   if (_pin >= 0) {
     _fsm(debounce(digitalRead(_pin) == _buttonPressed));
   }
 }  // tick()
 
 
 void Button::tick(bool activeLevel) {
   _fsm(debounce(activeLevel));
 }
 
 
 /**
  *  @brief Advance to a new state and save the last one to come back in cas of bouncing detection.
  */
 void Button::_newState(stateMachine_t nextState) {
   _state = nextState;
 }  // _newState()
 
 
 /**
  * @brief Run the finite state machine (FSM) using the given level.
  */
 void Button::_fsm(bool activeLevel) {
   unsigned long waitTime = (now - _startTime);
 
   // Implementation of the state machine
   switch (_state) {
     case Button::OCS_INIT:
       // on idle for idle_ms call idle function
       if (!_idleState and (waitTime > _idle_ms))
         if (_idleFunc) {
           _idleState = true;
           _idleFunc();
         }
 
       // waiting for level to become active.
       if (activeLevel) {
         _newState(Button::OCS_DOWN);
         _startTime = now;  // remember starting time
         _nClicks = 0;
 
         if (_pressFunc) _pressFunc();
         if (_paramPressFunc) _paramPressFunc(_pressFuncParam);
       }  // if
       break;
 
     case Button::OCS_DOWN:
       // waiting for level to become inactive.
 
       if (!activeLevel) {
         _newState(Button::OCS_UP);
         _startTime = now;  // remember starting time
 
       } else if (waitTime > _press_ms) {
         if (_longPressStartFunc) _longPressStartFunc();
         if (_paramLongPressStartFunc) _paramLongPressStartFunc(_longPressStartFuncParam);
         _newState(Button::OCS_PRESS);
       }  // if
       break;
 
     case Button::OCS_UP:
       // level is inactive
 
       // count as a short button down
       _nClicks++;
       _newState(Button::OCS_COUNT);
       break;
 
     case Button::OCS_COUNT:
       // dobounce time is over, count clicks
 
       if (activeLevel) {
         // button is down again
         _newState(Button::OCS_DOWN);
         _startTime = now;  // remember starting time
 
       } else if ((waitTime >= _click_ms) || (_nClicks == _maxClicks)) {
         // now we know how many clicks have been made.
 
         if (_nClicks == 1) {
           // this was 1 click only.
           if (_clickFunc) _clickFunc();
           if (_paramClickFunc) _paramClickFunc(_clickFuncParam);
 
         } else if (_nClicks == 2) {
           // this was a 2 click sequence.
           if (_doubleClickFunc) _doubleClickFunc();
           if (_paramDoubleClickFunc) _paramDoubleClickFunc(_doubleClickFuncParam);
 
         } else {
           // this was a multi click sequence.
           if (_multiClickFunc) _multiClickFunc();
           if (_paramMultiClickFunc) _paramMultiClickFunc(_multiClickFuncParam);
         }  // if
 
         reset();
       }  // if
       break;
 
     case Button::OCS_PRESS:
       // waiting for pin being release after long press.
 
       if (!activeLevel) {
         _newState(Button::OCS_PRESSEND);
 
       } else {
         // still the button is pressed
         if ((now - _lastDuringLongPressTime) >= _long_press_interval_ms) {
           if (_duringLongPressFunc) _duringLongPressFunc();
           if (_paramDuringLongPressFunc) _paramDuringLongPressFunc(_duringLongPressFuncParam);
           _lastDuringLongPressTime = now;
         }
       }  // if
       break;
 
     case Button::OCS_PRESSEND:
       // button was released.
 
       if (_longPressStopFunc) _longPressStopFunc();
       if (_paramLongPressStopFunc) _paramLongPressStopFunc(_longPressStopFuncParam);
       reset();
       break;
 
     default:
       // unknown state detected -> reset state machine
       _newState(Button::OCS_INIT);
       break;
   }  // if
 
 }
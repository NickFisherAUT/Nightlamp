/*
  Morse.cpp - Library for flashing Morse code.
  Created by David A. Mellis, November 2, 2007.
  Released into the public domain.
*/

#include "Arduino.h"
#include "Button.h"

Button::Button(int pin)
{
  pinMode(pin, INPUT);
  _buttonPin = pin;
}

bool Button::Released()
{
  bool changed=LOW;
   _reading = digitalRead(_buttonPin);
  if (_reading != _lastButtonState) {
    _lastDebounceTime = millis();
  }
  if ((millis() - _lastDebounceTime) > _debounceDelay) {
       if (_reading != _buttonState) {
      _buttonState = _reading;
    }
  }
  if (_buttonState == HIGH&&_lastButtonState_debounced == LOW) {
    _buttonPressedTime = millis();
  }
  if (_buttonState == LOW && _lastButtonState_debounced == HIGH)
  {
    _buttonReleasedTime = millis();
    _duration=_buttonReleasedTime-_buttonPressedTime;
   changed=HIGH; 
  }
  _lastButtonState = _reading;
  _lastButtonState_debounced=_buttonState;
  if(changed)
  {
    return(HIGH);
  }
  else
  {
  return(LOW);
  }
  //return (_buttonState);
}
bool Button::Value()
{
   _reading = digitalRead(_buttonPin);
  if (_reading != _lastButtonState) {
    _lastDebounceTime = millis();
  }
  if ((millis() - _lastDebounceTime) > _debounceDelay) {
       if (_reading != _buttonState) {
      _buttonState = _reading;
    }
  }
  if (_buttonState == HIGH&&_lastButtonState_debounced == LOW) {
    _buttonPressedTime = millis();
  }
  if (_buttonState == LOW && _lastButtonState_debounced == HIGH)
  {
    _buttonReleasedTime = millis();
    _duration=_buttonReleasedTime-_buttonPressedTime;
  
  }
  _lastButtonState = _reading;
  _lastButtonState_debounced=_buttonState;
  return (_buttonState);
}

unsigned long Button::getDuration()
{
  return (_duration);
}




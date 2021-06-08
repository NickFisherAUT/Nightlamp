/*
  Morse.h - Library for flashing Morse code.
  Created by David A. Mellis, November 2, 2007.
  Released into the public domain.
*/
#ifndef Button_h
#define Button_h

#include "Arduino.h"

class Button
{
  public:
    Button(int pin);
    bool Value();
    bool Released();
    unsigned long getDuration();
   
  private:
    int _buttonPin;
    int _reading;
    bool _buttonState=LOW;
    bool _lastButtonState = LOW;
    bool _lastButtonState_debounced = LOW;
    unsigned long _lastDebounceTime = 0;
    unsigned long _debounceDelay = 50;
    unsigned long _duration = 0;
    unsigned long _buttonPressedTime = 0;
    unsigned long _buttonReleasedTime = 0;

};

#endif

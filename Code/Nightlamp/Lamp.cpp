#include "Arduino.h"
#include "Lamp.h"
//#include "Color.h"

//Lamp::Lamp(int pin)
//{
//  pinMode(pin, INPUT);
//  _buttonPin = pin;
//}

void Lamp::adjustPosition(int val)
{
  if (val < 0 && (ledPosition + val >= -100))
  {
    this->ledPosition += val;
  }
  if (val > 0 && (ledPosition + val <= 100))
  {
    this->ledPosition += val;
  }
}

void Lamp::adjustBrightness(int val)
{
  if (val < 0 && (ledBrightness + val >= 0))
  {
    this->ledBrightness += val;
  }
  if (val > 0 && (ledBrightness + val <= 255))
  {
    this->ledBrightness += val;
  }
}

void Lamp::adjustColorTemperature(int val)
{
  if (val < 0 && (ledColorTemp + val >= -255))
  {
    this->ledColorTemp += val;
  }
  if (val > 0 && (ledColorTemp + val <= 255))
  {
    this->ledColorTemp += val;
  }
}

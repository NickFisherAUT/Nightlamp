#include "Button.h"
#include "Color.h"
#include "Lamp.h"
#include <Adafruit_NeoPixel.h>

// Variables for NEOPIXELS
#define PIN 5
#define NUM_LEDS 72
#define DEF_BRIGHTNESS 255
// NUM_LEDS * 2 für doppelten Streifen
Adafruit_NeoPixel strip = Adafruit_NeoPixel(NUM_LEDS*2, PIN, NEO_GRBW + NEO_KHZ800);

#define default_brightness 10
#define numFadeLeds 10.0
Button btnOnOff(9);
Button btnBrightnessUp(7);
Button btnBrightnessDown(8);
Button btnColorTempUp(12);
Button btnColorTempDown(11);
Button btnMoveLeft(10);
Button btnMoveRight(6);



Colors line [72];
//int stateOnOff = 0;
//int ledBrightness = 100;
//int ledPosition = 0;
//int ledColorTemp = 0;

Lamp nightLamp = {0, default_brightness, 0, 0, 72};


bool cylce10stat = false;
bool cylce100stat = false;
bool cylce500stat = false;
bool cylce1000stat = false;
bool cylce3000stat = false;
bool cylce60_000stat = false;
bool cylce100_000stat = false;

void setup()
{
  Serial.begin(9600);
  strip.begin();
  strip.show(); // Initialize all pixels to 'off'
  strip.setBrightness(DEF_BRIGHTNESS);
  strip.show();


}

void loop()
{

  cycle1000ms();
  cycle500ms();
  cycle100ms();
  cycle10ms();



}
/**************************************************************************************************************
   Cycle Functions
 ***************************************************************************************************************/
void cycle10ms() {
  if (millis() % 10 <= 5 & !cylce10stat)
  {
    cylce10stat = true;
  }
  if (millis() % 10 > 5 & cylce100stat)
  {
    cylce10stat = false;
    /*  User Code 10ms
    ********************************************************************/
    if (btnOnOff.Released())
    {
      int duration = btnOnOff.getDuration();
      if (duration > 1000)
      {
        nightLamp.stateOnOff = 0;
      } else if (nightLamp.stateOnOff < 4)
      {
        nightLamp.stateOnOff++;
      } else
      {
        nightLamp.stateOnOff = 1;
      }
      Serial.print("State On Off: ");
      Serial.println(nightLamp.stateOnOff);
    }


  }
}
void cycle100ms() {
  if (millis() % 100 <= 50 & !cylce100stat)
  {
    cylce100stat = true;
  }
  if (millis() % 100 > 50 & cylce100stat)
  {
    cylce100stat = false;
    /*  User Code 100ms
    ********************************************************************/
    switch (nightLamp.stateOnOff) {
      case 0:
        nightLamp.ledBrightness = default_brightness;
        nightLamp.ledPosition = 0;
        nightLamp.ledColorTemp = 0;
        display_lamp(0, 0, 0, 0, nightLamp.ledBrightness, nightLamp.ledPosition, nightLamp.ledColorTemp, 1);
        display_lamp(0, 0, 0, 0, nightLamp.ledBrightness, nightLamp.ledPosition, nightLamp.ledColorTemp, 2);
        break;
      case 1:
        display_lamp(0, 0, 0, 255, nightLamp.ledBrightness, nightLamp.ledPosition, nightLamp.ledColorTemp, 1);
        display_lamp(0, 0, 0, 255, nightLamp.ledBrightness, nightLamp.ledPosition, nightLamp.ledColorTemp, 2);
        break;
      case 2:
        display_lamp(0, 0, 0, 255, nightLamp.ledBrightness, nightLamp.ledPosition, nightLamp.ledColorTemp, 1);
        display_lamp(0, 0, 0, 255, 0, nightLamp.ledPosition, nightLamp.ledColorTemp, 2);
        break;
      case 3:
        display_lamp(0, 0, 0, 255, 0, nightLamp.ledPosition, nightLamp.ledColorTemp, 1);
        display_lamp(0, 0, 0, 255, nightLamp.ledBrightness, nightLamp.ledPosition, nightLamp.ledColorTemp, 2);
        break;
      case 4:
      show_color_all(255,0,0,0);
        break;
    }

    if (btnMoveLeft.Value())
    {
      nightLamp.adjustPosition(-1);
      Serial.print("Led Position: ");
      Serial.println(nightLamp.ledPosition);
    }
    if (btnMoveRight.Value())
    {
      nightLamp.adjustPosition(1);
      Serial.print("Led Position: ");
      Serial.println(nightLamp.ledPosition);
    }

    if (btnBrightnessUp.Value())
    {
      nightLamp.adjustBrightness(1);
      Serial.print("Led Brightness: ");
      Serial.println(nightLamp.ledBrightness);
    }
    if (btnBrightnessDown.Value())
    {
      nightLamp.adjustBrightness(-1);
      Serial.print("Led Brightness: ");
      Serial.println(nightLamp.ledBrightness);
    }

    if (btnColorTempUp.Value())
    {
      nightLamp.adjustColorTemperature(1);
      Serial.print("Led ColorTemp: ");
      Serial.println(nightLamp.ledColorTemp);
    }
    if (btnColorTempDown.Value())
    {
      nightLamp.adjustColorTemperature(-1);
      Serial.print("Led ColorTemp: ");
      Serial.println(nightLamp.ledColorTemp);
    }


  }
}
void cycle500ms() {

  if (millis() % 500 <= 250 & !cylce500stat)
  {
    cylce500stat = true;
  }
  if (millis() % 500 > 250 & cylce500stat)
  {

    cylce500stat = false;
    /*  User Code 500ms
    ********************************************************************/

  }
}
void cycle1000ms() {
  if (millis() % 1000 <= 500 & !cylce1000stat)
  {
    cylce1000stat = true;
  }
  if (millis() % 1000 > 500 & cylce1000stat)
  {
    cylce1000stat = false;
    /*  User Code 1000ms
    ********************************************************************/
    Serial.println("Test");

    Serial.println(nightLamp.stateOnOff);



  }
}

void display_lamp(double red, double green, double blue, double white, double Neo_brigthness, int centerPos, int ColorTemp, int num_side)
{
  int offset = 0;
  if (num_side == 1)
  {
    // unterseite leuchtet
    offset = 0;
  }
  if (num_side == 2)
  {
    //oberseite leuchtet
    offset = NUM_LEDS;
  }
  int led_start = 1 + centerPos;
  int led_end = led_start + NUM_LEDS - 1;
  if (ColorTemp > 0)
  {
    blue = 0;
    red = ColorTemp;
  } else
  {
    red = 0;
    blue = -ColorTemp;
  }

  if (led_start < 1) {
    led_start = 1;
  }
  if (led_start > NUM_LEDS) {
    led_start = NUM_LEDS;
  }


  if (led_end < 1) {
    led_end = 1;
  }
  if (led_end > NUM_LEDS) {
    led_end = NUM_LEDS;
  }

  Serial.print("Start :");
  Serial.print(led_start);
  Serial.print(" End :");
  Serial.println(led_end);
  for (int i = 1; i <= NUM_LEDS; i = i + 1) {
    strip.setPixelColor(i + offset, 0, 0, 0, 0);
  }
  for (int i = led_start; i <= led_end; i = i + 1) {

    strip.setPixelColor(i + offset, red * Neo_brigthness / 255, green * Neo_brigthness / 255, blue * Neo_brigthness / 255, white * Neo_brigthness / 255);
  }
  if (centerPos > 0)
  {
    double fade = 1.0;
    for (int i = led_start; i > 0 && i > led_start - numFadeLeds; i--)
    {
      fade = fade - 1.0 / numFadeLeds;
      strip.setPixelColor(i + offset, red * Neo_brigthness / 255 * fade, green * Neo_brigthness / 255 * fade, blue * Neo_brigthness / 255 * fade, white * Neo_brigthness / 255 * fade);

    }
  }
  if (centerPos < 0)
  {
    double fade = 1.0;
    for (int i = led_end; i < NUM_LEDS && i < led_end + numFadeLeds; i++)
    {
      fade = fade - 1.0 / numFadeLeds;
      strip.setPixelColor(i + offset, red * Neo_brigthness / 255 * fade, green * Neo_brigthness / 255 * fade, blue * Neo_brigthness / 255 * fade, white * Neo_brigthness / 255 * fade);

    }
  }
  strip.show();

}

void show_color_all(double red, double green, double blue, double white)
{
  for (int i = 1; i <= NUM_LEDS; i = i + 1) {

    strip.setPixelColor(i, red * 10.0 / 100, green * 10.0 / 100, blue * 10.0 / 100, white * 10.0 / 100);
  }
  strip.show();

}

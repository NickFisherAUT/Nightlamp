/*
  Morse.h - Library for flashing Morse code.
  Created by David A. Mellis, November 2, 2007.
  Released into the public domain.
*/
#ifndef Lamp_h
#define Lamp_h


#include "Arduino.h"
//


class Lamp
{
  public:
    int stateOnOff;
    int ledBrightness;
    int ledPosition;
    int ledColorTemp;
    int numberOfPixels;
    
    void adjustPosition(int val);
    void adjustBrightness(int val);
    void adjustColorTemperature(int val);
   

    Lamp(int S, int B, int P, int T, int numPixel){
      stateOnOff=S;
      ledBrightness=B;
      ledPosition=P;
      ledColorTemp=T;
      numberOfPixels=numPixel;
 
      
    }
    Lamp(){
      stateOnOff=0;
      ledBrightness=0;
      ledPosition=0;
      ledColorTemp=0;
      numberOfPixels=72;

    }



    
   
  private:
  
  


};

#endif

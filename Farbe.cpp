/* 
 * File:   Farbe.cpp
 * Author: ronno
 * 
 * Created on 21. November 2013, 07:56
 */
#include <Arduino.h>
#include "Farbe.h"

Farbe::Farbe()
    {
      rot=0;
      gruen=0;
      blau=0;
      brightness = 0;
    }


void Farbe::randomColor()
{
    rot = random(256);
    gruen = random(256);
    blau = random(256);
    if((rot<200 && gruen<200 && blau<200) || (rot>30 && gruen>30 && blau>30))
    {
        randomColor();
    }
}
/* 
 * File:   Element.h
 * Author: ronno
 *
 * Created on 21. November 2013, 07:55
 */

#ifndef ELEMENT_H
#define	ELEMENT_H

#include <Arduino.h>
#include "Farbe.h"

class Element
{
  private:
    Farbe farbe;
    Farbe target;
    float distRot;
    float distGruen;
    float distBlau;
    
    int rotKanal;
    int gruenKanal;
    int blauKanal;
    
    float fRot;
    float fGruen;
    float fBlau;
    
    int aufBlinken;
    
  public:
    
    Element() {};
    Element(int rotKanal, int gruenKanal, int blauKanal);
    void setzeKanal(int rotKanal, int gruenKanal, int blauKanal);
    void setzeFarbe(int rot, int gruen, int blau);
    void leuchten();
    void blinken();
    void randomColor();
    void pulseUp();
    void pulseDown();
    void goToColor();
    
    Farbe getFarbe();
    int getBrightness();
    
    void setFarbe(int r, int g, int b);
    void setFarbe(Farbe neueFarbe);
    void setTargetColor(Farbe target);
    void setBrightness(int wert);
    void increaseBrightness();
    void decreaseBrightness();
};

#endif	/* ELEMENT_H */


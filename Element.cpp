/* 
 * File:   Element.cpp
 * Author: ronno
 * 
 * Created on 21. November 2013, 07:55
 */

#include "Element.h"

Element::Element(int rotKanal, int gruenKanal, int blauKanal, String name)
{
    this->rotKanal = rotKanal;
    this->gruenKanal = gruenKanal;
    this->blauKanal = blauKanal;
    this->name = name;
    
    aufBlinken = 0;
    
    
    leuchten();
}
void Element::setzeKanal(int rotKanal, int gruenKanal, int blauKanal)
{
    this->rotKanal = rotKanal;
    this->gruenKanal = gruenKanal;
    this->blauKanal = blauKanal;
}
void Element::setzeFarbe(int rot, int gruen, int blau)
{
    farbe.rot = rot;
    farbe.gruen = gruen;
    farbe.blau = blau;
}
void Element::leuchten()
{
    if(farbe.brightness)
    {
        analogWrite(rotKanal,int(float(farbe.rot)*float(farbe.brightness)/255));
        analogWrite(gruenKanal,int(float(farbe.gruen)*float(farbe.brightness)/255));
        analogWrite(blauKanal,int(float(farbe.blau)*float(farbe.brightness)/255));
    } else
    {
        analogWrite(rotKanal,0);
        analogWrite(gruenKanal,0);
        analogWrite(blauKanal,0);
    }
}
void Element::blinken()
{
    if(aufBlinken)
    {
        leuchten();
        aufBlinken = 0;
    }
    else
    {
        analogWrite(rotKanal, 0);
        analogWrite(gruenKanal, 0);
        analogWrite(blauKanal, 0);
        aufBlinken = 1;
    }
    
}

void Element::randomColor()
{
    farbe.randomColor();
}

void Element::pulseUp()
{
    if(getBrightness()<255) increaseBrightness();
    if(getBrightness()>25 && getBrightness()<255) increaseBrightness();
    if(getBrightness()>50 && getBrightness()<255) increaseBrightness();
    if(getBrightness()>100 && getBrightness()<255) increaseBrightness();
    if(getBrightness()>150 && getBrightness()<255) increaseBrightness();
    if(getBrightness()>200 && getBrightness()<255) increaseBrightness();
    
    leuchten();
}
void Element::pulseDown()
{
    if(getBrightness()>0) decreaseBrightness();
    if(getBrightness()>25) decreaseBrightness();
    if(getBrightness()>50) decreaseBrightness();
    if(getBrightness()>100) decreaseBrightness();
    if(getBrightness()>150) decreaseBrightness();
    if(getBrightness()>200) decreaseBrightness();
    
    leuchten();
}
void Element::setTargetColor(Farbe target)
{
    this->target = target;
    distRot = target.rot - farbe.rot;
    distGruen = target.gruen - farbe.gruen;
    distBlau = target.blau - farbe.blau;
    
    fRot = farbe.rot;
    fGruen = farbe.gruen;
    fBlau = farbe.blau;
}
void Element::setTargetColor(int rot, int gruen, int blau)
{
    target.rot = rot;
    target.gruen = gruen;
    target.blau = blau;
    distRot = target.rot - farbe.rot;
    distGruen = target.gruen - farbe.gruen;
    distBlau = target.blau - farbe.blau;
    
    fRot = farbe.rot;
    fGruen = farbe.gruen;
    fBlau = farbe.blau;
}
void Element::targetRandomColor()
{
    target.randomColor();
    
    distRot = target.rot - farbe.rot;
    distGruen = target.gruen - farbe.gruen;
    distBlau = target.blau - farbe.blau;
    
    fRot = farbe.rot;
    fGruen = farbe.gruen;
    fBlau = farbe.blau;
}
void Element::goToColor()
{
    fRot += distRot/255;
    fGruen += distGruen/255;
    fBlau += distBlau/255;
    farbe.rot = fRot;
    farbe.gruen = fGruen;
    farbe.blau = fBlau;
    
    farbe.printFarbe();

    leuchten();
}
Farbe Element::getFarbe()
{
    return farbe;
}
int Element::getBrightness()
{
    return farbe.brightness;
}
String Element::getName()
{
    return name;
}
void Element::setFarbe(int r, int g, int b)
{
    farbe.rot = r;
    farbe.gruen = g;
    farbe.blau = b;
}
void Element::setFarbe(Farbe neueFarbe)
{
    farbe = neueFarbe;
}
void Element::farbeRandomColor()
{
    farbe.randomColor();
}
void Element::setBrightness(int wert)
{
    if (0<=wert && wert<=255)
    {
        farbe.brightness = wert;
    }else
    {
        Serial.println("===================== UNGUELTIGER WER FUER BRIGHTNESS!!!");
    }
}
void Element::increaseBrightness()
{
    if (farbe.brightness<255)
    {
        farbe.brightness++;
    }
}
void Element::decreaseBrightness()
{
    if (farbe.brightness>0)
    {
        farbe.brightness--;
    }
}


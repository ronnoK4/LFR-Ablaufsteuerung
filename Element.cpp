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
//    if(getBrightness()<255) increaseBrightness();
//    if(getBrightness()>40 && getBrightness()<255) increaseBrightness();
//    if(getBrightness()>70 && getBrightness()<255) increaseBrightness();
//    if(getBrightness()>100 && getBrightness()<255) increaseBrightness();
//    if(getBrightness()>130 && getBrightness()<255) increaseBrightness();
//    if(getBrightness()>160 && getBrightness()<255) increaseBrightness();
//    if(getBrightness()>190 && getBrightness()<255) increaseBrightness();
//    if(getBrightness()>220 && getBrightness()<255) increaseBrightness();
    
    farbe.brightness += exp((farbe.brightness-30)/100);
        if(farbe.brightness>255)
        farbe.brightness=255;
    
//    Serial.print("======");
//    Serial.println(farbe.brightness);
    
    leuchten();
}
void Element::pulseDown()
{
//    if(getBrightness()>0) decreaseBrightness();
//    if(getBrightness()>40) decreaseBrightness();
//    if(getBrightness()>70) decreaseBrightness();
//    if(getBrightness()>100) decreaseBrightness();
//    if(getBrightness()>130) decreaseBrightness();
//    if(getBrightness()>160) decreaseBrightness();
//    if(getBrightness()>190) decreaseBrightness();
//    if(getBrightness()>220) decreaseBrightness();
    
    farbe.brightness -= exp((farbe.brightness-30)/100);
    if(farbe.brightness<0)
        farbe.brightness=0;
    
//    Serial.print("======");
//    Serial.println(farbe.brightness);
    
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
void Element::targetHardRandomColor()
{
    target.hardRandomColor();
    
    distRot = target.rot - farbe.rot;
    distGruen = target.gruen - farbe.gruen;
    distBlau = target.blau - farbe.blau;
    
    fRot = farbe.rot;
    fGruen = farbe.gruen;
    fBlau = farbe.blau;
}
void Element::goToColor()
{
    fRot += distRot/256;
    fGruen += distGruen/256;
    fBlau += distBlau/256;
    farbe.rot = fRot;
    farbe.gruen = fGruen;
    farbe.blau = fBlau;
    
//    farbe.printFarbe();

    leuchten();
}
Farbe Element::getFarbe()
{
    return farbe;
}
Farbe Element::getTargetColor()
{
    return target;
}
double Element::getBrightness()
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
void Element::setBrightness(double wert)
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


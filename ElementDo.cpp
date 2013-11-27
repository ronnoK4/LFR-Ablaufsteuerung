/* 
 * File:   ElementDo.cpp
 * Author: ronno
 * 
 * Created on 21. November 2013, 08:06
 */

#include "ElementDo.h"


ElementDo::ElementDo()
{
    functionCount = 0;
    activated = false;
    functionTimer = millis();
    for (int i = 0; i<4; i++)
    {
        observers[i] = NULL;
    }
    name = "default";
}
ElementDo::ElementDo(String name)
{
    functionCount = 0;
    activated = false;
    functionTimer = millis();
    for (int i = 0; i<4; i++)
    {
        observers[i] = NULL;
    }
    this->name = name;
}
String ElementDo::getName()
{
    return name;
}
void ElementDo::activate()
{
	activated = true;
        Serial.print(functionElement->getName());
        Serial.print("::");
        Serial.print(getName());
        Serial.print(" ->activated");
        Serial.println(activated);

}
void ElementDo::activateObservers()
{
    for (int i = 0; i<4; i++)
    {
        if (observers[i])
        {
            observers[i]->activate();
        }
    }
}
void ElementDo::setFunctionElement(Element *functionElement)
{
	this->functionElement = functionElement;
}

void ElementDo::setObserver(ElementDo *observer, int number)
{
    observers[number] = observer;
}
void ElementDo::deleteObserver()
{
	observers[0] = NULL;
}
/**
 * 
 */
void ElementDoSetColor::now()
{
    if(activated)
    {
        switch(mode)
        {
            case(0):
                functionElement->farbeRandomColor();
                break;
            case(1):
                functionElement->setFarbe(rot, gruen, blau);
                break;
            case(2):
                functionElement->setFarbe(targetElement->getFarbe());
                break;  
            default:
                functionElement->setFarbe(255, 255, 255);
                break;
        }
            functionElement->leuchten();
            activateObservers();
            activated = false;
            functionElement->farbe.printFarbe();
    }
}
void ElementDoSetTargetColor::now()
{
    if(activated)
    {
        switch(mode)
        {
            case(0):
                functionElement->targetRandomColor();
                break;
            case(1):
            functionElement->targetHardRandomColor();
            break;
            case(2):
                functionElement->setTargetColor(rot, gruen, blau);
                break;
            case(3):
                functionElement->setTargetColor(targetElement->getFarbe());
                break;
            case(4):
            {
                startFarbe = startElement->getTargetColor();
                zielFarbe = targetElement->getTargetColor();
                startFarbe.rot += ((zielFarbe.rot - startFarbe.rot)*station)/3;
                startFarbe.gruen += ((zielFarbe.gruen - startFarbe.gruen)*station)/3;
                startFarbe.blau += ((zielFarbe.blau - startFarbe.blau)*station)/3;

                functionElement->setTargetColor(startFarbe);
            }
            break;
            default:
                functionElement->setTargetColor(255, 255, 255);
                break;
        }
        
        Serial.print("===");
        Serial.print(functionElement->getName());
        Serial.print("===WURDE AUF");
        functionElement->target.printFarbe();
        Serial.print("===GESETZT");
            activateObservers();
            activated = false;
    }
}
void ElementDoSetBrightness::now()
{
    if(activated)
    {   
        functionElement->setBrightness(brightness);
        functionElement->leuchten();
        activateObservers();
        activated = false;
    }
}
void ElementDoBlink::now()
{
    if(activated)
    {
        if(functionTimer+velocity < millis())
        {            
            functionElement->blinken();
            functionCount++;
            functionTimer = millis();
            if(functionCount > counts)
            {
                activateObservers();
                activated = false;
                functionCount = 0;
            }
        }
    }
}
void ElementDoBlinkToSmooth::now()
{
    if(activated)
    {
        if(functionTimer+velocity < millis())
        {   
            if(velocity>100){
                acceleration = velocity*0.1;
            }
            else if(velocity>75){
                acceleration = velocity*0.04;
            }else if(velocity>50){
                acceleration = velocity*0.01;
            }else {
                acceleration = velocity*0.005;
            }
            
            functionElement->blinken();
            functionCount++;
            functionTimer = millis();
            velocity -= acceleration;
            
            if(velocity < 10)
            {
                activateObservers();
                activated = false;
                velocity = velOriginal;
            }
        }
    }
}
void ElementDoPulseUp::now()
{
    if(activated)
    {  	
        if(functionTimer+velocity < millis())
        {
            functionElement->pulseUp();
            functionCount++;
            functionTimer = millis();
            if(functionCount > counts)
            {
                activateObservers();
                activated = 0;
                functionCount = 0;
            }
//            Serial.print("======");
//            Serial.print(counts);
//            Serial.print("======");
//            Serial.println(functionElement->getBrightness());
        }
    }
}
void ElementDoPulseDown::now()
{
    if(activated)
    {
        if(functionTimer+velocity < millis())
        {
            functionElement->pulseDown();
            functionCount++;
            functionTimer = millis();
            if(functionCount > counts)
            {
                activateObservers();
                activated = false;
                functionCount = 0;
            }
//            Serial.print("======");
//            Serial.print(functionCount);
//            Serial.print("======");
//            Serial.println(functionElement->getBrightness());
        }
    }
}
void ElementDoGoToColor::now()
{
    if(activated)
    {
        if(functionTimer+velocity < millis())
        {
            functionElement->goToColor();
            functionCount++;
            functionTimer = millis();
            if(functionCount > counts)
            {
                activateObservers();
                activated = false;
                functionCount = 0;
                Serial.print("===");
                Serial.print(functionElement->getName());
                functionElement->farbe.printFarbe();
            }
        }
    }
}
void ElementDoLastElement::setLastObservers(ElementDo *raute, ElementDo *let, ElementDo *freedom, ElementDo *ring)
{	  	
	this->raute = raute;
	this->let = let;
	this->freedom = freedom;
	this->ring = ring;
        
        Serial.println("setLastObservers");
}
void ElementDoLastElement::activate()
{
  	Serial.println("lastActivate");

	activationCount++;
	if(activationCount>3)
	{		
		raute->activate();
		let->activate();
		freedom->activate();
		ring->activate();
		activationCount = 0;
	}
}
 void ElementDoNothing::now()
 {
     if(activated)
     {
         if(functionTimer+delay < millis())
         {
             if(count > 0)
             {
                 activateObservers();
                 activated = false;
                 count = -1;
             }
             functionTimer = millis();
             count++;
         }
     }
 }
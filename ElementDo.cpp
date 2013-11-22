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
    for (int i = 0; i<3; i++)
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
    for (int i = 0; i<3; i++)
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
        Serial.print(getName());
        Serial.print("activated");
        Serial.println(activated);

}
void ElementDo::activateObservers()
{
    for (int i = 0; i<3; i++)
    {
        if (observers[i])
        {
            observers[i]->activate();
            Serial.print("activateObserver-> ");
            Serial.println(observers[i]->getName());
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
	delete observers[0];
}

void ElementDo::now() { }

void ElementDoSetColor::now()
{
    if(activated)
    {
        functionElement->setFarbe(targetColor);
        functionElement->leuchten();
        activateObservers();
        activated = false;
    }
}
//void ElementDoSetColor::activate()
//{
//	activated = true;
//}
void ElementDoSetElementTargetColor::now()
{
    if(activated)
    {   
        functionElement->setTargetColor(targetElement->getFarbe());
        functionElement->leuchten();
        activateObservers();
        activated = false;
    }
}
//void ElementDoSetElementTargetColor::activate()
//{
//	activated = true;
//}
void ElementDoSetTargetColor::now()
{
    if(activated)
    {
        functionElement->setTargetColor(targetColor);	
	    activateObservers();
        activated = false;
    }
}
//void ElementDoSetTargetColor::activate()
//{
//	activated = true;
//}
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
				// Serial.println("passed");
                activateObservers();
                
                activated = false;
                functionCount = 0;
            }
        }
    }
}
//void ElementDoBlink::activate()
//{
//	activated = true;
//}
void ElementDoPulseUp::now()
{
    if(activated)
    {  
//		Serial.println("pulseUp");
	
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
  				
//				Serial.println("pulseUp->functionCount");
            }
        }
    }
}
//void ElementDoPulseUp::activate()
//{
//	activated = true;
//}
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
        }
    }
}
//void ElementDoPulseDown::activate()
//{
//	activated = true;
//}
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



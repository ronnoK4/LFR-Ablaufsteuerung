/* 
 * File:   ElementDo.h
 * Author: ronno
 *
 * Created on 21. November 2013, 08:06
 */

#ifndef ELEMENTDO_H
#define	ELEMENTDO_H

#include <Arduino.h>
#include "Farbe.h"
#include "Element.h"

class ElementDo
{
private:

protected:
    Element *functionElement;
    ElementDo *observers[4];
    unsigned long functionCount;
    boolean activated;
    unsigned long functionTimer;
    String name;
    
public:
    ElementDo();
    ElementDo(String name);
    void activateObservers();
    void setFunctionElement(Element *functionElement);
    void setObserver(ElementDo *observer, int number);
    void deleteObserver();
    void setVelocity(int velocity);
    void setCounts(int counts);
    String getName();

    virtual void activate();
    void setLastObservers() {}    //code ging nachdem ich diese funktion auskommentiert hatte... evt. hat das virtual void ohne 0=; gestört
    virtual void now() {}
};

class ElementDoSetColor : public ElementDo
{
private:
    Element *targetElement;
    int rot;
    int gruen;
    int blau;
    int mode;
public:
    ElementDoSetColor() : ElementDo("SetColor-random")
    {
        mode = 0;
    }
    ElementDoSetColor(int rot, int gruen,  int blau) : ElementDo("SetColor-RGB")
    {
        mode = 1;
        this->rot = rot;
        this->gruen = gruen;
        this->blau = blau;
    }
    ElementDoSetColor(Element *targetElement) : ElementDo("SetColor-Element")
    {
        mode = 2;
        this->targetElement = targetElement;
    }

    void now();
};

class ElementDoSetTargetColor : public ElementDo
{
private:
    int rot;
    int gruen;
    int blau;
    Element *targetElement;
    Element *startElement;
    Farbe startFarbe;
    Farbe zielFarbe;
    int mode;
    int station;
public:
    ElementDoSetTargetColor() : ElementDo("SetTargetColor-random")
    {
        mode = 0;
    }
    ElementDoSetTargetColor(String hart) : ElementDo("SetTargetColor-HARDrandom")
    {
        mode = 1;
    }   
    ElementDoSetTargetColor(int rot, int gruen, int blau) : ElementDo("SetTargetColor-RGB")
    {
        mode = 2;
        this->rot = rot;
        this->gruen = gruen;
        this->blau = blau;
    }
    ElementDoSetTargetColor(Element *targetElement) : ElementDo("SetTargetColor-Element")
    {
        mode = 3;
        this->targetElement =  targetElement;
    }
    ElementDoSetTargetColor(Element *startElement, Element *targetElement, int station) : ElementDo("Set-TargetColor-Spektrum")
    {
        mode = 4;
        this->targetElement = targetElement;
        this->startElement = startElement;
        this->station = station;
    }
    void now();
};

class ElementDoSetBrightness : public ElementDo
{
private:
    int brightness;
public:
    ElementDoSetBrightness(int brightness) : ElementDo("SetBrightness")
    {
        this->brightness = brightness;
    } 
    void now();
};

class ElementDoBlink : public ElementDo
{
private:
	int velocity;
	int counts;
public:
    ElementDoBlink(int velocity, int counts) : ElementDo("Blink")
	{
                this->velocity = velocity;
		this->counts = counts;
	}
    void now();
};
class ElementDoBlinkToSmooth : public ElementDo
{
private:

	int velOriginal;
        double velocity;
        double acceleration;
public:

    ElementDoBlinkToSmooth(int velocity) : ElementDo("BlinkToSmooth")
	{
                this->velocity = velocity;
		this->velOriginal = velocity;
	}
    void now();
};
class ElementDoPulseUp : public ElementDo
{
private:
	int velocity;
	int counts;

public:
    ElementDoPulseUp(int velocity, int counts) : ElementDo("PulseUp")
	{
		this->velocity = velocity;
		this->counts = counts;
	}
    void now();
};

class ElementDoPulseDown : public ElementDo
{
private:
	int velocity;
	int counts;
public:
    ElementDoPulseDown(int velocity, int counts) : ElementDo("PulseDown")
	{
		this->velocity = velocity;
		this->counts = counts;

	}
    void now();
};

class ElementDoGoToColor : public ElementDo
{
private:
	int velocity;
	int counts;
public:
    ElementDoGoToColor(int velocity, int counts) : ElementDo("GoToColor")
	{
		this->velocity = velocity;		
		this->counts = counts;
	}
    void now();
};
class ElementDoLastElement : public ElementDo
{
private:
	ElementDo *raute;
	ElementDo *let;
	ElementDo *freedom;
	ElementDo *ring;
	int activationCount;
	
public:
	ElementDoLastElement() : ElementDo("LastElement")
	{
		activationCount = 0;
	}
	void activate();
	void setLastObservers(ElementDo *raute, ElementDo *let, ElementDo *freedom, ElementDo *ring);
};

 class ElementDoNothing : public ElementDo
 {
 private:
 	unsigned long delay;
        int count;
 public:
     ElementDoNothing(unsigned long delay) : ElementDo("Nothing")
     {
         this->delay = delay;
         count = -1;
     }
     void now();
 };

#endif	/* ELEMENTDO_H */


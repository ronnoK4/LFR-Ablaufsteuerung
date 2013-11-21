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
    ElementDo *observers[3];
    unsigned long functionCount;
    boolean activated;
    unsigned long functionTimer;
    
public:
    ElementDo();
    void activateObservers();
    void setFunctionElement(Element *functionElement);
    void setObserver(ElementDo *observer, int number);
    void deleteObserver();
    void setVelocity(int velocity);
    void setCounts(int counts);

    void activate();
    void setLastObservers() {}    //code ging nachdem ich diese funktion auskommentiert hatte... evt. hat das virtual void ohne 0=; gestört
    virtual void now();
};

class ElementDoSetColor : public ElementDo
{
private:
    Farbe targetColor;
public:
    ElementDoSetColor(Farbe targetColor) : ElementDo()
    {
        this->targetColor = targetColor;
    }
    void now();
//    void activate();
};

class ElementDoSetElementTargetColor : public ElementDo
{
private:
    Element *targetElement;
public:
    ElementDoSetElementTargetColor(Element *targetElement) : ElementDo()
    {
        this->targetElement =  targetElement;
    }
    
    void now();
//    void activate();
};

class ElementDoSetTargetColor : public ElementDo
{
private:
    Farbe targetColor;
public:
    ElementDoSetTargetColor(Farbe targetColor) : ElementDo()
    {
        this->targetColor = targetColor;
    }
    
    void now();
//    void activate();
};

class ElementDoBlink : public ElementDo
{
private:
	int velocity;
	int counts;
public:
    ElementDoBlink(int velocity, int counts) : ElementDo()
	{
		this->velocity = velocity;
		this->counts = counts;
	}
    void now();
//    void activate();
};

class ElementDoPulseUp : public ElementDo
{
private:
	int velocity;
	int counts;

public:
    ElementDoPulseUp(int velocity, int counts) : ElementDo()
	{
		this->velocity = velocity;
		this->counts = counts;
	}
    void now();
//    void activate();
};

class ElementDoPulseDown : public ElementDo
{
private:
	int velocity;
	int counts;
public:
    ElementDoPulseDown(int velocity, int counts) : ElementDo()
	{
		this->velocity = velocity;
		this->counts = counts;

	}
    void now();
//    void activate();
};

class ElementDoGoToColor : public ElementDo
{
private:
	int velocity;
	int counts;
public:
    ElementDoGoToColor(int velocity, int counts) : ElementDo()
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
	ElementDoLastElement() : ElementDo()
	{
		activationCount = 0;
	}
	void activate();
	void setLastObservers(ElementDo *raute, ElementDo *let, ElementDo *freedom, ElementDo *ring);
};

// class ElementDoNothing : public ElementDo
// {
// private:
// 	delay
// public:
//     ElementDoNothing(unsigned long delay) : ElementDo()
//     {
//         functionCount = delay;
//     }
//     void now();
// };

#endif	/* ELEMENTDO_H */


#include <Arduino.h>
#include "Element.h"
#include "ElementDo.h"

#define ARRAY_SIZE 7


Element raute(2,3,4);
Element let(5,6,7);
Element freedom(8,9,10);
Element ring(11,12,13);

int pulseFULL;
int goToColorFULL;

ElementDo **rauteArray = new ElementDo*[ARRAY_SIZE];
ElementDo **letArray = new ElementDo*[ARRAY_SIZE];
ElementDo **freedomArray = new ElementDo*[ARRAY_SIZE];
ElementDo **ringArray = new ElementDo*[ARRAY_SIZE];

ElementDoLastElement lastElement;


void rauteSetup();
void letSetup();
void freedomSetup();
void ringSetup();
void setArrayFunctionElement(ElementDo **doArray, Element *elem, int anzahl);
void setArrayObservers(ElementDo **doArray, int anzahl);

//HardwareSerial Serial;


void setup()
{
  Serial.begin(9600);
  
  delay(1000);
  pulseFULL = 86;
  goToColorFULL = 255;

  delay(random(500));
  rauteSetup();
  delay(random(500));
  letSetup();
  delay(random(500));
  freedomSetup();
  delay(random(500));
  ringSetup();

  lastElement.setLastObservers(rauteArray[0], letArray[0], freedomArray[0], ringArray[0]);
}

void loop()
{
//  Serial.println("loop");
  for(int i=0; i<ARRAY_SIZE; i++)
  {
    rauteArray[i]->now();
    letArray[i]->now();
    freedomArray[i]->now();
    ringArray[i]->now();
  }
}

void setArrayFunctionElement(ElementDo **doArray, Element *elem, int anzahl)
{
  for(int i=0; i<anzahl; i++)
  {
    doArray[i]->setFunctionElement(elem);
  }
}

void setArrayObservers(ElementDo **doArray, int anzahl)
{
  for(int i=0; i<anzahl-1; i++)
  {
    doArray[i]->setObserver(doArray[i+1], 0);
  }
  doArray[anzahl-1]->setObserver(&lastElement, 0);
}

void rauteSetup()
{
  raute.randomColor();
  raute.setBrightness(255);
  
  rauteArray[0] = new ElementDoBlink                    (random(250), 3);
  rauteArray[1] = new ElementDoBlink                    (random(250), 3);
  rauteArray[2] = new ElementDoBlink                    (random(250), 3);
  rauteArray[3] = new ElementDoBlink                    (random(250), 3);
  rauteArray[4] = new ElementDoPulseDown                (50, pulseFULL);
  rauteArray[5] = new ElementDoNothing                  (5000);
  rauteArray[6] = new ElementDoPulseUp                  (50, pulseFULL);

  setArrayFunctionElement(rauteArray, &raute, ARRAY_SIZE);
  setArrayObservers(rauteArray, ARRAY_SIZE);
  rauteArray[0]->activate();
}

void letSetup()
{
  let.randomColor();
  let.setBrightness(255);
  
  letArray[0] = new ElementDoBlink                    (random(250), 3);
  letArray[1] = new ElementDoBlink                    (random(250), 3);
  letArray[2] = new ElementDoBlink                    (random(250), 3);
  letArray[3] = new ElementDoBlink                    (random(250), 3);
  letArray[4] = new ElementDoPulseDown                (50, pulseFULL);
  letArray[5] = new ElementDoNothing                  (5000);
  letArray[6] = new ElementDoPulseUp                  (50, pulseFULL);
 
  setArrayFunctionElement(letArray, &let, ARRAY_SIZE);
  setArrayObservers(letArray, ARRAY_SIZE);
  letArray[0]->activate();
  
//  letArray[4]->setObserver(freedomArray[4], 0);       //freedom soll nach raute und ring auch langsam runterfahren
}

void freedomSetup()
{
  freedom.randomColor();
  freedom.setBrightness(255);
  
  freedomArray[0] = new ElementDoBlink                    (random(250), 3);
  freedomArray[1] = new ElementDoBlink                    (random(250), 3);
  freedomArray[2] = new ElementDoBlink                    (random(250), 3);
  freedomArray[3] = new ElementDoBlink                    (random(250), 3);
  freedomArray[4] = new ElementDoPulseDown                (50, pulseFULL);
  freedomArray[5] = new ElementDoNothing                  (5000);
  freedomArray[6] = new ElementDoPulseUp                  (50, pulseFULL);
  
  setArrayFunctionElement(freedomArray, &freedom, ARRAY_SIZE);
  setArrayObservers(freedomArray, ARRAY_SIZE);
  freedomArray[0]->activate();
  
//  freedomArray[3]->deleteObserver();                          //wird von letArray[4] gesetzt
}

void ringSetup()
{
  ring.randomColor();
  ring.setBrightness(255);
  
  ringArray[0] = new ElementDoBlink                    (random(250), 3);
  ringArray[1] = new ElementDoBlink                    (random(250), 3);
  ringArray[2] = new ElementDoBlink                    (random(250), 3);
  ringArray[3] = new ElementDoBlink                    (random(250), 3);
  ringArray[4] = new ElementDoPulseDown                (50, pulseFULL);
  ringArray[5] = new ElementDoNothing                  (5000);
  ringArray[6] = new ElementDoPulseUp                  (50, pulseFULL);

  setArrayFunctionElement(ringArray, &ring, ARRAY_SIZE);
  setArrayObservers(ringArray, ARRAY_SIZE);
  ringArray[0]->activate();
}



int main(void)
{
	init();
	setup();
	for (;;)
		loop();

	return 0; // must NEVER be reached
}
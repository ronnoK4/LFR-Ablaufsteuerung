#include <Arduino.h>
#include "Element.h"
#include "ElementDo.h"

#define ARRAY_SIZE 27


Element raute(2,3,4, "RAUTE");
Element let(5,6,7, "LET");
Element freedom(8,9,10, "FREEDOM");
Element ring(11,12,13, "RING");

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
  pulseFULL = 127;
  goToColorFULL = 255;

  rauteSetup();
  letSetup();
  freedomSetup();
  ringSetup();

  lastElement.setLastObservers(rauteArray[22], letArray[22], freedomArray[22], ringArray[22]);
}

void loop()
{
//  Serial.println("loop");
  for(int i=22; i<ARRAY_SIZE; i++)
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
  raute.setFarbe(255,0,0);
  raute.setBrightness(255);
  rauteArray[0] = new ElementDoBlink                    (random(250), 3);
  rauteArray[1] = new ElementDoBlink                    (random(250), 3);
  rauteArray[2] = new ElementDoBlink                    (random(250), 3);
  rauteArray[3] = new ElementDoBlink                    (random(250), 3);
  rauteArray[4] = new ElementDoNothing                  (3000);
  rauteArray[5] = new ElementDoBlinkToSmooth            (800);
  rauteArray[6] = new ElementDoSetBrightness            (127);
  rauteArray[7] = new ElementDoSetTargetColor           ();                    //setzen einer zufallsfarbe  
  rauteArray[8] = new ElementDoGoToColor                (20, goToColorFULL);
  rauteArray[9] = new ElementDoPulseDown                (30, pulseFULL*0.8);
  rauteArray[10] = new ElementDoPulseUp                 (30, pulseFULL*0.8);
  rauteArray[11] = new ElementDoPulseDown               (30, pulseFULL*0.8);
  rauteArray[12] = new ElementDoPulseUp                 (30, pulseFULL*0.8);
  rauteArray[13] = new ElementDoPulseDown               (30, pulseFULL);
  rauteArray[14] = new ElementDoSetTargetColor          (&let);
  rauteArray[15] = new ElementDoNothing                 (random(1500));
  rauteArray[16] = new ElementDoPulseUp                 (random(10), pulseFULL);
  rauteArray[17] = new ElementDoGoToColor               (15, goToColorFULL);
  rauteArray[18] = new ElementDoSetTargetColor          ("hart");
  rauteArray[19] = new ElementDoGoToColor               (20, goToColorFULL);
  rauteArray[20] = new ElementDoNothing                 (10000);
  rauteArray[21] = new ElementDoPulseDown               (random(80,300), pulseFULL);
  
  //====================2. Abschnitt============================================
  
  rauteArray[22] = new ElementDoPulseUp               (1, pulseFULL);
  rauteArray[23] = new ElementDoPulseDown             (1, pulseFULL);
  rauteArray[24] = new ElementDoPulseUp               (2, pulseFULL*0.5);
  rauteArray[25] = new ElementDoPulseDown             (2, pulseFULL*0.5);
  rauteArray[26] = new ElementDoNothing               (800);
  
  
  setArrayFunctionElement(rauteArray, &raute, ARRAY_SIZE);
  setArrayObservers(rauteArray, ARRAY_SIZE);
  rauteArray[22]->activate();
  
  rauteArray[3]->deleteObserver(); 
  rauteArray[4]->setObserver(letArray[6], 1);
  rauteArray[4]->setObserver(freedomArray[5], 2);
  rauteArray[4]->setObserver(ringArray[6], 3);
  rauteArray[14]->setObserver(letArray[7], 1);
  rauteArray[14]->setObserver(freedomArray[6], 2);
  rauteArray[14]->setObserver(ringArray[7], 3);
  rauteArray[18]->setObserver(ringArray[11], 0);
  
  //====================2. Abschnitt============================================

  


 }

void letSetup()
{
  randomSeed(analogRead(0));
  let.setFarbe(255,255,255);
  let.setBrightness(255);
  
  letArray[0] = new ElementDoBlink                    (random(250), 3);
  letArray[1] = new ElementDoBlink                    (random(250), 3);
  letArray[2] = new ElementDoBlink                    (random(250), 3);
  letArray[3] = new ElementDoBlink                    (random(250), 3);
  letArray[4] = new ElementDoPulseDown                (75, pulseFULL*0.9);
  letArray[5] = new ElementDoPulseDown                (100, pulseFULL*0.11);
  letArray[6] = new ElementDoSetColor                 ();
  letArray[7] = new ElementDoSetTargetColor           (&freedom);
  letArray[8] = new ElementDoNothing                  (random (1500));
  letArray[9] = new ElementDoPulseUp                  (random(10), pulseFULL); 
  letArray[10] = new ElementDoGoToColor               (15, goToColorFULL);
  letArray[11] = new ElementDoSetTargetColor          (&raute, &ring, 1);
  letArray[12] = new ElementDoGoToColor               (20, goToColorFULL);
  letArray[13] = new ElementDoNothing                 (10000);
  letArray[14] = new ElementDoPulseDown               (random(80,300), pulseFULL);
  letArray[15] = new ElementDoNothing                 (1);
  letArray[16] = new ElementDoNothing                 (1);
  letArray[17] = new ElementDoNothing                 (1);
  letArray[18] = new ElementDoNothing                 (1);
  letArray[19] = new ElementDoNothing                 (1);
  letArray[20] = new ElementDoNothing                 (1);
  letArray[21] = new ElementDoNothing                 (1);
  
  //====================2. Abschnitt============================================
  
  letArray[22] = new ElementDoPulseUp               (1, pulseFULL);
  letArray[23] = new ElementDoPulseDown             (1, pulseFULL);
  letArray[24] = new ElementDoPulseUp               (2, pulseFULL*0.5);
  letArray[25] = new ElementDoPulseDown             (2, pulseFULL*0.5);
  letArray[26] = new ElementDoNothing               (800);
  
  setArrayFunctionElement(letArray, &let, ARRAY_SIZE);
  setArrayObservers(letArray, ARRAY_SIZE);
  letArray[22]->activate();
  
  letArray[4]->deleteObserver();       //freedom soll nach raute und ring auch langsam runterfahren
  letArray[5]->deleteObserver();
  letArray[6]->deleteObserver();
  letArray[11]->setObserver(rauteArray[19], 1);
  letArray[11]->setObserver(freedomArray[11], 2);
  letArray[11]->setObserver(ringArray[12], 3);
  
  //====================2. Abschnitt============================================

  

}

void freedomSetup()
{
  freedom.setFarbe(255,255,255);
  freedom.setBrightness(255);
  
  freedomArray[0] = new ElementDoBlink                    (random(250), 3);
  freedomArray[1] = new ElementDoBlink                    (random(250), 3);
  freedomArray[2] = new ElementDoBlink                    (random(250), 3);
  freedomArray[3] = new ElementDoBlink                    (random(250), 3);
  freedomArray[4] = new ElementDoPulseDown                (125, pulseFULL);
  freedomArray[5] = new ElementDoSetColor                 ();
  freedomArray[6] = new ElementDoSetTargetColor           (&ring);
  freedomArray[7] = new ElementDoNothing                  (random(1500));
  freedomArray[8] = new ElementDoPulseUp                  (random(10), pulseFULL);
  freedomArray[9] = new ElementDoGoToColor                (15, goToColorFULL);
  freedomArray[10] = new ElementDoSetTargetColor          (&raute, &ring, 2);
  freedomArray[11] = new ElementDoGoToColor               (20, goToColorFULL);
  freedomArray[12] = new ElementDoNothing                 (10000);
  freedomArray[13] = new ElementDoPulseDown               (random(80,300), pulseFULL);
  freedomArray[14] = new ElementDoNothing                 (1);
  freedomArray[15] = new ElementDoNothing                 (1);
  freedomArray[16] = new ElementDoNothing                 (1);
  freedomArray[17] = new ElementDoNothing                 (1);
  freedomArray[18] = new ElementDoNothing                 (1);
  freedomArray[19] = new ElementDoNothing                 (1);
  freedomArray[20] = new ElementDoNothing                 (1);
  freedomArray[21] = new ElementDoNothing                 (1);

  //====================2. Abschnitt============================================
  
  freedomArray[22] = new ElementDoPulseUp               (1, pulseFULL);
  freedomArray[23] = new ElementDoPulseDown             (1, pulseFULL);
  freedomArray[24] = new ElementDoPulseUp               (2, pulseFULL*0.5);
  freedomArray[25] = new ElementDoPulseDown             (2, pulseFULL*0.5);
  freedomArray[26] = new ElementDoNothing               (800);

  
  setArrayFunctionElement(freedomArray, &freedom, ARRAY_SIZE);
  setArrayObservers(freedomArray, ARRAY_SIZE);
  freedomArray[22]->activate();
  
  freedomArray[3]->deleteObserver();                       //wird von letArray[4] gesetzt
  freedomArray[4]->setObserver(letArray[5], 0);            //let und ring sollen ganz runter pulsen
  freedomArray[4]->setObserver(ringArray[5], 1);
  freedomArray[5]->deleteObserver();
  freedomArray[10]->setObserver(letArray[11], 0);
  
  //====================2. Abschnitt============================================
  

}

void ringSetup()
{
  ring.setFarbe(255,255,255);
  ring.setBrightness(255);
  
  ringArray[0] = new ElementDoBlink                    (random(250), 3);
  ringArray[1] = new ElementDoBlink                    (random(250), 3);
  ringArray[2] = new ElementDoBlink                    (random(250), 3);
  ringArray[3] = new ElementDoBlink                    (random(250), 3);
  ringArray[4] = new ElementDoPulseDown                (75, pulseFULL*0.9);
  ringArray[5] = new ElementDoPulseDown                (100, pulseFULL*0.11);
  ringArray[6] = new ElementDoSetColor                 ();
  ringArray[7] = new ElementDoSetTargetColor           (&raute);
  ringArray[8] = new ElementDoNothing                  (random(1500));
  ringArray[9] = new ElementDoPulseUp                  (random(10), pulseFULL);
  ringArray[10] = new ElementDoGoToColor               (15, goToColorFULL);
  ringArray[11] = new ElementDoSetTargetColor          ("hart");
  ringArray[12] = new ElementDoGoToColor               (20, goToColorFULL);
  ringArray[13] = new ElementDoNothing                 (10000);
  ringArray[14] = new ElementDoPulseDown               (random(80,300), pulseFULL);
  ringArray[15] = new ElementDoNothing                 (1);
  ringArray[16] = new ElementDoNothing                 (1);
  ringArray[17] = new ElementDoNothing                 (1);
  ringArray[18] = new ElementDoNothing                 (1);
  ringArray[19] = new ElementDoNothing                 (1);
  ringArray[20] = new ElementDoNothing                 (1);
  ringArray[21] = new ElementDoNothing                 (1);
  
  //====================2. Abschnitt============================================
  
  ringArray[22] = new ElementDoPulseUp               (1, pulseFULL);
  ringArray[23] = new ElementDoPulseDown             (1, pulseFULL);
  ringArray[24] = new ElementDoPulseUp               (2, pulseFULL*0.5);
  ringArray[25] = new ElementDoPulseDown             (2, pulseFULL*0.5);
  ringArray[26] = new ElementDoNothing               (800);

  setArrayFunctionElement(ringArray, &ring, ARRAY_SIZE);
  setArrayObservers(ringArray, ARRAY_SIZE);
  ringArray[22]->activate();
  
  ringArray[4]->setObserver(freedomArray[4], 0);        //freedom soll ganz runter pulsen
  ringArray[5]->setObserver(rauteArray[4], 0);          //raute blinksequenz startet
  ringArray[6]->deleteObserver();
  ringArray[11]->setObserver(freedomArray[10], 0);
  
  //====================2. Abschnitt============================================

}



int main(void)
{
	init();
	setup();
	for (;;)
		loop();

	return 0; // must NEVER be reached
}
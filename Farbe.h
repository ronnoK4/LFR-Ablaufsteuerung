/* 
 * File:   Farbe.h
 * Author: ronno
 *
 * Created on 21. November 2013, 07:56
 */

#ifndef FARBE_H
#define	FARBE_H

class Farbe
{
  public:
    int rot;
    int gruen;
    int blau;
    double brightness;
    
    Farbe();
    void randomColor();
    void hardRandomColor();
    void printFarbe();
};

#endif	/* FARBE_H */


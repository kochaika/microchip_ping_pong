#ifndef __DEFINITIONS_H
#define __DEFINITIONS_H

#include <p18f4520.h>
#include <delays.h>   
#include <timers.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "LCD.h"
#include "EEPROM.h"
//#include "ballImg.h"

#define EEPROM_ADDR     0
#define BUTTONS_PORT 	PORTB
#define KEY_DELAY 7

struct Coordinate
{
	unsigned int x;
	unsigned int y;
};

extern struct Coordinate ballCentre = {120,160};
extern unsigned int ballRaduis = 4;

extern unsigned int leftBorder = 5;
extern unsigned int rightBorder = 235; //240-5
extern unsigned int upBorder = 5;
extern unsigned int downBorder = 315; //320-5

extern unsigned int upRacketCentre = 120;
extern unsigned int upRacketIndent = 5 + 5;
extern unsigned int upRacketWidth = 35;

extern unsigned int downRacketCentre = 120;
extern unsigned int downRacketIndent = 315 - 5;
extern unsigned int downRacketWidth = 35;

extern unsigned int colorBlack = 0b0000000000000000;
extern unsigned int colorWhite = 0b1111111111111111;

/**
* Status of current game
* 0 - Game 
* 1 - Loss
* 2 - Win
*/
extern unsigned char gameStatus;
#endif
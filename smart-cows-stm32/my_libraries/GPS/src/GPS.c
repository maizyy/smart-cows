/*
 * GPS.c
 *
 *  Created on: May 18, 2022
 *      Author: Jogn
 */

#include <GPS.h>
#include <stdlib.h>
#include "adc.h"


Position* GPS_getCurrentPosition()
{
	Position *currentPosition = (Position*) malloc(sizeof(float)*2);
	currentPosition->latitude = 10;
	currentPosition->longitude = 15;
	return currentPosition;
}



/*
 * GPS.c
 *
 *  Created on: May 18, 2022
 *      Author: Jogn
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <GPS.h>

#define GPGLL "$GPGLL"


uint8_t gpsDataReady = 0;

static char messageBuffer[80] = {};
static uint8_t mess_index = 0;
Position currentPosition = {0,0};

/*
 * private functions
 */
static uint8_t validateMessage();
static int parseGPGLLSentence();
static float changeCordsToDec(float deg_coord, char nsew);

static uint8_t validateMessage()
{

	return (messageBuffer[0] == '$' &&
		messageBuffer[1] == 'G' &&
		messageBuffer[2] == 'P' &&
		messageBuffer[3] == 'G' &&
		messageBuffer[4] == 'L' &&
		messageBuffer[5] == 'L');

}

static int parseGPGLLSentence()
{
	float lat = 0;
	float lon = 0;
    char sn, we;
	sscanf(messageBuffer, "$GPGLL,%f,%c,%f,%c", &lat, &sn, &lon, &we);
	currentPosition.latitude = (float) changeCordsToDec(lat, sn);
	currentPosition.longitude = (float) changeCordsToDec(lon, we);
	return (currentPosition.latitude != 0 && currentPosition.longitude != 0);
}

static float changeCordsToDec(float deg_coord, char nsew) {
    int degree = (int)(deg_coord/100);
    float minutes = deg_coord - degree*100;
    float dec_deg = minutes / 60;
    float decimal = degree + dec_deg;
    if (nsew == 'S' || nsew == 'W')
    {
        decimal *= -1;
    }
    return decimal;
}


/*
 * public functions
 */

void GPS_Init(uint8_t *rxData)
{
	gpsDataReady = 0;
	HAL_UART_Receive_IT(GPS_USART, (uint8_t *) &rxData, 1);
}


void GPS_UART_Callback(uint8_t *rxData)
{

	if(mess_index == 0 && *rxData == '$')
	{
		messageBuffer[mess_index] = *rxData;
		++mess_index;
	}
	else if (mess_index >= 1 && mess_index < sizeof(messageBuffer))
	{
		if(*rxData == '\n' || *rxData == '\r')
		{
			messageBuffer[mess_index] = '\0';
			if(validateMessage())
			{
				if (parseGPGLLSentence())
					gpsDataReady = 1;
			}
			mess_index = 0;
			memset(messageBuffer, 0 , sizeof(messageBuffer));
		}
		else
		{
			messageBuffer[mess_index] = *rxData;
			++mess_index;
		}
	}
	else
	{
		mess_index = 0;
	}

	if(gpsDataReady == 0)
	{
		HAL_UART_Receive_IT(GPS_USART, (uint8_t *) rxData, 1);
	}
}


void GPS_getCurrentPosition(Position *const position)
{
	memcpy(position, &currentPosition, sizeof(Position));
	gpsDataReady = 0;
}


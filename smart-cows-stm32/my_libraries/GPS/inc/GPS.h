/*
 * GPS.h
 *
 *  Created on: May 18, 2022
 *      Author: Jogn
 */

#ifndef GPS_GPS_H_
#define GPS_GPS_H_

#include <usart.h>
#define GPS_USART &huart3

typedef struct {
	float latitude;
	float longitude;
} Position;

// This global variable determines whether GPS data is ready for transmission
extern uint8_t gpsDataReady;


void GPS_Init(uint8_t *rxData);

void GPS_UART_Callback(uint8_t *rxData);

void GPS_getCurrentPosition(Position *const position);


#endif /* GPS_GPS_H_ */

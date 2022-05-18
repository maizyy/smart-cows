/*
 * GPS.h
 *
 *  Created on: May 18, 2022
 *      Author: Jogn
 */

#ifndef GPS_GPS_H_
#define GPS_GPS_H_


typedef struct {
	float latitude;
	float longitude;
} Position;


Position* GPS_getCurrentPosition();


#endif /* GPS_GPS_H_ */

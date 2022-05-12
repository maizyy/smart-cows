#ifndef Battery_3_7_h
#define Battery_3_7_h

#include "adc.h"

	void BATTERY_Init(ADC_HandleTypeDef* hadc, uint32_t timeout);
	double BATTERY_GetBatteryVolts();
	int BATTERY_GetBatteryChargeLevel();

#endif

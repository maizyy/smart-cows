#ifndef Battery_3_7_h
#define Battery_3_7_h

#include "adc.h"

	void battery_init(ADC_HandleTypeDef* hadc, uint32_t timeout);

	int battery_getBatteryChargeLevel(void);

	float battery_getBatteryVolts(void);

#endif

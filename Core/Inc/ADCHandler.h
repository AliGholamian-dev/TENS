#ifndef __ADCHANDLER_H
#define __ADCHANDLER_H

#include "stdint.h"

void initADC(void);
void startADC(void);

float getVref(void);
float convertToVoltage(uint16_t adcValue);
float convertToMilliVolts(float voltage);
float getChannel1Current(void);
float getChannel2Current(void);
float getHighVoltage(void);
float getBatteryVoltage(void);
float getChargerCurrent(void);
float getCpuTemp(void);

#endif /* __ADCHANDLER_H */

#ifndef __WAVEGENERATOR_H
#define __WAVEGENERATOR_H

#include "WaveGeneratorTypes.h"

void turnOff(void);
void turnOn(const WaveConfig* waveConfig);
void initPWM(void);
void watchOverHighVoltage(void);

#endif /* __WAVEGENERATOR_H */

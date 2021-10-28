#ifndef __WAVEGENERATORTYPES_H
#define __WAVEGENERATORTYPES_H

typedef float DutyCycle;
typedef float Hz;
typedef float Intensity;

typedef struct WaveConfig {
	Hz frequency;
	DutyCycle dutyCycle_percent;
	Intensity maxVoltage;
} WaveConfig;

#endif /* __WAVEGENERATORTYPES_H */

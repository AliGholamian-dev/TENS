#include "ADCHandler.h"
#include "dma.h"
#include "adc.h"

uint16_t adcValues[7] = {0, 0, 0, 0, 0, 0, 0};
static const float OUTPUT_RESITOR_VALUE = 100.00;

void initADC() {
	MX_DMA_Init();
	MX_ADC_Init();
	HAL_ADCEx_Calibration_Start(&hadc);
}
void startADC() {
	HAL_ADC_Start_DMA(&hadc, (uint32_t*)adcValues, 7);
}

float getVref() {
	static const uint32_t* VREFINT_CAL_ADDR = (uint32_t*)0x1FFFF7BA;
	const uint16_t VREFINT_CAL  = *((uint16_t*) VREFINT_CAL_ADDR);
	return 3.3 * VREFINT_CAL / adcValues[6];
}

float convertToVoltage(uint16_t adcValue) {
	static const float ADC_MAX = 4095.00;
	return adcValue / ADC_MAX * getVref();
}

float convertToMilliVolts(float voltage) {
	return voltage * 1000;
}

float getChannel1Current() {
	return convertToMilliVolts(convertToVoltage(adcValues[0])) / OUTPUT_RESITOR_VALUE;
}

float getChannel2Current() {
	return convertToMilliVolts(convertToVoltage(adcValues[1])) / OUTPUT_RESITOR_VALUE;
}

float getHighVoltage() {
	static const float RESITOR_DIVISION_RATIO = 22.7;
	return convertToVoltage(adcValues[2]) * RESITOR_DIVISION_RATIO;
}

float getBatteryVoltage() {
	return convertToVoltage(adcValues[3]);
}

float getChargerCurrent() {
	return convertToMilliVolts(convertToVoltage(adcValues[4])) / OUTPUT_RESITOR_VALUE;
}
float getCpuTemp() {
	static const uint32_t* TS_CAL_ADDR = (uint32_t*)0x1FFFF7B8;
	const uint16_t TS_CAL  = *((uint16_t*) TS_CAL_ADDR);
	return 850 + ((TS_CAL - adcValues[5]) * 10 / 4 );
}

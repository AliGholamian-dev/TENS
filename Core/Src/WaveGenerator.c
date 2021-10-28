#include "WaveGenerator.h"
#include "ADCHandler.h"
#include "tim.h"

static const uint16_t converterCompareValue = 200;
static float maxVoltage;

void turnOff(void) {
	__HAL_TIM_SetCompare(&htim1, TIM_CHANNEL_1, 0);
	__HAL_TIM_SetCompare(&htim14, TIM_CHANNEL_1, 0);
	
	HAL_TIM_PWM_Stop(&htim14, TIM_CHANNEL_1);
	HAL_TIM_PWM_Stop(&htim1, TIM_CHANNEL_1);
	
	__HAL_TIM_SetCompare(&htim1, TIM_CHANNEL_1, 0);
	__HAL_TIM_SetCompare(&htim14, TIM_CHANNEL_1, 0);
}

void turnOn(const WaveConfig* waveConfig) {
	static const float _1HzPrs    = 10000.00;
	static const float maxCompare = 4800.00;
	turnOff();
	maxVoltage = 0.00;
	
	HAL_TIM_PWM_Start(&htim14, TIM_CHANNEL_1);
	__HAL_TIM_SetCompare(&htim14, TIM_CHANNEL_1, converterCompareValue);
	
	if(waveConfig->frequency > 0) {
		uint16_t prs  = (_1HzPrs / waveConfig->frequency) - 1;
		uint16_t comp = (waveConfig->dutyCycle_percent * maxCompare) - 1;
		maxVoltage = waveConfig->maxVoltage;
		
		__HAL_TIM_SET_PRESCALER(&htim1, prs);
			HAL_TIM_PWM_Start(&htim1, TIM_CHANNEL_1);
		__HAL_TIM_SetCompare(&htim1, TIM_CHANNEL_1, comp);
	}
	else
		turnOff();
}

void initPWM(void) {
	MX_TIM1_Init();
  MX_TIM14_Init();
  MX_TIM16_Init();
  MX_TIM17_Init();
  MX_TIM3_Init();
}

void watchOverHighVoltage(void) {
	if (getHighVoltage() > maxVoltage) {
		__HAL_TIM_SetCompare(&htim14, TIM_CHANNEL_1, 0);
	}
	else {
		__HAL_TIM_SetCompare(&htim14, TIM_CHANNEL_1, converterCompareValue);
	}
}

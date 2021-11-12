#include "MenuHandler.h"
#include "ButtonReader.h"
#include "WaveGenerator.h"
#include "i2c.h"
#include "stdio.h"
#include "ssd1306.h"
#include "stdbool.h"

typedef enum MenuState { 
	startTherapy = 0,
	intensitySelection = 1, 
	intervalSelection = 2,
	dutyCycleSelection = 3,
	maxIndex = 3,
	homeScreen = 4,
} MenuState; 

static char menuTitles[maxIndex + 1][50] = 
{
	"Start Therapy",
	"Intensity(V)",
	"Interval(Hz)",
	"Duty Cycle(%)"
};
static char lcdStringBuffer[50];
static MenuState highlightedIndex = startTherapy;
static MenuState menuState = homeScreen;
static WaveConfig waveConfig = {0.5, 0.5, 25};

bool firstTimeEnter = true;

///Private Functions -> Declaration not available in header file
void handleSelectedIndex(KeyType pressedKey) {
	if(menuState == homeScreen) {
		if(pressedKey == down) {
			highlightedIndex++;
			if (highlightedIndex > maxIndex)
				highlightedIndex = 0;
		}
		else if(pressedKey == up) {
			if (highlightedIndex == 0)
				highlightedIndex = 3;
			else 
				highlightedIndex--;
		}
	}
}

void handleConfiremedIndex(KeyType pressedKey) {
	if(pressedKey == confirm) {
		if(menuState == homeScreen) {
			menuState = highlightedIndex;
		}
		else {
			menuState = homeScreen;
			turnOff();
		}
	}
}

void handleValueChange(KeyType pressedKey, float* value, float min, float max, float step) {
	if(pressedKey == right) {
		(*value) += step;
		if((*value) >= max)
			(*value) = max;
	}
	else if(pressedKey == left) {
		(*value) -= step;
		if((*value) <= min)
			(*value) = min;
	}
}
float getCurrentIndexValue(uint8_t index) {
	float value = 0.00;
		switch (index)
    {
    	case intensitySelection:
				value = waveConfig.maxVoltage;
    		break;
    	case intervalSelection:
				value = waveConfig.frequency;
    		break;
    	case dutyCycleSelection:
				value = waveConfig.dutyCycle_percent * 100.00;
    		break;
    	default:
				value = 0.0;
    		break;
    }
		return value;
}

void showStartTherapy(void) {
	ssd1306_SetCursor(0, 0);
	ssd1306_WriteString("Press OK to stop", &Font_7x10, White);
	ssd1306_SetCursor(8, 20);
	ssd1306_WriteString("Started", &Font_16x26, White);
	turnOn(&waveConfig);
	watchOverHighVoltage();
}

void showIntensitySelectionScreen(KeyType pressedKey) {
	static const Intensity maxPossibleVoltage = 60;
	handleValueChange(pressedKey, &waveConfig.maxVoltage, 20, maxPossibleVoltage, 1);
	ssd1306_SetCursor(0, 0);
	ssd1306_WriteString("Select Intensity", &Font_7x10, White);
	ssd1306_DrawCircle(64, 32, 22, White);
	ssd1306_SetCursor(53,23);
	sprintf(lcdStringBuffer, "%2u", (uint8_t)waveConfig.maxVoltage);
	ssd1306_WriteString(lcdStringBuffer, &Font_11x18, White);
	ssd1306_DrawRectangle(0, 58, (waveConfig.maxVoltage / maxPossibleVoltage) * SSD1306_WIDTH, 63, White);
}

void showIntervalSelectionScreen(KeyType pressedKey) {
	static const Hz maxPossibleFreq = 5;
	static const Hz minPossibleFreq = 0.1;
	handleValueChange(pressedKey, &waveConfig.frequency, minPossibleFreq, maxPossibleFreq, 0.1);
	ssd1306_SetCursor(0, 0);
	ssd1306_WriteString("Select Interval", &Font_7x10, White);
	ssd1306_SetCursor(47,23);
	sprintf(lcdStringBuffer, "%1.1f", waveConfig.frequency);
	ssd1306_WriteString(lcdStringBuffer, &Font_11x18, White);
}

void showDutyCycleSelectionScreen(KeyType pressedKey) {
	static const DutyCycle maxPossibleDutyCycle = 1;
	handleValueChange(pressedKey, &waveConfig.dutyCycle_percent, 0, maxPossibleDutyCycle, 0.01);
	ssd1306_SetCursor(0, 0);
	ssd1306_WriteString("Select DutyCycle", &Font_7x10, White);
	ssd1306_DrawCircle(64, 32, 22, White);
	ssd1306_SetCursor(53,23);
	sprintf(lcdStringBuffer, "%2u", (uint8_t)(waveConfig.dutyCycle_percent * 100));
	ssd1306_WriteString(lcdStringBuffer, &Font_11x18, White);
	ssd1306_DrawRectangle(0, 58, (waveConfig.dutyCycle_percent / maxPossibleDutyCycle) * SSD1306_WIDTH, 63, White);
}

void showHomeScreen(void) {
	for(int i = 0; i < (maxIndex + 1); i++)
  {
		SSD1306_COLOR color = White;
		if(highlightedIndex == i)
			color = Black;
		ssd1306_SetCursor(0, i * 15);
		sprintf(lcdStringBuffer, "%s", menuTitles[i]);
		ssd1306_WriteString(lcdStringBuffer, &Font_7x10, color);
		if(i != startTherapy) {
			ssd1306_SetCursor(91, i * 15);
			float value = getCurrentIndexValue(i);
			sprintf(lcdStringBuffer, "%-2.2f", value);
			ssd1306_WriteString(lcdStringBuffer, &Font_7x10, color);
		}
  }
}

///Public Functions -> Declaration available in header file
void initDisplay(void) {
	MX_I2C1_Init();
	ssd1306_Init();
	waveConfig.maxVoltage 			 = 25.0;
	waveConfig.frequency         = 0.50;
	waveConfig.dutyCycle_percent = 0.50;
}
	
void showWelcomePage(void) {
	ssd1306_Fill(Black);
	ssd1306_SetCursor(32, 20);
  ssd1306_WriteString("TENS", &Font_16x26, White);
	ssd1306_UpdateScreen();
	ssd1306_Fill(Black);
  HAL_Delay(4000);
	ssd1306_UpdateScreen();
}

void handleMenu(void) {
	if(getKeyState() == pressed || firstTimeEnter) {
		firstTimeEnter = false;
		KeyType pressedKey = getPressedKey();
		handleSelectedIndex(pressedKey);
		handleConfiremedIndex(pressedKey);
		ssd1306_Fill(Black);
		switch (menuState)
    {
    	case startTherapy:
				showStartTherapy();
    		break;
    	case intensitySelection:
				showIntensitySelectionScreen(pressedKey);
    		break;
    	case intervalSelection:
				showIntervalSelectionScreen(pressedKey);
    		break;
    	case dutyCycleSelection:
				showDutyCycleSelectionScreen(pressedKey);
    		break;
    	case homeScreen:
				showHomeScreen();
    		break;
    	default:
				turnOff();
				menuState = homeScreen;
				highlightedIndex = 0;
    		break;
    }
		ssd1306_UpdateScreen();
		while(getKeyState() == pressed) {
			getPressedKey();
			watchOverHighVoltage();
		}
	}
}

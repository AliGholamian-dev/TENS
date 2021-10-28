#include "ButtonReader.h"
#include "main.h"

static KeyState keyPressed = notPressed;
static KeyType  pressedKey = none;

KeyState getKeyState(void) {
	return keyPressed;
}

void setPressedKey(uint16_t GPIO_Pin) {
	keyPressed = pressed;
  if(GPIO_Pin == Button3_Pin)
		pressedKey = confirm;
	else if(GPIO_Pin == Button1_Pin)
		pressedKey = right;
	else if(GPIO_Pin == Button2_Pin)
		pressedKey = left;
	else if(GPIO_Pin == Button4_Pin)
		pressedKey = down;
	else if(GPIO_Pin == Button5_Pin)
		pressedKey = up;
	else {
		pressedKey = none;
		keyPressed = notPressed;
	}
}

KeyType getPressedKey(void) {
	keyPressed = notPressed;
	KeyType pressedKey_copy = pressedKey;
	pressedKey = none;
	return pressedKey_copy;
}

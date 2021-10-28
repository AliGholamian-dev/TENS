#ifndef __BUTTONREADER_H
#define __BUTTONREADER_H

#include "ButtonReaderTypes.h"

KeyState getKeyState(void);
void     setPressedKey(uint16_t GPIO_Pin);
KeyType  getPressedKey(void);

#endif /* __BUTTONREADER_H */

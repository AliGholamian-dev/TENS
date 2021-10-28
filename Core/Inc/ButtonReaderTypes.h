#ifndef __BUTTONREADERTYPES_H
#define __BUTTONREADERTYPES_H

#include "stdint.h"

typedef enum KeyType {
	confirm = 0,  
	left = 1,
	right = 2,  
	up = 3,
	down = 4,
	none = 5
} KeyType; 

typedef enum KeyState { 
	notPressed = 0,
	pressed = 1, 
} KeyState;

#endif /* __BUTTONREADERTYPES_H */

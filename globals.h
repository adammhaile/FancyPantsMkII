#include "Arduino.h"

#define MENU_SIZE 10
#define MAX_MENU (MENU_SIZE-1)
#define MENU_SIDE 1

const __FlashStringHelper * menu(uint8_t i)
{
	static const __FlashStringHelper * menu[MENU_SIZE] = 
	{
		F("1234567890"),
		F("Rainbow"),
		F("Party!"),
		F("Go To 11"),
		F("Testing"),
		F("Max Power"),
		F("Flower"),
		F("Bloom"),
		F("Blinder"),
		F("Hello!"),
	};

	return menu[i];
}

int8_t curMenu = 0;
int8_t dispMenu = 0;

long oldEnc = 0;

volatile unsigned long lastButton = 0;
#define DEBOUNCE_TIME 250

volatile bool buttonPressed = false;

uint8_t pressCount = 0;

int freeRam () 
{
  extern int __heap_start, *__brkval; 
  int v; 
  return (int) &v - (__brkval == 0 ? (int) &__heap_start : (int) __brkval); 
}
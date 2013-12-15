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

volatile unsigned long lastSelect = 0;
volatile unsigned long lastOverride = 0;
#define DEBOUNCE_TIME 250

volatile bool selected = false;
volatile bool overridden = false;

uint8_t pressCount = 0;

unsigned long overrideRef = 0;
volatile int8_t countdown = 0;
#define OVERRIDE_TIME 15

int freeRam () 
{
  extern int __heap_start, *__brkval; 
  int v; 
  return (int) &v - (__brkval == 0 ? (int) &__heap_start : (int) __brkval); 
}

//Helper for time delays without actually pausing execution
bool TimeElapsed(unsigned long ref, unsigned long wait)
{
	static unsigned long now = 0;
	now = millis();

	if(now < ref || ref == 0) //for the 50 day rollover or first boot
		return true;  

	if((now - ref) > wait)
		return true;
	else
		return false;
}
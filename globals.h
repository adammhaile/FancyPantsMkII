#include "Arduino.h"

#include "Adafruit_GFX.h"
#include "Adafruit_SSD1306.h"

#include "Encoder.h"

#include "strip_util.h"

#define ENCODER_A 10
#define ENCODER_B 9
Encoder encoder(ENCODER_A, ENCODER_B);

#define OLED_RESET 15
Adafruit_SSD1306 display(OLED_RESET);

#if (SSD1306_LCDHEIGHT != 64)
#error("Height incorrect, please fix Adafruit_SSD1306.h!");
#endif

#define ENCODER_BTN_PIN 2
#define ENCODER_BTN_INT 2
#define OVER_BTN_PIN 11
#define OVER_BTN_INT 1

#define MENU_SIZE 3
#define MAX_MENU (MENU_SIZE-1)
#define MENU_SIDE 1

const __FlashStringHelper * menu(uint8_t i)
{
	static const __FlashStringHelper * menu[MENU_SIZE] = 
	{
		F("Animations"),
		F("Brightness"),
		F("DON'T PRESS"),
	};

	return menu[i];
}

uint8_t maxMenu = MAX_MENU;
uint8_t menuSize = MENU_SIZE;

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
#define OVERRIDE_TIME 5

#define MENU_HOME	0
#define MENU_ANIM	1
#define MENU_BRIGHT	2

volatile uint8_t menuLevel = MENU_HOME;

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
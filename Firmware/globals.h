#ifndef GLOBALS_H
#define GLOBALS_H

#include "Arduino.h"

#include "Adafruit_GFX.h"
#include "Adafruit_SSD1306.h"
#include "Adafruit_NeoPixel.h"

#include "arrays.h"

#include "Encoder.h"

#define NEO_A_PIN 0 //PB0
#define NEO_A_NUM 42 * 6
#define NEO_B_PIN 1 //PB1
#define NEO_B_NUM (42 * 6) - 2 //oops, lost a couple pixels
#define NUM_PIXELS (NEO_A_NUM + NEO_B_NUM)
#define NUM_X 12
#define NUM_Y 42
Adafruit_NeoPixel stripA = Adafruit_NeoPixel(NEO_A_NUM, NEO_A_PIN, NEO_GRB + NEO_KHZ800);
Adafruit_NeoPixel stripB = Adafruit_NeoPixel(NEO_B_NUM, NEO_B_PIN, NEO_GRB + NEO_KHZ800);

void ledShow() 
{
	stripA.show();
	stripB.show();
}

void setPixelColor(uint8_t x, uint8_t y, uint32_t c)
{
	if(x < NUM_X && y < NUM_Y)
	{
		if(x < 6)
			stripA.setPixelColor(_pixels[y][x], c);
		else
		{
			stripB.setPixelColor(_pixels[y][x], c);
		}
	}
}

uint8_t _brightness = 25;
#define MIN_BRIGHT 10
uint8_t _brightPercent = 10;


#define C(r, g, b) ((uint32_t)r << 16) | ((uint32_t)g <<  8) | b

#define C_OFF		C(0,0,0)
#define C_WHITE		C(255,255,255)

#define C_RED		C(255, 0, 0)
#define C_ORANGE	C(255, 75, 0)
#define C_YELLOW	C(255, 255, 0)
#define C_GREEN		C(0, 255, 0)
#define C_BLUE		C(0, 0, 255)
#define C_VIOLET	C(143, 0, 255)

#define WHEEL_MAX 384

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
volatile bool updateDisplay = true;

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


#endif
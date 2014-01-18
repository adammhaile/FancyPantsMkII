#include "Adafruit_NeoPixel.h"

uint8_t _brightness = 25;
#define MIN_BRIGHT 10
uint8_t _brightPercent = 10;

#define NEO_A_PIN 1
#define NEO_A_NUM 42 * 6
Adafruit_NeoPixel strip = Adafruit_NeoPixel(NEO_A_NUM, NEO_A_PIN, NEO_GRB + NEO_KHZ800);

uint32_t C(uint8_t r, uint8_t g, uint8_t b) {
	return ((uint32_t)r << 16) | ((uint32_t)g <<  8) | b;
}

#define C_OFF		C(0,0,0)
#define C_WHITE		C(255,255,255)
#define C_RED		C(255,0,0)
#define C_GREEN		C(0,255,0)
#define C_BLUE		C(0,0,255)

void ledShow() {
	strip.show();
}
void colorFill(uint32_t c) {
	for(uint16_t i=0; i<strip.numPixels(); i++) {
		strip.setPixelColor(i, c);
	}
}
void setBrightness(uint8_t level) { 
	strip.setBrightness(level);
}
void allOff() {
	colorFill(C_OFF);
}

//Input a value 0 to cycle_max to get a color value.
//The colours are a transition r - g -b - back to r
uint32_t Wheel(uint16_t WheelPos)
{
	byte r, g, b;
	switch(WheelPos / 128)
	{
	case 0:
		r = 127 - WheelPos % 128;   //Red down
		g = WheelPos % 128;      // Green up
		b = 0;                  //blue off
		break; 
	case 1:
		g = 127 - WheelPos % 128;  //green down
		b = WheelPos % 128;      //blue up
		r = 0;                  //red off
		break; 
	case 2:
		b = 127 - WheelPos % 128;  //blue down 
		r = WheelPos % 128;      //red up
		g = 0;                  //green off
		break; 
	}

	r *= 2;
	g *= 2;
	b *= 2;

	return(C(r,g,b));
}

///Animations Here
uint16_t curStep = 0;
uint16_t oldStep = 0;
uint8_t  curAnim = 1;
uint8_t  oldAnim = 1;
void rainbowCycle() {
	static uint16_t i;
	for(i=0; i< strip.numPixels(); i++) {
		strip.setPixelColor(i, Wheel(((i * 256 / strip.numPixels()) + curStep) & 255));
	}
	if(curStep >= 256)
		curStep = 0;
}

void fullRainbow() {
	colorFill(Wheel(curStep & 255));
	if(curStep >= 256)
		curStep = 0;
}

uint32_t wipeColor = C_GREEN;
void colorWipe() {
	static uint16_t i;
	for(i=0; i< curStep; i++) {
		strip.setPixelColor(i, wipeColor);
	}

	if(curStep >= strip.numPixels())
	{
		allOff();
		curStep = 0;
	}
}

void max_overload(){
	if((curStep/4) % 2)
		colorFill(C_OFF);
	else
		colorFill(C_WHITE);
}
///End Animations
#define ANIM_SIZE 4
#define ANIM_MAX (ANIM_SIZE-1)

typedef void (* animPtr)();
animPtr anims[] = {
	max_overload,
	rainbowCycle,
	fullRainbow,
	colorWipe,
};

const __FlashStringHelper * animNames(uint8_t i)
{
	static const __FlashStringHelper * anims[ANIM_SIZE] = 
	{
		F("<< BACK"),
		F("RainbowCycle"),
		F("FullRainbow"),
		F("ColorWipe"),
	};

	return anims[i];
}

void stripInit()
{
	strip.begin();
	strip.setBrightness(_brightness);
	ledShow();
}
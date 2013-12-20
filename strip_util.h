#include "Adafruit_NeoPixel.h"

#define NEO_A_PIN 0
#define NEO_A_NUM 120
Adafruit_NeoPixel strip = Adafruit_NeoPixel(NEO_A_NUM, NEO_A_PIN, NEO_GRB + NEO_KHZ800);

uint32_t C(uint8_t r, uint8_t g, uint8_t b) {
	return ((uint32_t)r << 16) | ((uint32_t)g <<  8) | b;
}

#define C_OFF		C(0,0,0)
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

void rainbowCycle() {
	static uint16_t i;
	for(i=0; i< strip.numPixels(); i++) {
		strip.setPixelColor(i, Wheel(((i * 256 / strip.numPixels()) + curStep) & 255));
	}
	if(curStep >= 256)
		curStep = 0;
}
///End Animations

void stripInit()
{
	strip.begin();
	strip.setBrightness(32);
	ledShow();
}
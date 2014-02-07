#include "arrays.h"
#include "globals.h"
#include "text_util.h"

uint32_t _rainbow[] =
{
	C_RED,
	C_ORANGE,
	C_YELLOW,
	C_GREEN,
	C_BLUE,
	C_VIOLET,
};

void colorFill(uint32_t c) {
	for(uint8_t x=0; x<NUM_X; x++)
		for(uint8_t y=0; y<NUM_Y; y++)
			setPixelColor(x, y, c);
}

void setBrightness(uint8_t level) { 
	stripA.setBrightness(level);
	stripB.setBrightness(level);
}

void allOff() {
	colorFill(C_OFF);
}

static uint8_t _x, _y;

////Input a value 0 to cycle_max to get a color value.
////The colours are a transition r - g -b - back to r
//uint32_t Wheel(uint16_t WheelPos)
//{
//	byte r, g, b;
//	switch(WheelPos / 128)
//	{
//	case 0:
//		r = 127 - WheelPos % 128;   //Red down
//		g = WheelPos % 128;      // Green up
//		b = 0;                  //blue off
//		break; 
//	case 1:
//		g = 127 - WheelPos % 128;  //green down
//		b = WheelPos % 128;      //blue up
//		r = 0;                  //red off
//		break; 
//	case 2:
//		b = 127 - WheelPos % 128;  //blue down 
//		r = WheelPos % 128;      //red up
//		g = 0;                  //green off
//		break; 
//	}
//
//	r *= 2;
//	g *= 2;
//	b *= 2;
//
//	return(C(r,g,b));
//}

//Helper to for the wheel calc
static uint32_t wheelHelper(uint16_t pos, uint16_t cycle_step, uint8_t length)
{
  return Wheel( ((pos * (WHEEL_MAX+1) / length) + cycle_step) & WHEEL_MAX);
}

///Animations Here
uint16_t curStep = 0;
uint16_t oldStep = 0;
uint8_t  curAnim = 1;
uint8_t  oldAnim = 1;
void rainbowCycle() {
	//static uint16_t i;
	//for(i=0; i< strip.numPixels(); i++) {
	//	strip.setPixelColor(i, Wheel(((i * 256 / strip.numPixels()) + curStep) & 255));
	//}
	//if(curStep >= 256)
	//	curStep = 0;
}

void fullRainbow() {
	colorFill(Wheel(curStep & 255));
	if(curStep >= 256)
		curStep = 0;
}

uint8_t _wipeColor = 0;
void colorWipe() {
	static uint8_t x, y;
	for(x=0; x < NUM_X; x++)
	{
		for(y=0; y<=curStep; y++)
		{
			setPixelColor(x,y, _rainbow[_wipeColor]);
		}
	}

	if(curStep >= NUM_Y)
	{
		allOff();
		curStep = 0;

		_wipeColor++;
		if(_wipeColor >= 6)
			_wipeColor = 0;
	}
}

/*
Looks like a blooming flower
dir = true -> bloom outward
dir = false -> fold inward
*/
void bloom(boolean dir) {
	static uint8_t x, y;
	for(int y=0; y<NUM_Y; y++) 
	{
		for(int x=0; x<NUM_X; x++)
		{
			setPixelColor(x, y, wheelHelper(_vectors[y][x], dir ? WHEEL_MAX - curStep : curStep, NUM_Y));
		}
	}

	if(curStep >= WHEEL_MAX)
		curStep = 0;
}

void bloomOut(){ bloom(true); }
void bloomIn(){ bloom(false); }

void rainbow_h_wipe()
{
	for(_x=0; _x<NUM_X; _x++)
	{
		static uint32_t c;
		c = Wheel((_x * NUM_Y + curStep) % WHEEL_MAX);
		for(_y=0; _y<NUM_Y; _y++)
			setPixelColor(_x, _y, c);
	}

	if(curStep >= WHEEL_MAX)
		curStep = 0;
}

void rainbow_v_wipe()
{
	for(_y=0; _y<NUM_Y; _y++)
	{
		static uint32_t c;
		c = Wheel((_y * NUM_X + curStep) % WHEEL_MAX);
		for(_x=0; _x<NUM_X; _x++)
			setPixelColor(_x, _y, c);
	}

	if(curStep >= WHEEL_MAX)
		curStep = 0;
}

#define OVERLOAD_COUNT 4
uint8_t overloadColors[OVERLOAD_COUNT][3] = 
{
	{255,255,255},
	{255,0,0},
	{0,255,0},
	{0,0,255},
};
uint8_t overloadColor = 0;
bool overloadDir = true;
void max_overload(){
	if(curStep >= 256) 
	{
		overloadDir = !overloadDir;
		if(overloadDir)
		{
			overloadColor++;
			if(overloadColor >= OVERLOAD_COUNT)
				overloadColor = 0;
		}
		curStep = 0;
	}
	static uint8_t r,g,b,brightness;
	brightness = (overloadDir ? curStep : 255 - curStep);
	r = (overloadColors[overloadColor][0] * brightness) >> 8;
    g = (overloadColors[overloadColor][1] * brightness) >> 8;
    b = (overloadColors[overloadColor][2] * brightness) >> 8;
	colorFill(C(r,g,b));
}


void displayText()
{
	static int16_t posA = 41, posB = 41;
	if(curStep > 1) curStep = 0;
	
	if(curStep % 2)
	{
		colorFill(C_OFF); //clear the buffer
		if(drawString(5, posA, C_RED, "DR WHO SUCKS!"))
			posA--;
		else
			posA = 41;

		if(drawString(11, posB, C_GREEN, "BEST IN terms of PANTS!"))
			posB--;
		else
			posB = 41;
	}
}
///End Animations
#define ANIM_SIZE 9
#define ANIM_MAX (ANIM_SIZE-1)

typedef void (* animPtr)();
animPtr anims[ANIM_SIZE] = {
	max_overload,
	rainbowCycle,
	displayText,
	fullRainbow,
	colorWipe,
	rainbow_h_wipe,
	rainbow_v_wipe,
	bloomIn,
	bloomOut
};

uint8_t animStepSize[ANIM_SIZE] = {
	50,//max_overload
	1,//rainbowCycle
	1,//displayText
	2,//fullRainbow
	1,//colorWipe
	4,//rainbow_h_wipe
	4,//rainbow_v_wipe
	1,//bloomIn
	1,//bloomOut
};

const __FlashStringHelper * animNames(uint8_t i)
{
	static const __FlashStringHelper * anims[ANIM_SIZE] = 
	{
		F("<< BACK"),
		F("RainbowCycle"),
		F("Text"),
		F("FullRainbow"),
		F("ColorWipe"),
		F("Rainbow H"),
		F("Rainbow V"),
		F("Bloom In"),
		F("Bloom Out"),
	};

	return anims[i];
}

void stripInit()
{
	stripA.begin();
	stripA.setBrightness(_brightness);
	stripB.begin();
	stripB.setBrightness(_brightness);

	ledShow();
}
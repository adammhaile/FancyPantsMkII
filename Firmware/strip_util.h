#include "Adafruit_NeoPixel.h"
#include "arrays.h"

uint8_t _brightness = 25;
#define MIN_BRIGHT 10
uint8_t _brightPercent = 10;


#define NEO_A_PIN 0 //PB0
#define NEO_A_NUM 42 * 6
#define NEO_B_PIN 1 //PB1
#define NEO_B_NUM 42 * 6
#define NUM_PIXELS (NEO_A_NUM + NEO_B_NUM)
#define NUM_X 12
#define NUM_Y 42
Adafruit_NeoPixel stripA = Adafruit_NeoPixel(NEO_A_NUM, NEO_A_PIN, NEO_GRB + NEO_KHZ800);
Adafruit_NeoPixel stripB = Adafruit_NeoPixel(NEO_B_NUM, NEO_B_PIN, NEO_GRB + NEO_KHZ800);

#define C(r, g, b) ((uint32_t)r << 16) | ((uint32_t)g <<  8) | b

#define C_OFF		C(0,0,0)
#define C_WHITE		C(255,255,255)

#define C_RED		C(255, 0, 0)
#define C_ORANGE	C(255, 127, 0)
#define C_YELLOW	C(255, 255, 0)
#define C_GREEN		C(0, 255, 0)
#define C_BLUE		C(0, 0, 255)
#define C_VIOLET	C(143, 0, 255)

#define WHEEL_MAX 384

uint32_t _rainbow[] =
{
	C_RED,
	C_ORANGE,
	C_YELLOW,
	C_GREEN,
	C_BLUE,
	C_VIOLET,
};

void ledShow() 
{
	stripA.show();
	stripB.show();
}

void setPixelColor(uint8_t x, uint8_t y, uint32_t c)
{
	if(x < 6)
		stripA.setPixelColor(_pixels[y][x], c);
	else
		stripB.setPixelColor(_pixels[y][x], c);
}

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
uint32_t wheelHelper(uint16_t pos, uint16_t cycle_step, uint8_t length)
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

void max_overload(){
	if((curStep/4) % 2)
		colorFill(C_OFF);
	else
		colorFill(C_WHITE);
}
///End Animations
#define ANIM_SIZE 7
#define ANIM_MAX (ANIM_SIZE-1)

typedef void (* animPtr)();
animPtr anims[] = {
	max_overload,
	rainbowCycle,
	fullRainbow,
	colorWipe,
	rainbow_h_wipe,
	bloomIn,
	bloomOut
};

const __FlashStringHelper * animNames(uint8_t i)
{
	static const __FlashStringHelper * anims[ANIM_SIZE] = 
	{
		F("<< BACK"),
		F("RainbowCycle"),
		F("FullRainbow"),
		F("ColorWipe"),
		F("Rainbow H"),
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
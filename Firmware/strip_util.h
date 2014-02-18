#include "arrays.h"
#include "globals.h"
#include "text_util.h"
#include "gol.h"

typedef bool (* animPtr)();

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

void fillX(uint8_t x, uint32_t c)
{
	if(x >= NUM_X) return;
	for(_y=0;_y<NUM_Y;_y++)
	{
		setPixelColor(x, _y, c);
	}
}

void fillY(uint8_t y, uint32_t c)
{
	if(y >= NUM_Y) return;
	for(_x=0;_x<NUM_X;_x++)
	{
		setPixelColor(_x, y, c);
	}
}

//Input a value 0 to cycle_max to get a color value.
//The colours are a transition r - g -b - back to r
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
	return Wheel(((pos * 384 / length) + cycle_step) % WHEEL_MAX);
}

///Animations Here
uint16_t curStep = 0;
uint16_t oldStep = 0;
uint8_t  curAnim = 1;
uint8_t  oldAnim = 1;
uint8_t subStep = 0;


bool fullRainbow() {
	colorFill(Wheel(curStep & 255));

	curStep += 5;
	if(curStep >= 256)
		curStep = 0;

	return true;
}

uint8_t _wipeColor = 0;
bool colorWipe() {
	static uint8_t x, y;
	allOff();
	for(x=0; x < NUM_X; x++)
	{
		for(y=0; y<=curStep; y++)
		{
			setPixelColor(x,y, _rainbow[_wipeColor]);
		}
	}

	curStep += 1;
	if(curStep >= NUM_Y)
	{
		curStep = 1;

		_wipeColor++;
		if(_wipeColor >= 6)
		{
			_wipeColor = 0;
			curStep = 0;
		}
	}

	return true;
}

/*
Looks like a blooming flower
dir = true -> bloom outward
dir = false -> fold inward
*/
void bloom(bool dir) {
	for(_y=0; _y<NUM_Y; _y++) 
	{
		for(_x=0; _x<NUM_X; _x++)
		{
			static uint32_t c;
			static uint16_t step;
			step = dir ? (WHEEL_MAX - curStep) : curStep;
			c = wheelHelper(vector(_x, _y), step, NUM_Y);
			setPixelColor(_x, _y, c);
		}
	}

	curStep += 8;
	if(curStep >= WHEEL_MAX)
		curStep = 0;
}

bool bloomOut(){ bloom(true); return true; }
bool bloomIn(){ bloom(false); return true; }

bool rainbow_h_wipe()
{
	for(_x=0; _x<NUM_X; _x++)
	{
		static uint32_t c;
		c = wheelHelper(_x, curStep, NUM_X);
		for(_y=0; _y<NUM_Y; _y++)
			setPixelColor(_x, _y, c);
	}

	curStep += 4;
	if(curStep >= WHEEL_MAX)
		curStep = 0;

	return true;
}

bool rainbow_v_wipe()
{
	for(_y=0; _y<NUM_Y; _y++)
	{
		static uint32_t c;
		c = wheelHelper(_y, curStep, NUM_Y);
		for(_x=0; _x<NUM_X; _x++)
			setPixelColor(_x, _y, c);
	}

	curStep += 4;
	if(curStep >= WHEEL_MAX)
		curStep = 0;

	return true;
}

#define OVERLOAD_COUNT 1
uint8_t overloadColors[OVERLOAD_COUNT][3] = 
{
	{255,255,255},
	//{255,0,0},
	//{0,255,0},
	//{0,0,255},
};
uint8_t overloadColor = 0;
bool overloadDir = true;
bool max_overload(){

	if(curStep >= 256) 
	{
		overloadDir = !overloadDir;
		//if(overloadDir)
		//{
		//	overloadColor++;
		//	if(overloadColor >= OVERLOAD_COUNT)
		//		overloadColor = 0;
		//}
		curStep = 0;
	}
	static uint8_t r,g,b,brightness;
	brightness = (overloadDir ? curStep : 255 - curStep);
	r = (overloadColors[overloadColor][0] * brightness) >> 8;
	g = (overloadColors[overloadColor][1] * brightness) >> 8;
	b = (overloadColors[overloadColor][2] * brightness) >> 8;
	colorFill(C(r,g,b));

	curStep += 127;

	return true;
}


#define TEXT_START 41
bool displayText()
{
	static int16_t posA = TEXT_START, posB = TEXT_START;
	static bool result;
	result = false;
	subStep++;

	if(subStep >= 2)
	{
		subStep = 0;

		colorFill(C_OFF); //clear the buffer
		if(drawString(5, posA, C_RED, "DR WHO SUCKS!"))
			posA--;
		else
			posA = TEXT_START;

		if(drawString(11, posB, C_GREEN, "BEST IN terms of PANTS!"))
			posB--;
		else
			posB = TEXT_START;
		result = true;
	}

	curStep += 1;
	if(posB == TEXT_START)
		curStep = 0;

	return result;
}

bool fireflies()
{
	static long rnd;
	for(_x=0; _x<NUM_X; _x++)
	{
		for(_y=0; _y<NUM_Y; _y++)
		{
			setPixelColor(_x, _y, Wheel((int)random(0,WHEEL_MAX)));
		}
	}

	curStep += 1;
	if(curStep >= 50)
		curStep = 0;

	return true;
}

bool rotate(uint32_t colors[], uint8_t numColors, uint8_t width, uint8_t speed, uint16_t steps)
{
	static bool result;
	result = false;
	subStep++;
	if(subStep >= speed)
	{
		subStep = 0;

		for(_x=0; _x<NUM_X; _x++)
		{
			fillX(_x, colors[(((_x+(curStep / speed))/width)%numColors)]);
		}

		result = true;
	} 

	curStep += 1;
	if(curStep == steps * speed)
		curStep = 0;

	return result;
}

bool rotate_rainbow()
{
	return rotate(_rainbow, 6, 3, 2, 120);
}

bool emergency()
{
	static uint32_t colors[] = {C_BLUE, C_RED};

	return rotate(colors, 2, 6, 1, 120);
}

uint32_t larsonColors[] = 
{
	C(64,0,0),
	C(128,0,0),
	C(255,0,0),
};
bool larson()
{
	static bool result;
	result = false;
	static bool dir = true;
	static int8_t step = 0;


	subStep++;

	if(subStep >= 2)
	{
		subStep = 0;
		allOff();
		fillX(step - 2, larsonColors[0]);
		fillX(step - 1, larsonColors[1]);
		fillX(step, larsonColors[2]);
		fillX(step + 1, larsonColors[1]);
		fillX(step + 2, larsonColors[0]);

		step += dir ? 1 : -1;
		if(step >=11 || step <= 0)
		{
			dir = !dir;
		}

		result = true;
	}

	curStep += 1;
	if(curStep >= 48)
		curStep = 0;

	return result;
}

bool brite_off()
{
	colorFill(C_WHITE);

	bool result = (curStep == 0);

	curStep++;
	if(curStep > 50) curStep = 0;

	return result;
}

bool police()
{
	static bool result;
	static uint8_t start, stop;
	result = false;

	if(curStep % 2)
	{
		if((curStep%10)/5)
		{
			start = 0;
			stop = 5;
		}
		else
		{
			start = 6;
			stop = 11;
		}

		for(_x=start;_x<=stop;_x++)
			fillX(_x, C_BLUE);
	}
	else
	{
		allOff();
	}

	curStep++;
	if(curStep > 100) curStep = 0;

	return true;
}

void setGOLRandom(uint8_t num, uint8_t color)
{
	static uint8_t rand = 0;
	for(_x=0;_x<NUM_X;_x++)
	{
		for(_y=0;_y<NUM_Y;_y++)
		{
			if((_y%8) == 0)
			{
				rand = (uint8_t)random(0,256);
			}

			setWorldPixel(_x, _y, num, color, (rand & (1<<(_y&7))) > 0);
		}
	}
}

static bool _golNum = false;
void runGOL(uint8_t color, bool regen)
{
	if(regen)
	{
		setGOLRandom((uint8_t)_golNum, color);
	}
	else
	{
		for(_x=0;_x<NUM_X;_x++)
		{
			for(_y=0;_y<NUM_Y;_y++)
			{
				switch (getLiveDie(_x, _y, !_golNum, color))
				{
				case -1: //dies
					setWorldPixel(_x, _y, _golNum, color, false);
					break;
				case 1: //born
					setWorldPixel(_x, _y, _golNum, color, true);
					break;
				default: //stays the same
					setWorldPixel(_x, _y, _golNum, color, 
						getWorldPixel(_x, _y, !_golNum, color));
					break;
				}

			}
		}
	}
}
bool stepGOL(bool r, bool g, bool b)
{
	static uint8_t step = 10;
	static bool result;
	result = false;

	subStep++;
	if(subStep >= step || curStep == 0)
	{
		subStep = 0;

		if(r) runGOL(GOL_RED, curStep < step);
		if(g) runGOL(GOL_GRN, curStep < step);
		if(b) runGOL(GOL_BLU, curStep < step);

		for(_x=0;_x<NUM_X;_x++) 
		{
			for(_y=0;_y<NUM_Y;_y++)
			{
				static uint8_t cR, cG, cB;
				cR = r && getWorldPixel(_x, _y, _golNum, GOL_RED) ? 255 : 0;
				cG = g && getWorldPixel(_x, _y, _golNum, GOL_GRN) ? 255 : 0;
				cB = b && getWorldPixel(_x, _y, _golNum, GOL_BLU) ? 255 : 0;

				setPixelColor(_x, _y, C(cR,cG,cB));
			}
		}

		_golNum = !_golNum;

		result = true;
	}

	curStep++;
	if(curStep >= 100 * step)
		curStep = 0;

	return result;
}

bool gol_red()
{
	stepGOL(true, false, false);
}

bool gol_green()
{
	stepGOL(false, true, false);
}

bool gol_blue()
{
	stepGOL(false, false, true);
}

bool gol_all()
{
	stepGOL(true, true, true);
}

#define DEMO_SIZE 7
static uint8_t _demoAnim = 0;
animPtr demoAnims[DEMO_SIZE] = {
	fullRainbow,
	rainbow_h_wipe,
	police,
	bloomOut,
	bloomIn,
	fireflies,
	rotate_rainbow,
};

bool demo()
{
	static bool result;
	result = demoAnims[_demoAnim]();
	if(curStep == 0)
	{
		_demoAnim++;
		if(_demoAnim >= DEMO_SIZE)
			_demoAnim = 0;
	}

	return result;
}


///End Animations
#define ANIM_SIZE 19
#define ANIM_MAX (ANIM_SIZE-1)

animPtr anims[ANIM_SIZE] = {
	max_overload,
	demo,
	displayText,
	fullRainbow,
	colorWipe,
	rainbow_h_wipe,
	rainbow_v_wipe,
	bloomIn,
	bloomOut,
	fireflies,
	rotate_rainbow,
	emergency,
	larson,
	brite_off,
	police,
	gol_red,
	gol_green,
	gol_blue,
	gol_all,
};

static const char * _animNames[ANIM_SIZE] = 
{
	"<< BACK",
	"Demo",
	"Text",
	"FullRainbow",
	"ColorWipe",
	"Rainbow H",
	"Rainbow V",
	"Bloom In",
	"Bloom Out",
	"FireFlies",
	"Rotate Rainbow",
	"Emergency",
	"Larson",
	"Brite Off",
	"Police",
	"GOL Red",
	"GOL Green",
	"GOL Blue",
	"GOL All",
};


void stripInit()
{
	stripA.begin();
	stripA.setBrightness(_brightness);
	stripB.begin();
	stripB.setBrightness(_brightness);

	ledShow();
}
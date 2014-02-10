#include <EEPROM.h>
#include <Wire.h>
#include "globals.h"
#include "strip_util.h"
#include "TimerOne.h"

void saveBright() {
	EEPROM.write(0, _brightPercent);
}

void loadBright() {
	_brightPercent = EEPROM.read(0);
	_brightness = (int)(255.0  * (((float)_brightPercent) / 100.0));
	setBrightness(_brightness);
}

void setup()   {  
	encoder.write(curEncPos *  4);
	//init all the things
	curMenu = 0;
	dispMenu = 0;
	curStep = 0;
	oldStep = 0;
	curAnim = 1;
	oldAnim = 1;

	display.begin(SSD1306_SWITCHCAPVCC, 0x3D);  // initialize with the I2C addr 0x3D (for the 128x64)
	display.clearDisplay();
	display.display();

	//set button pin and pull-up resistor
	pinMode(ENCODER_BTN_PIN, INPUT);
	digitalWrite(ENCODER_BTN_PIN, HIGH);
	attachInterrupt(ENCODER_BTN_INT, buttonSelect, FALLING);

	pinMode(OVER_BTN_PIN, INPUT);
	digitalWrite(OVER_BTN_PIN, HIGH);
	attachInterrupt(OVER_BTN_INT, buttonOverride, FALLING);

	Serial.begin(115200);
	display.setTextWrap(false);

	loadBright();

	//displayMenu();

	stripInit();

	colorFill(C_RED);
	ledShow();
	delay(250);

	colorFill(C_GREEN);
	ledShow();
	delay(250);

	colorFill(C_BLUE);
	ledShow();
	delay(250);

	allOff();
	ledShow();

	//Timer1.initialize();
	//Timer1.attachInterrupt(animStep, 1000000 / 30); // 30 frames/second
}

void animStep()
{
	if(anims[curAnim]());
	{
		ledShow();
	}
}

uint8_t menuStart = 0;
uint8_t menuIndex = 0;
uint8_t menuLine = 0;
void displayMenu()
{
	//noInterrupts();

	//static uint32_t m;
	//m = millis();

	display.setTextSize(1);
	display.setTextColor(WHITE);
	display.setCursor(0,0);
	display.print(_animNames[curAnim]);
	display.print(" - ");
	display.println((16 * 1024) - freeRam(), DEC);

	if(menuLevel == MENU_BRIGHT)
	{
		display.setTextSize(4);
		display.setTextColor(WHITE);
		display.setCursor(20, 24);
		if(_brightPercent < 100)
			display.print(0);
		if(_brightPercent < 10)
			display.print(0);
		display.print(_brightPercent);
		display.print("%");
	}
	else
	{
		display.setTextSize(2);
		display.setCursor(0,16);

		menuStart = curMenu < MENU_SIDE ? menuSize - (MENU_SIDE - curMenu) : curMenu - MENU_SIDE;
		menuLine = 0;
		for(int i=menuStart; i<menuStart + 7; i++)
		{
			menuIndex = i > maxMenu ? i - menuSize : i;
			if(menuIndex == curMenu)
				display.setTextColor(BLACK, WHITE);
			else
				display.setTextColor(WHITE);

			if(menuLevel == MENU_HOME)
				display.println(_main_menu[menuIndex]);
			else if(menuLevel == MENU_ANIM)
				display.println(_animNames[menuIndex]);

			menuLine++;
		}
	}

	display.display();
	display.clearDisplay();

	//Serial.println(millis() - m, DEC);

	updateDisplay = false;

	//interrupts();
}

void getEncoder() {
	static uint8_t dir = 1;
	newEnc = encoder.read() / 4; //current encoder has too many steps and pressing the button causes a step to happen

	if(newEnc != curEncPos)
	{
		//Serial.print(newEnc, DEC); Serial.print(" - "); Serial.println(curEncPos, DEC);
		dir = newEnc > curEncPos ? -1 : 1;
		if(menuLevel == MENU_BRIGHT)
		{

			_brightPercent += dir * 10;
			if(_brightPercent > 100) _brightPercent = MIN_BRIGHT;
			else if(_brightPercent < MIN_BRIGHT) _brightPercent = 100;

			_brightness = (int)(255.0  * (((float)_brightPercent) / 100.0));
			setBrightness(_brightness);
		}
		else
		{
			curMenu += dir;

			if(curMenu > maxMenu)
				curMenu = 0;
			else if(curMenu < 0)
				curMenu = maxMenu;
		}
		curEncPos = newEnc;

		updateDisplay = true;
	}
}

void buttonSelect()
{
	if (TimeElapsed(lastSelect, DEBOUNCE_TIME))
	{   
		lastSelect = millis();
		selected = true;
		//Serial.println("BTN!");
	}
}

void buttonOverride()
{
	if (TimeElapsed(lastOverride, DEBOUNCE_TIME))
	{   
		lastOverride = millis();
		overrideRef = 0;
		overridden = true;
		countdown = OVERRIDE_TIME;
	}
}

void displayOverride()
{
	display.setTextSize(8);
	display.setTextColor(WHITE);
	display.setCursor(countdown > 9 ? 20 : 44, 4);
	display.print(countdown);

	display.display();
	display.clearDisplay();
}

void toggleEnable()
{
	_enabled = !_enabled;
	if(_enabled)
	{
		ledShow();
	}
	else
	{
		colorFill(C_OFF);
		ledShow();
	}
}

void loop() {
	static unsigned long stepRef = 0;
	if(TimeElapsed(stepRef, 25) && _enabled)
	{
		stepRef = millis();
		animStep();
		//Serial.println(millis() - stepRef, DEC);
	}

	if(selected)
	{
		selected = false;
		dispMenu = curMenu;

		if(menuLevel == MENU_HOME)
		{
			if(dispMenu == 0) //Animations
			{
				menuLevel = MENU_ANIM;
				dispMenu = 0;
				curMenu = 0;
				maxMenu = ANIM_MAX;
				menuSize = ANIM_SIZE;
			}
			else if(dispMenu == 1)
			{
				menuLevel = MENU_BRIGHT;
			}
			else if(dispMenu == 2)
			{
				toggleEnable();
			}
		}
		else if(menuLevel == MENU_ANIM)
		{
			if(dispMenu == 0)
			{
				menuLevel = MENU_HOME;
				dispMenu = 0;
				curMenu = 0;
				maxMenu = MAX_MENU;
				menuSize = MENU_SIZE;
			}
			else
			{
				if(!_enabled) toggleEnable();
				allOff();
				curAnim = dispMenu;
				curStep = 0;
				subStep = 0;
			}
		}
		else if(menuLevel == MENU_BRIGHT)
		{
			menuLevel = MENU_HOME;
			saveBright();
		}

		updateDisplay = true;
	}

	if(overridden)
	{
		if(!_enabled) toggleEnable();

		if(curAnim)
		{
			oldAnim = curAnim;
			oldStep = curStep;
			curAnim = 0;
			setBrightness(255);
		}

		if(TimeElapsed(overrideRef, 1000))
		{
			overrideRef = millis();

			displayOverride();
			countdown--;
			if(countdown < 1)
			{
				setBrightness(_brightness);
				curStep = oldStep;
				curAnim = oldAnim;
				overridden = false;
				updateDisplay = true;
				overrideRef = 0;
			}
		}
	}
	else
	{
		getEncoder();
		if(updateDisplay) 
		{
			displayMenu();
		}
	}
}

#include <Wire.h>
#include "globals.h"
#include "TimerOne.h"

void setup()   {  
	display.begin(SSD1306_SWITCHCAPVCC, 0x3D);  // initialize with the I2C addr 0x3D (for the 128x64)
	display.clearDisplay();
	display.display();
	// init done

	//set button pin and pull-up resistor
	pinMode(ENCODER_BTN_PIN, INPUT);
	digitalWrite(ENCODER_BTN_PIN, HIGH);
	attachInterrupt(ENCODER_BTN_INT, buttonSelect, FALLING);

	pinMode(OVER_BTN_PIN, INPUT);
	digitalWrite(OVER_BTN_PIN, HIGH);
	attachInterrupt(OVER_BTN_INT, buttonOverride, FALLING);

	Serial.begin(115200);
	display.setTextWrap(false);

	displayMenu();

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

	Timer1.initialize();
	Timer1.attachInterrupt(animStep, 1000000 / 60); // 30 frames/second
}

void animStep()
{
	anims[curAnim]();
	ledShow();

	curStep++;
}

uint8_t menuStart = 0;
uint8_t menuIndex = 0;
uint8_t menuLine = 0;
void displayMenu()
{
	display.setTextSize(1);
	display.setTextColor(WHITE);
	display.setCursor(0,0);
	display.print(animNames(curAnim));
	display.print(" - ");
	display.println((16 * 1024) - freeRam(), DEC);

	display.setTextSize(2);
	display.setCursor(0,16);



	if(menuLevel == MENU_BRIGHT)
	{

	}
	else
	{
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
				display.println(menu(menuIndex));
			else if(menuLevel == MENU_ANIM)
				display.println(animNames(menuIndex));

			menuLine++;
		}
	}



	display.display();
	display.clearDisplay();
}

void getEncoder() {
	static long newEnc;
	newEnc = encoder.read() / 4; //current encoder has too many steps and pressing the button causes a step to happen
	if(newEnc != oldEnc)
	{
		if(newEnc > oldEnc)
			curMenu++;
		else if(newEnc < oldEnc)
			curMenu--;

		if(curMenu > maxMenu)
			curMenu = 0;
		else if(curMenu < 0)
			curMenu = maxMenu;

		oldEnc = newEnc;
	}
}

void buttonSelect()
{
	if (TimeElapsed(lastSelect, DEBOUNCE_TIME))
	{   
		lastSelect = millis();
		selected = true;
	}
}

void buttonOverride()
{
	if (TimeElapsed(lastOverride, DEBOUNCE_TIME))
	{   
		lastOverride = millis();
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

void loop() {

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
				menuLevel == MENU_BRIGHT;
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
				allOff();
				curAnim = dispMenu;
				curStep = 0;
			}
		}
		else if(menuLevel == MENU_BRIGHT)
		{

		}
		//pressCount++;
	}

	if(overridden)
	{
		if(TimeElapsed(overrideRef, 1000))
		{
			overrideRef = millis();
			displayOverride();
			countdown--;
			if(countdown < 0)
			{
				overridden = false;
				overrideRef = 0;
			}
		}
	}
	else
	{
		displayMenu();
		getEncoder();
	}
}



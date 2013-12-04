#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#include "globals.h"

#include <Encoder.h>

Encoder encoder(10, 11);

#define OLED_RESET 15
Adafruit_SSD1306 display(OLED_RESET);

#if (SSD1306_LCDHEIGHT != 64)
#error("Height incorrect, please fix Adafruit_SSD1306.h!");
#endif

void setup()   {  
	// by default, we'll generate the high voltage from the 3.3v line internally! (neat!)
	display.begin(SSD1306_SWITCHCAPVCC, 0x3D);  // initialize with the I2C addr 0x3D (for the 128x64)
	// init done

	//set button pin and pull-up resistor
	pinMode(2, INPUT);
	digitalWrite(2, HIGH);

	attachInterrupt(2, buttonPress, FALLING);

	Serial.begin(115200);

	//display.display(); // show splashscreen
	//delay(2000);
	//display.clearDisplay();   // clears the screen and buffer
}

uint8_t menuStart = 0;
uint8_t menuIndex = 0;
uint8_t menuLine = 0;
void displayMenu()
{
	display.setTextSize(1);
	display.setTextColor(BLACK, WHITE);
	display.setCursor(0,0);
	display.print(menu(dispMenu));
	//display.print(" - ");
	//display.println((16 * 1024) - freeRam(), DEC);

	display.setTextSize(2);
	display.setCursor(0,16);
	menuStart = curMenu < MENU_SIDE ? MENU_SIZE - (MENU_SIDE - curMenu) : curMenu - MENU_SIDE;
	menuLine = 0;
	for(int i=menuStart; i<menuStart + 7; i++)
	{
		menuIndex = i > MAX_MENU ? i - MENU_SIZE : i;
		if(menuIndex == curMenu)
			display.setTextColor(BLACK, WHITE);
		else
			display.setTextColor(WHITE);

		display.setCursor(0,16+(16*menuLine));
		display.print(menu(menuIndex));
		menuLine++;
	}

	display.display();
	display.clearDisplay();
}

void getEncoder() {
	static long newEnc;
	newEnc = encoder.read() / 2; //current encoder has too many steps and pressing the button causes a step to happen
	if(newEnc != oldEnc)
	{
		if(newEnc > oldEnc)
			curMenu++;
		else if(newEnc < oldEnc)
			curMenu--;

		if(curMenu > MAX_MENU)
			curMenu = 0;
		else if(curMenu < 0)
			curMenu = MAX_MENU;

		oldEnc = newEnc;
	}
}

void buttonPress()
{
	if ((millis() - lastButton) > DEBOUNCE_TIME)
	{   
		lastButton = millis();
		buttonPressed = true;
	}
}

void loop() {

	if(buttonPressed)
	{
		buttonPressed = false;
		dispMenu = curMenu;
		//pressCount++;
	}

	displayMenu();
	getEncoder();
}



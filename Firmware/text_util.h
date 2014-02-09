#include "globals.h"
#include "LEDFont.h"
#include <avr/pgmspace.h>

//void drawLine(int16_t x0, int16_t y0, int16_t x1, int16_t y1, uint32_t color) 
//{
//	int16_t steep = abs(y1 - y0) > abs(x1 - x0);
//	if (steep) {
//		swap(x0, y0);
//		swap(x1, y1);
//	}
//
//	if (x0 > x1) {
//		swap(x0, x1);
//		swap(y0, y1);
//	}
//
//	int16_t dx, dy;
//	dx = x1 - x0;
//	dy = abs(y1 - y0);
//
//	int16_t err = dx / 2;
//	int16_t ystep;
//
//	if (y0 < y1) {
//		ystep = 1;
//	} else {
//		ystep = -1;
//	}
//
//	for (; x0<=x1; x0++) {
//		
//		{
//			if (steep) {
//				setPixelColor(y0, x0, color);
//			} else {
//				setPixelColor(x0, y0, color);
//			}
//		}
//		err -= dy;
//		if (err < 0) {
//			y0 += ystep;
//			err += dx;
//		}
//	}
//}
//
//void drawFastVLine(int16_t x, int16_t y, int16_t h, uint32_t color) 
//{
//	// Update in subclasses if desired!
//	drawLine(x, y, x, y+h-1, color);
//}
//
//void fillRect(int16_t x, int16_t y, int16_t w, uint8_t h, uint32_t color) 
//{
//	// Update in subclasses if desired!
//	for (int16_t i=x; i<x+w; i++) {
//		drawFastVLine(i, y, h, color);
//	}
//}

// Draw a character
void drawChar(int16_t x, int16_t y, unsigned char c, uint32_t color) 
{
	if((x >= NUM_X)            || // Clip right
		(y >= NUM_Y)           || // Clip bottom
		((x + 6) < 0) || // Clip left
		((y + 8) < 0))   // Clip top
		return;

	for (int8_t h=0; h<6; h++ ) 
	{
		if(c >= 97 && c <= 122) c -= 32; 
		if(c > 90 || c < 32) continue;

		uint8_t line;
		if (h == 5) 
			line = 0x0;
		else 
			line = _led_font[(c-32)*5 + h];
			//line = /*pgm_read_byte*/(_led_font+(((uint8_t)c)*5)+h);

		for (int8_t w = 0; w<6; w++) 
		{
			if (line & 0x1) 
			{
				if(x-w >= 0 &&  y+h >= 0)
					setPixelColor(x-w, y+h, color);
			} 
			line >>= 1;
		}
	}
}

bool drawString(int16_t x, int16_t y, uint32_t color, const String &str)
{
	int8_t len = str.length();
	
	//Serial.println(y, DEC);
	if(y + (len * 6) <= 0) return false;
	
	//Serial.println("dS2");
	uint8_t i = 0;
	while (i < len && y < NUM_Y) {
		drawChar(x, y, str[i], color);
		y += 6;
		i++;
	}
	return true;
}

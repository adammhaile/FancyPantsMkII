#include "globals.h"

#define GOL_RED 0
#define GOL_GRN 1
#define GOL_BLU 2

uint8_t _world[3][2][12][6]; //2x 12x42 display but y-axis divided into bytes

__attribute__((noinline)) bool getWorldPixel(uint8_t x, uint8_t y, uint8_t num, uint8_t color)
{
	static uint8_t rowByte = 0; // 0 means top 8, 1 means bottom 8
	static uint8_t rowBit = 0;

	if(!(num >= 0 && num < 2)) return false;

	rowByte = y >> 3;
	rowBit = y&7;

	return (_world[color][num][x][rowByte] & (1 << rowBit)) > 0;
}

__attribute__((noinline)) void setWorldPixel(uint8_t x, uint8_t y, uint8_t num, uint8_t color, bool state)
{
	static uint8_t rowByte = 0; // 0 means top 8, 1 means bottom 8
	static uint8_t rowBit = 0;

	if(!(num >= 0 && num < 2)) return;

	rowByte = y >> 3;
	rowBit = y&7;

	if(state)
		_world[color][num][x][rowByte] |= (1 << rowBit);
	else
		_world[color][num][x][rowByte] &= ~(1 << rowBit);
}

uint8_t neighbours(uint8_t x, uint8_t y, uint8_t num, uint8_t color) { //Calculate how many living neighbors each pixel has.
	return  getWorldPixel((x + 1) % NUM_X, y, num, color) +
		getWorldPixel(x, ((y + 1) % NUM_Y), num, color) +
		getWorldPixel((x + NUM_X - 1) % NUM_X, y, num, color) +
		getWorldPixel(x, (y + NUM_Y - 1) % NUM_Y, num, color) +
		getWorldPixel((x + 1) % NUM_X, (y + 1) % NUM_Y, num, color) +
		getWorldPixel((x + NUM_X - 1) % NUM_X, (y + 1) % NUM_Y, num, color) +
		getWorldPixel((x + NUM_X - 1) % NUM_X, (y + NUM_Y - 1) % NUM_Y, num, color) +
		getWorldPixel((x + 1) % NUM_X, (y + NUM_Y - 1) % NUM_Y, num, color);
} //end neighbors

int8_t getLiveDie(uint8_t x, uint8_t y, uint8_t num, uint8_t color)
{
	static uint8_t count = 0;
	count = neighbours(x, y, num, color);
	if (count == 3 && !(getWorldPixel(x, y, num, color))) {
		// A new cell is born
		return 1;
	} 

	if ((count < 2 || count > 3) && getWorldPixel(x, y, num, color)) {
		// Cell dies
		return -1;
	}

	return 0;// stays the same
}
#ifndef _VSARDUINO_H_
#define _VSARDUINO_H_
//Board = Mighty 1284p 16MHz using Optiboot
#define __AVR_ATmega1284p__
#define __AVR_ATmega1284P__
#define ARDUINO 105
#define ARDUINO_MAIN
#define __AVR__
#define __avr__
#define F_CPU 16000000L
#define __cplusplus
#define __inline__
#define __asm__(x)
#define __extension__
#define __ATTR_PURE__
#define __ATTR_CONST__
#define __inline__
#define __asm__ 
#define __volatile__

#define __builtin_va_list
#define __builtin_va_start
#define __builtin_va_end
#define __DOXYGEN__
#define __attribute__(x)
#define NOINLINE __attribute__((noinline))
#define prog_void
#define PGM_VOID_P int
            
typedef unsigned char byte;
extern "C" void __cxa_pure_virtual() {;}

void saveBright();
void loadBright();
//
void animStep();
void displayMenu();
void getEncoder();
void buttonSelect();
void buttonOverride();
void displayOverride();
void toggleEnable();
//

#include "C:\Program Files (x86)\Arduino\hardware\mighty-1284p\cores\standard\arduino.h"
#include "C:\Program Files (x86)\Arduino\hardware\mighty-1284p\variants\standard\pins_arduino.h" 
#include "G:\GitHub\FancyPantsMkII\Firmware\FancyPantsMkII.ino"
#include "G:\GitHub\FancyPantsMkII\Firmware\Adafruit_GFX.cpp"
#include "G:\GitHub\FancyPantsMkII\Firmware\Adafruit_GFX.h"
#include "G:\GitHub\FancyPantsMkII\Firmware\Adafruit_NeoPixel.cpp"
#include "G:\GitHub\FancyPantsMkII\Firmware\Adafruit_NeoPixel.h"
#include "G:\GitHub\FancyPantsMkII\Firmware\Adafruit_SSD1306.cpp"
#include "G:\GitHub\FancyPantsMkII\Firmware\Adafruit_SSD1306.h"
#include "G:\GitHub\FancyPantsMkII\Firmware\Encoder.cpp"
#include "G:\GitHub\FancyPantsMkII\Firmware\Encoder.h"
#include "G:\GitHub\FancyPantsMkII\Firmware\LEDFont.h"
#include "G:\GitHub\FancyPantsMkII\Firmware\TimerOne.cpp"
#include "G:\GitHub\FancyPantsMkII\Firmware\TimerOne.h"
#include "G:\GitHub\FancyPantsMkII\Firmware\arrays.h"
#include "G:\GitHub\FancyPantsMkII\Firmware\direct_pin_read.h"
#include "G:\GitHub\FancyPantsMkII\Firmware\glcdfont.c"
#include "G:\GitHub\FancyPantsMkII\Firmware\globals.h"
#include "G:\GitHub\FancyPantsMkII\Firmware\gol.h"
#include "G:\GitHub\FancyPantsMkII\Firmware\interrupt_config.h"
#include "G:\GitHub\FancyPantsMkII\Firmware\interrupt_pins.h"
#include "G:\GitHub\FancyPantsMkII\Firmware\strip_util.h"
#include "G:\GitHub\FancyPantsMkII\Firmware\text_util.h"
#endif

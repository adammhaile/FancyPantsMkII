#ifndef _VSARDUINO_H_
#define _VSARDUINO_H_
//Board = Mighty 1284p 16MHz using Optiboot
#define __AVR_ATmega1284P__
#define 
#define ARDUINO 105
#define ARDUINO_MAIN
#define __AVR__
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

//
void displayMenu();
void getEncoder();
void buttonSelect();
void buttonOverride();
void displayOverride();
//

#include "C:\Program Files (x86)\Arduino\hardware\mighty-1284p\variants\standard\pins_arduino.h" 
#include "C:\Program Files (x86)\Arduino\hardware\mighty-1284p\cores\standard\arduino.h"
#include "G:\GitHub\FancyPantsMkII\FancyPantsMkII.ino"
#include "G:\GitHub\FancyPantsMkII\RTClib.cpp"
#include "G:\GitHub\FancyPantsMkII\RTClib.h"
#include "G:\GitHub\FancyPantsMkII\globals.h"
#endif

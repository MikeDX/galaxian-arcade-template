#ifndef _CONFIG_H
#define _CONFIG_H
#include <string.h>

typedef unsigned char byte;
typedef unsigned short word;
typedef unsigned char sbyte;
typedef unsigned long dword;

//#define SOUNDTEST
//#define DEBUG 
//#define SMS_TARGET
#define ATTRACT_MODE
#define GALAXIAN_TARGET
#define SCRAMBLE_HW // SCRAMBLE HARDWARE VARIANT

typedef struct {
  byte xpos;
  byte code;
  byte color;
  byte ypos;
} _vsprite;

void draw_bcd_byte(byte x, byte y, byte bcd);

#endif


#ifndef _GALAXIAN_H
#define _GALAXIAN_H


#ifdef FROGF_HW
//#define ATTRACT_MODE

#define VRAM 0x8800
#define ORAM 0x9040
#define TRAM 0x9000
#define IRQ_ADDR 0xA804
#define STARS_ADDR 0xA803 // NOT USED
#define HFLIP_ADDR 0xA802
#define VFLIP_ADDR 0xA806
#define WATCHDOG_ADDR 0xB800
#define INPUT0 0xD000
#define INPUT1 0xD008
#define INPUT2 0xD010
#define AYCMD  0xE000
#define AYTRIG 0xE008
#define D82551 0xD018
#define D82552 0xE018

#define RAM 0x8000

#endif



#ifdef SCRAMBLE_HW
//#define ATTRACT_MODE

#define VRAM 0x4800
#define ORAM 0x5040
#define TRAM 0x5000

#define IRQ_ADDR 0x6801
#define STARS_ADDR 0x6804
#define HFLIP_ADDR 0x6806
#define VFLIP_ADDR 0x6807
#define WATCHDOG_ADDR 0x7000
#define INPUT0 0x8100
#define INPUT1 0x8101
#define INPUT2 0x8102
#define AYCMD  0x8200
#define AYTRIG 0x8201
#define D82551 0x8103
#define D82552 0x8203

#define RAM 0x4000



#endif

#ifdef SCOBRAB_HW
//#define ATTRACT_MODE

#define VRAM 0x8800
#define ORAM 0x9040
#define TRAM 0x9000

#define IRQ_ADDR 0xA801
#define STARS_ADDR 0xA804
#define HFLIP_ADDR 0xA806
#define VFLIP_ADDR 0xA807
#define WATCHDOG_ADDR 0xB000
#define INPUT0 0x9800
#define INPUT1 0x9801
#define INPUT2 0x9802

#define AYCMD  0xA000
#define AYTRIG 0xA001

#define D82551 0x9803
#define D82552 0xA003

#define RAM 0x8000



#endif



// possibly change for other platforms

#define LEFT1   !(input0 & 0x20)
#define RIGHT1  !(input0 & 0x10)
#define UP1     (!(input2 & 0x10) || !(input0 & 0x1))
#define DOWN1   !(input2 & 0x40)

#define FIRE1   !(input0 & 0x08)
#define BOMB1   !(input0 & 0x02)
#define COIN1   !(input0 & 0x80)

#define START1  !(input1 & 0x80)

#define LEFT2   !(input1 & 0x20)
#define RIGHT2  !(input1 & 0x10)
#define UP2     !(input0 & 0x01)
#define DOWN2   !(input2 & 0x01)

#define FIRE2   !(input1 & 0x8)
#define BOMB2   !(input1 & 0x04)
#define COIN2   !(input0 & 0x40)

#define START2  !(input1 & 0x40)

#define SERVICE !(input0 & 0x04)

#define IPT_COCKTAIL !(input2 & 0x08)

#define DIP1 (input1 & 0x03)
#define DIP2 (input2 & 0x06) >> 1


//#define watchdog watchdog_c++; 
#define watchdog __asm ld a, (#_watchdog_c)  __endasm;

#define getchar(x, y) vram[(29-x)][y];

volatile byte __at (INPUT0) input0;
volatile byte __at (INPUT1) input1;
volatile byte __at (INPUT2) input2;
volatile byte __at (AYCMD) ay_cmd;
volatile byte __at (AYTRIG) ay_trigger;


byte __at (VRAM) vram[32][32];
byte __at (0x0) ram[0x10000];

byte sound_enable = 0x08;

#define rputchar(x,y,ch) vram[x][y]=ch

struct {
  byte scroll;
  byte attrib;
} __at (TRAM) vcolumns[32];

struct {
  byte xpos;
  byte code;
  byte color;
  byte ypos;
} __at (ORAM) msprites[8];

struct {
  byte unused1;
  byte xpos;
  byte unused2;
  byte ypos;
} __at (0x5060) vmissiles[8];


byte __at (IRQ_ADDR) enable_irq;
byte __at (STARS_ADDR) enable_stars;
byte __at (HFLIP_ADDR) enable_hflip;
byte __at (VFLIP_ADDR) enable_vflip;

byte __at (0x6808) missile_width;
byte __at (0x6809) missile_offset;
byte __at (WATCHDOG_ADDR) watchdog_c;


/// 

#define LOCHAR 0x30
#define HICHAR 0xff

#define CHAR(ch) (ch-LOCHAR)

#define BLANK 0x10

#define CHAR_BLANK 0x10
#define SP_BLANK 0x15

extern byte framecount;
extern _vsprite vsprites[8];
extern byte animframe;

void clrscr();
void set8255(void);

//byte getchar(byte x, byte y);

extern volatile byte video_framecount; // actual framecount


#endif

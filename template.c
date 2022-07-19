#include "config.h"
#include "machine.h"

// Tell the compiler we want these headers available to other files
#ifdef COMPILER_DEFINES
#include "galaxian.h"
#include "core.h"
#endif

//#link "galaxian.c"

void main();

byte credits = 0;
byte framecount = 0;
_vsprite vsprites[8];
byte animframe=0;
byte audioqueue[0x10];
byte queueproc;
byte queueptr;

byte playing;
word score;
word tscore;


struct {
  word score;
  char name[4];
} hiscores[5] = {
  { 0x0100, "MYK" },
  { 0x0100, "GUD" },
  { 0x0070, "POB" },
  { 0x0060, "YAK" },
  { 0x0050, "DUG" }
};

#include "init.h"


///

void reset_framecount(void) {
  video_framecount = 0;
  framecount = 0;
}

// add two 16-bit BCD values
word bcd_add(word a, word b) __naked {
  a; b; // to avoid warning
  __asm
    push	ix
    ld	ix,#0
    add	ix,sp
    ld	a,4 (ix)
    add	a, 6 (ix)
    daa
    ld	c,a
    ld	a,5 (ix)
    adc	a, 7 (ix)
    daa
    ld	b,a
    ld	l, c
    ld	h, b
    pop	ix
    ret
    __endasm;
}

word bcd_sub(word a, word b) __naked {
  a; b; // to avoid warning
  __asm
    push	ix
    ld	ix,#0
    add	ix,sp
    ld	a,4 (ix)
    sub	a, 6 (ix)
    daa
    ld	c,a
    ld	a,5 (ix)
    sbc	a, 7 (ix)
    daa
    ld	b,a
    ld	l, c
    ld	h, b
    pop	ix
    ret
    __endasm;
}

void draw_score(byte x, byte y, word value) {
  //  score;
  draw_bcd_word(x,y,value);
  putstring(x+4,y,"00");
}

void drawscore(void) {
  static byte fc = 0;
  if(playing) {
    fc ++;
    if (fc == 0x10) {
      putstring(2,0,"@@@");
    }
    if (fc == 0x20) {      
      putstring(2,0,"1UP");
      fc = 0 ;
    }

    if(score != tscore) {
      if(score < tscore) {
        score = bcd_add(score,0x1);
      }
      if(score > tscore) {
        score = bcd_sub(score,0x1);
      }
      draw_score(0,1,score);

      //  putstring(2,1,"@@00");
      draw_score(11,1,hiscores[0].score);

      //  putstring(12,1,"10000");
      //  draw_score(20,1,0);
    }
  }
}



void draw_bcd_word(byte x, byte y, word bcd) {
  byte j;
  byte d = 0;
  //  x += 3;
  for (j=0; j<4; j++) {
    byte s = (bcd & 0xf000) >> 12;
    if (s>0 || d > 0) {
      putchar(x, y, CHAR('0'+s));
      d = 1;
    }
    x++;
    bcd <<= 4;
  }
}


void memset_safe(void* _dest, char ch, word size) {
  byte* dest = _dest;
  while (size--) {
    *dest++ = ch;
  }
}
void resetsprites(void) {
  __asm
    push bc
    ld hl, #_vsprites
    ld b, #7
    _rsploop::
  ld (hl), #0xff
    inc hl

    ld (hl), #SP_BLANK
    inc hl
    inc hl
    
    ld (hl), #0xff
    inc hl
    djnz _rsploop
    pop bc

    __endasm;

}

void drawtexts(void) {
  putstring(19,31,"CREDIT@");
  draw_bcd_byte(26,31,credits);
  putstring(2,0,"1UP");
  putstring(22,0,"2UP");
  putstring(9,0,"HIGH@SCORE");
  vcolumns[0].attrib=3; // 1up hi 2up - red
  vcolumns[1].attrib=7; // scores = white

  vcolumns[29].attrib = 1;
  vcolumns[30].attrib = 1;

  vcolumns[31].attrib=7; // credit line = wihte
  putstring(24,1,"00"); // 2p score

}


void attract(void) {
while(credits == 0) {
//  byte x = 0;
  putstring(9,13,"INSERT COIN");
  vcolumns[13].attrib=7; // credit line = wihte

  wait_for_frame();
}
}
void p1p2start(void) {
  sclear(1);
//    vsprites[0].xpos = 0;
}

void game(void) {}


void main(void) {
  init_sound();
  memset_safe(audioqueue,0xff,0x10);

  queue_sound(SONG_STOP);
  queue_sound(SOUND_OK);

  reset_framecount();

  enable_irq = 1;
  enable_stars = 0x00;

  #ifdef SOUNDTEST
  if(START1)
    soundtest();
  #endif
  clrscr();

  drawtexts();
  score = 1;
  tscore = 0;
  playing = 1;
  drawscore();
  playing = 0;

  while(1) {
    #ifdef ATTRACT_MODE
    if(credits == 0) 
      attract();

    p1p2start();
    #endif
    wait_for_frame();
    sclear(1);
    drawtexts();
    wait_for_frame();
    game();
    drawtexts();
  }
}



void draw_bcd_byte(byte x, byte y, byte bcd) {
  byte s = (bcd & 0xf0) >> 4;
  if (s>0)
    putchar(x, y, CHAR('0'+s));
  s = (bcd & 0x0f);
  x++;
  putchar(x, y, CHAR('0'+s));
}

void queue_sound(byte c) {
  audioqueue[queueptr] = c;

  if(++queueptr == 0x10)
    queueptr = 0;
}

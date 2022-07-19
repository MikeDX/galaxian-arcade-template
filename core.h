#ifndef _CORE_H
#define _CORE_H

#include "config.h"

void reset_video_framecount();

void putchar(byte x, byte y, byte ch);
void clrobjs();
void putstring(byte x, byte y, const char* string);
void queue_sound(byte cmd);
void wait_for_frame();
void reset_framecount(void);
void init_sound(void);
void drawscore(void);
void draw_bcd_word(byte x, byte y, word bcd);
void sclear(byte wait);

#define SOUND_CREDIT 8
#define SONG_STOP 0
#define SOUND_OK 0

extern byte credits;

#endif

#ifdef GALAXIAN_TARGET
#include "galaxian.h"

void start() __naked {

  __asm
    di
    LD      SP,#RAM + 0x800

    ; run ramtest
      call _ramtest
      ; clear all ram
        ld de,#RAM+1
        ld hl,#RAM
        xor a
        ld (hl),a
        ld bc,#0x800
        ldir
        EI
        ; copy initialized data to RAM
          LD    BC, #l__INITIALIZER
          LD    A, B
          LD    DE, #s__INITIALIZED
          LD    HL, #s__INITIALIZER
          LDIR
          JP    _main

          ; padding to get to offset 0x66
            .ds   0x66 - (. - _start)
            __endasm;
}


// starts at address 0x66
void rst_66() __interrupt {
  static byte db = 0;
  video_framecount++;
  if(COIN1) {
    db = 1;
  }
  if(!COIN1 && db) {
    db = 0;
    if(credits < 0x100) {
      __asm
        ld a, (#_credits)
        inc a
        daa
        ld (#_credits),a
        __endasm;
      queue_sound(SOUND_CREDIT);
      draw_bcd_byte(26,31,credits);
      //      putchar(27,31,credits);
    }
  }
  //  ay_trigger = 0x00;

//  process_audio_queue();

}

#endif

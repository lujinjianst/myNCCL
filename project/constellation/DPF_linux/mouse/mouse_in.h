#ifndef __MOUSE_IN_H_
#define __MOUSE_IN_H_

#include "../common/common.h"
#include "../jpeg/jpeg.h"
#include "../jpeg/effects.h"
#include "../font/font.h"
#include "../mp3/play.h"

#include <signal.h>
#include <sys/wait.h>
#include <linux/soundcard.h>
#include <sys/time.h>

#define MOUSE_DEVICE	"/dev/input/mice"

#define COLOR_A 0xffffff
#define COLOR_B 0xffFF00

#define C_WIDTH 10
#define C_HEIGHT 16
#define T__ 0x0
#define BORD 0x0
#define X__ 0xffffff

#define MUSIC 1
#define PREVIEW 2
#define SLIDE 3
#define EXIT 4

#define PAGE_UP 1
#define PAGE_DOWN 2

#define MP3_PREV 1
#define MP3_NEXT 2
#define MP3_PAUSE 3
#define MP3_LIST 4
#define MP3_MODE 5
#define MP3_PAGE_PREV 6
#define MP3_PAGE_NEXT 7

#define UP_X (780.0/1024)
#define UP_Y (730.0/768)
#define DOWN_X (880.0/1024)
#define DOWN_Y (730.0/768)

#define MUSIC_X (25.0/1024)
#define PREVIEW_X (25.0/1024)
#define SLIDE_X (25.0/1024)
#define EXIT_X (25.0/1024)

#define MUSIC_Y (80.0/768)
#define PREVIEW_Y (160.0/768)
#define SLIDE_Y (240.0/768)
#define EXIT_Y (320.0/768)

typedef signed char s8_t;

typedef struct					//information of mouse
{
    int dx;
    int dy;
    int dz;
    int button;
}mevent_t;

u16_t buf[C_WIDTH * C_HEIGHT]; 		//save mouse's area
mevent_t mevent;

u16_t menu_bpp[350][80];

u16_t cursor_pixel[C_WIDTH * C_HEIGHT] = 
{
BORD,T__,T__,T__,T__,T__,T__,T__,T__,T__,
BORD,BORD,T__,T__,T__,T__,T__,T__,T__,T__,
BORD,X__,BORD,T__,T__,T__,T__,T__,T__,T__,
BORD,X__,X__,BORD,T__,T__,T__,T__,T__,T__,
BORD,X__,X__,X__,BORD,T__,T__,T__,T__,T__,
BORD,X__,X__,X__,X__,BORD,T__,T__,T__,T__,
BORD,X__,X__,X__,X__,X__,BORD,T__,T__,T__,
BORD,X__,X__,X__,X__,X__,X__,BORD,T__,T__,
BORD,X__,X__,X__,X__,X__,X__,X__,BORD,T__,
BORD,X__,X__,X__,X__,X__,BORD,BORD,BORD,BORD,
BORD,X__,X__,BORD,X__,X__,BORD,T__,T__,T__,
BORD,X__,BORD,BORD,BORD,X__,X__,BORD,T__,T__,
BORD,BORD,T__,T__,BORD,X__,X__,BORD,T__,T__,
T__,T__,T__,T__,T__,BORD,X__,X__,BORD,T__,
T__,T__,T__,T__,T__,BORD,X__,X__,BORD,T__,
T__,T__,T__,T__,T__,T__,BORD,BORD,T__,T__
};

#endif

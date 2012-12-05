#ifndef __PLAY_IN_H_
#define __PLAY_IN_H_

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <sys/ioctl.h>
#include <sys/mman.h>
#include <linux/soundcard.h>
#include <string.h>

#include "../common/common.h"
#include "../font/font.h"
#include "../jpeg/jpeg.h"

#define MP3_PREV 1
#define MP3_NEXT 2
#define MP3_PAUSE 3
#define MP3_LIST 4
#define MP3_MODE 5
#define MP3_PAGE_PREV 6
#define MP3_PAGE_NEXT 7

#define PREV_X 205.0/800
#define PAUSE_X 281.0/800
#define NEXT_X 360.0/800
#define CUR_X 190.0/800
#define NAME_X 260.0/800
#define LIST_BUTTON_X 477.0/800  
#define MODE_X 445.0/800  
#define LIST_X 190.0/800 
#define MP3_PREV_X 445.0/800
#define MP3_NEXT_X 470.0/800

#define PREV_Y 298.0/480
#define PAUSE_Y 298.0/480
#define NEXT_Y 300.0/480
#define CUR_Y 280.0/480
#define NAME_Y 280.0/480
#define LIST_BUTTON_Y 302.0/480
#define MODE_Y 302.0/480
#define LIST_Y 330.0/480
#define MP3_PREV_Y 440.0/480
#define MP3_NEXT_Y 440.0/480

#define CUR_NAME_WIDTH 360.0/800
#define CUR_NAME_HEIGHT 17.0/480

#define PAUSE_WIDTH 70.0/800
#define PAUSE_HEIGHT 30.0/480

u16_t pause_bpp[60][100];
u16_t name_bpp[30][470];
u16_t mp3_border[410][235];

typedef struct
{
	u16_t s_x;
	u16_t s_y;
	u16_t e_x;
	u16_t e_y;
}Mp3_t;

Mp3_t coord_t[5];

int position = 1;

extern int decode(unsigned char const *start, unsigned long length, int fd);

#endif

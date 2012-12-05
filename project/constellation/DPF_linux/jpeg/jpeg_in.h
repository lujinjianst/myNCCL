#ifndef __JPEG_IN_H_
#define __JPEG_IN_H_

#include <math.h>
#include <signal.h>
#include <dirent.h>

#include "effects.h"
#include "../common/common.h"
#include "../font/font.h"

#define ROW_BLANK 20
#define COL_BLANK 15

#define UP_X (780.0/1024)
#define UP_Y (730.0/768)
#define DOWN_X (880.0/1024)
#define DOWN_Y (730.0/768)

typedef struct
{
	u16_t s_x;
	u16_t s_y;
	u16_t e_x;
	u16_t e_y;
}Coord;				//reduced picture's coordinate

Coord point[9];
u16_t enlarge_bpp[600][800];

extern u8_t *decode_jpeg (const char *filename, fb_info *jpeg_inf);
extern u32_t * rgb24to32(u8_t *buf24, fb_info jpeg_inf);
extern u16_t * rgb24to16(u8_t *buf24, fb_info jpeg_inf);
extern u8_t * scale24(u8_t *buf24, fb_info new_inf, fb_info jpeg_inf);

#endif

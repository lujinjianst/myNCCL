#ifndef __FONT_H_
#define __FONT_H_

#include <ft2build.h>
#include "../common/common.h"
#include FT_FREETYPE_H

int init_ft (const char *file, int size);
int display_string (const char * buf, int x, int y, fb_info fb_inf,u32_t color);

#endif

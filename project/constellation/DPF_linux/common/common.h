#ifndef __COMMON_H__
#define __COMMON_H__

#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <string.h>
#include <sys/ioctl.h>
#include <sys/mman.h>
#include <errno.h>
#include <linux/fb.h>
#include <unistd.h>
#include <dirent.h>

#define	FB_DEVICE	"/dev/fb0"

typedef unsigned char u8_t;
typedef unsigned int u16_t;
typedef unsigned int u32_t;

typedef struct					//information of framebuffer
{
   int w;
   int h;
   int bpp;
   char *fbmem;
} fb_info;

int fb_pixel(fb_info fb_inf, int x, int y, int color);

int init_frambuffer(fb_info *fb_inf);

void itoa(char *src, int num);

void cut_suffix(char *str);

int init_link(const char *pathname, FILE *fp, char file_type[]);

#endif

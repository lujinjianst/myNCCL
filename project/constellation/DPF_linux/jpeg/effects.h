#ifndef __EFFECTS_H_
#define __EFFECTS_H_

#include "../common/common.h"
#include <time.h>

void chess(fb_info fb_inf, u16_t *buf16);

void top_left_corner(fb_info fb_inf, u16_t *buf16);

void left_right(fb_info fb_inf, u16_t *buf16);

void circle(fb_info fb_inf, u16_t *buf16);

void rand_line(fb_info fb_inf, u16_t *buf16);

void fan_shaped(fb_info fb_inf, u16_t *buf16);

void fan_shaped_circle(fb_info fb_inf, u16_t *buf16);

void slide_corner(fb_info fb_inf, u16_t  *buf32);

void clock_wise(fb_info fb_inf,u16_t  *buf32);

void Dissolve(fb_info fb_inf, u16_t  *buf32);

void Rotation(fb_info fb_inf, u16_t  *buf32);

void display_fivestar(fb_info fb_inf, u16_t  *buf32);

void display_fivestar5(fb_info fb_inf, u16_t  *buf32);

void display_threestar5(fb_info fb_inf, u16_t  *buf32);

#endif

#ifndef __PLAY_IN_H_
#define __PLAY_IN_H_

void start_mp3(fb_info fb_inf);

void exchange_song(fb_info fb_inf, char *mode);

int list(fb_info fb_inf, char *str);

void draw_mp3(fb_info fb_inf, int *page_num, int pause_flag);

void draw_button(fb_info fb_inf, char *str);

int mp3_area(fb_info fb_inf, int x, int y);

int play_song(fb_info fb_inf, int page_num, int num);

int click_song(int x, int y);

void prev_song(fb_info fb_inf, int *page_num);

void next_song(fb_info fb_inf, int *page_num);

#endif

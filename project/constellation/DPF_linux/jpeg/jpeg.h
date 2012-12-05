#ifndef __JPEG_H_
#define __JPEG_H_

int display_jpeg(fb_info fb_inf);

void chess(fb_info fb_inf, u16_t *buf16);

void preview(fb_info fb_inf, int page_num);

void page_prev(fb_info fb_inf, int *page_num);

void page_next(fb_info fb_inf, int *page_num);

int picture_enlarge(fb_info fb_inf, int page_num, int pic_num);

int which_pic_click(fb_info fb_inf, int x, int y);

int enlarge_area(fb_info fb_inf, int x, int y);

void recover_enlarge_pic(fb_info fb_inf);

void disp_border(fb_info fb_inf, char *filename, int x, int y);

int init_link(const char *pathname, FILE *fp, char file_type[]);

int filename_list();

extern u8_t *decode_jpeg (const char *filename, fb_info *jpeg_inf);
extern u32_t * rgb24to32(u8_t *buf24, fb_info jpeg_inf);
extern u16_t * rgb24to16(u8_t *buf24, fb_info jpeg_inf);
extern u8_t * scale24(u8_t *buf24, fb_info new_inf, fb_info jpeg_inf);

#endif

#include "jpeg_in.h"

/*******************************************************************
 * Save Filename
 *******************************************************************/
int filename_list()
{
	FILE *fp = fopen("../jpeg/jpg.txt", "w+");

	init_link("../jpeg/constellation/",fp, ".jpg");

	fclose(fp);

	fp = NULL;

	return 0;
}

/*******************************************************************
 * Display Music Border
 *******************************************************************/
void disp_border(fb_info fb_inf, char *filename, int x, int y)
{
	int i, j;
	fb_info jpeg_inf;
	fb_info new_inf;

	new_inf.w = fb_inf.w * 0.3;
	new_inf.h = fb_inf.h * 0.5;

	u8_t *buf24 = decode_jpeg(filename, &jpeg_inf);
	u8_t *scale_buf = scale24(buf24, new_inf, jpeg_inf);
	u16_t *buf16 = rgb24to32(scale_buf, new_inf);
	
	for(i = 0; i < new_inf.h; i++)
		for (j = 0; j < new_inf.w; j++)
			fb_pixel(fb_inf, x+j, y+i, buf16[j + i * new_inf.w]);

	free(buf24);
	free(scale_buf);
	free(buf16);
}

/*******************************************************************
 * Display Jpeg
 *******************************************************************/
int display_jpeg(fb_info fb_inf)
{
	fb_info jpeg_inf;	
	u8_t *buf24; 
	u8_t * scale_buf; 
	u16_t *buf16;

	int k = 0;
	char filename[50];
	char tmp[20];
	FILE *fp = NULL;

	fp = fopen("../jpeg/jpg.txt", "r");
	if (fp == NULL)
	{
		printf("jpg file open error!\n");
		return 0;	
	}
	void (*effects[12])(fb_info, u16_t *);

	effects[0] = left_right;
	effects[1] = display_fivestar;
	effects[2] = rand_line;
	effects[3] = fan_shaped;
	effects[4] = Rotation;
	effects[5] = clock_wise;
	effects[6] = fan_shaped_circle;
	effects[7] = slide_corner;
	effects[8] = display_threestar5;
	effects[9] = chess;
	effects[10] =  Dissolve;
	effects[11] = display_fivestar5;

	while (1)
	{
		bzero(filename, sizeof(filename));
		bzero(tmp, sizeof(tmp));
		strcpy(filename, "../jpeg/constellation/");
		fgets(tmp, sizeof(tmp), fp);
		strcat(filename, tmp);
		filename[strlen(filename)-1] = '\0';

		buf24 = decode_jpeg(filename, &jpeg_inf);
		scale_buf = scale24(buf24, fb_inf, jpeg_inf);
		buf16 = rgb24to32(scale_buf, fb_inf);

		effects[k++](fb_inf, buf16);

		free(buf24);
		free(scale_buf);
		free(buf16);

		if (k > 11) 
		{
			k = 0;
			fclose(fp);
			fp = fopen("../jpeg/jpg.txt", "r");
			
			if (fp == NULL)
			{
				printf("jpg file open error!\n");
				return 0;	
			}
		}

		sleep(1);
	}

	return 0;
}

/*******************************************************************
 * Return A Jpeg Filename On The Basis Of Page Num And Picture Num
 *******************************************************************/
void which_jpeg_file(char *str, int page_num, int pic_num)
{
	int i = 0, k = 0;
	char tmp[20];
	FILE *fp = fopen("../jpeg/jpg.txt", "r");

	if (fp == NULL)
	{
		printf("jpg file open error.\n");
		return;
	}

	k = 9 * (page_num-1) + pic_num;

	for (i = 0; i < k && fgets(tmp, sizeof(tmp), fp) != NULL; i++);

	if (i == k) strcpy(str, tmp);

	fclose(fp);
} 

/*******************************************************************
 * Click Enlarge Area
 *******************************************************************/
int enlarge_area(fb_info fb_inf, int x, int y)
{
	fb_info new_inf;
	new_inf.w = fb_inf.w * 0.6;
	new_inf.h = fb_inf.h * 0.6;
	u32_t start_x = 200.0/1024*fb_inf.w;
	u32_t start_y = 100.0/768*fb_inf.h;

	if (x >= start_x && x <= start_x + new_inf.w && y >= start_y && y <= start_y + new_inf.h)
		return 1;

	return 0;
}

/*******************************************************************
 * Recover Enlarge Picture
 *******************************************************************/
void recover_enlarge_pic(fb_info fb_inf)
{
	int i, j;
	fb_info new_inf;
	new_inf.w = fb_inf.w * 0.6;
	new_inf.h = fb_inf.h * 0.6;
	u16_t start_x = 200.0/1024*fb_inf.w;
	u16_t start_y = 100.0/768*fb_inf.h;

	for(i = 0; i < new_inf.h; i++)
		for(j = 0; j < new_inf.w; j++)
			((u16_t *)fb_inf.fbmem)[fb_inf.w * (start_y + i) + start_x + j] = enlarge_bpp[i][j];
}

/*******************************************************************
 * Enlarge Jpeg
 *******************************************************************/
int picture_enlarge(fb_info fb_inf, int page_num, int pic_num)
{
	int i,j;
	char tmp[20];
	char filename[50];
	fb_info jpeg_inf;
	fb_info new_inf;

	u16_t start_x = 200.0/1024*fb_inf.w;
	u16_t start_y = 100.0/768*fb_inf.h;

	bzero(filename, sizeof(filename));
	bzero(tmp, sizeof(tmp));
	which_jpeg_file(tmp, page_num, pic_num);

	if (!strcmp(tmp, "")) return 1; 

	strcpy(filename, "../jpeg/constellation/");
	strcat(filename, tmp);
	filename[strlen(filename)-1] = '\0';

	new_inf.w = fb_inf.w * 0.6;
	new_inf.h = fb_inf.h * 0.6;
	u8_t *buf24 = decode_jpeg(filename, &jpeg_inf);
	u8_t *scale_buf = scale24(buf24, new_inf, jpeg_inf);
	u16_t *buf16 = rgb24to32(scale_buf, new_inf);

	for(i = 0; i < new_inf.h; i++)
		for(j = 0; j < new_inf.w; j++)
			enlarge_bpp[i][j] = ((u16_t *)fb_inf.fbmem)[fb_inf.w * (start_y + i) + start_x + j];

	for(i = 0; i < new_inf.h; i++)
	{
		for (j = 0; j < new_inf.w; j++)
			fb_pixel(fb_inf, start_x + j, (start_y + i), buf16[new_inf.w * i + j]);
	}
	
	free(buf24);
	free(scale_buf);
	free(buf16);

	return 0;
}

/*******************************************************************
 * Display Reduced Jpeg
 *******************************************************************/
void disp_reduce_pic(fb_info fb_inf, char *filename, int x, int y)
{
	if (!strcmp(filename, "../jpeg/constellation"))
		return;

	int i, j;
	fb_info jpeg_inf;
	fb_info new_inf;

	new_inf.w = fb_inf.w * 0.26;
	new_inf.h = fb_inf.h * 0.26;

	u8_t *buf24 = decode_jpeg(filename, &jpeg_inf);
	u8_t *scale_buf = scale24(buf24, new_inf, jpeg_inf);
	u16_t *buf16 = rgb24to32(scale_buf, new_inf);
	
	for(i = 0; i < new_inf.h; i++)
		for (j = 0; j < new_inf.w; j++)
			fb_pixel(fb_inf, x+j, y+i, buf16[j + i * new_inf.w]);

	free(buf24);
	free(scale_buf);
	free(buf16);
}

/*******************************************************************
 * Print Page
 *******************************************************************/
int print_page(fb_info fb_inf)
{

	if (init_ft("../font/fanxinshu.TTF", 24) != 0){
		fprintf(stderr, "Error initial font\n")	;
		return 1;
	}

	display_string("上一页", UP_X*fb_inf.w, UP_Y*fb_inf.h, fb_inf, 0xFFffff);
	display_string("下一页", DOWN_X*fb_inf.w, DOWN_Y*fb_inf.h, fb_inf, 0xffffFF);

	return 0;
}

/*******************************************************************
 * Save Reduced Picture's Coordinate
 *******************************************************************/
void init_coord(fb_info fb_inf)
{
	int i, j, x, y, k = 0;

	for (i = 0; i < 3; i++)
	{
		for (j = 0; j < 3; j++)
		{
			x = (fb_inf.w * 0.26) * j + ROW_BLANK * (j+3);
			y = (fb_inf.h * 0.26) * i + COL_BLANK * (i+2);
			point[k].s_x = x;
			point[k].s_y = y;
			point[k].e_x = x + (fb_inf.w * 0.26);
			point[k].e_y = y + (fb_inf.h * 0.26);			
			k++;
		}
	}
}

/*******************************************************************
 * Which Picture Click
 *******************************************************************/
int which_pic_click(fb_info fb_inf, int x, int y)
{
	int i;

	init_coord(fb_inf);

	for (i = 0; i < 9; i++)
		if (x >= point[i].s_x && x <= point[i].e_x && y >= point[i].s_y && y <= point[i].e_y)
			return (i+1);

	return 0;
}

/*******************************************************************
 * Pick Up Filename From File
 *******************************************************************/
int pickup_filename(fb_info fb_inf, int page_num)
{
	int i, j, x, y;
	char tmp[20], filename[50];
	FILE *fp = NULL;

	fp = fopen("../jpeg/jpg.txt", "r");
	if (fp == NULL)
	{
		printf("jpg file open error!\n");
		return -1;	
	}

	for (i = 9; i < 9*page_num; i++)
		fgets(tmp, sizeof(tmp), fp);

	for(i = 0; i < 3 && !feof(fp); i++)
	{
		for(j = 0; j < 3 && !feof(fp); j++)
		{
			bzero(filename, sizeof(filename));
			bzero(tmp, sizeof(tmp));
			strcpy(filename, "../jpeg/constellation/");
			fgets(tmp, sizeof(tmp), fp);
			strcat(filename, tmp);
			filename[strlen(filename)-1] = '\0';

			x = (fb_inf.w * 0.26) * j + ROW_BLANK * (j+3);
			y = (fb_inf.h * 0.26) * i + COL_BLANK * (i+2);

			disp_reduce_pic(fb_inf, filename, x, y);
		}
	}

	print_page(fb_inf);
	fclose(fp);

	return 0;
}

/*******************************************************************
 * Whether File Empty
 *******************************************************************/
int check_up_file(int page_num)
{
	FILE *fp = fopen("../jpeg/jpg.txt", "r");
	char tmp[20];
	int i;

	if (fp == NULL)
	{
		printf("jpg file open error.\n");
		return -1;
	}

	for (i = 0; i < (page_num-1)*9 && !feof(fp); i++)	
	{
		bzero(tmp, sizeof(tmp));
		fgets(tmp, sizeof(tmp), fp);
	}

	bzero(tmp, sizeof(tmp));
	fgets(tmp, sizeof(tmp), fp);

	if (!strcmp(tmp , ""))
		return 1;

	return 0;
}

/*******************************************************************
 * Print Background
 *******************************************************************/
void print_background(fb_info fb_inf)
{
	int i, j;
	fb_info jpeg_inf;
	u8_t *buf24 = decode_jpeg("../jpeg/welcome/welcome.jpg", &jpeg_inf);
	u8_t *scale_buf = scale24(buf24, fb_inf, jpeg_inf);
	u16_t *buf16 = rgb24to32(scale_buf, fb_inf);	

	for (i = 0; i < fb_inf.h; i++)
		for (j = 0; j < fb_inf.w; j++)
			fb_pixel(fb_inf, j, i, buf16[fb_inf.w * i + j]);

	free(buf24);
	free(scale_buf);
	free(buf16);
}

/*******************************************************************
 * Next Page Picture
 *******************************************************************/
void page_next(fb_info fb_inf, int *page_num)
{
	if (check_up_file(*page_num))
	{
		(*page_num)--;
		return;
	}
	print_background(fb_inf);

	pickup_filename(fb_inf, *page_num);
}

/*******************************************************************
 * Prev Page Picture
 *******************************************************************/
void page_prev(fb_info fb_inf, int *page_num)
{
	print_background(fb_inf);

	pickup_filename(fb_inf, *page_num);
}

/*******************************************************************
 * Preview
 *******************************************************************/
void preview(fb_info fb_inf, int page_num)
{
	pickup_filename(fb_inf, page_num);

	print_page(fb_inf);
}

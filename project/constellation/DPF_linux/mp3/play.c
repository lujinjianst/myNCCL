#include "play_in.h"

/*******************************************************************
 * Init Dsp
 *******************************************************************/
int set_dsp()
{
	int  id, ret;
	int  rate = 44100;
	int  format = AFMT_S16_LE;
	int  channels = 1;

	if((id = open("/dev/dsp", O_WRONLY)) < 0)
	{
		perror("dsp dev open error");
	}

	ret = ioctl(id, SNDCTL_DSP_SPEED, &rate);
	if ( ret == -1 ) {
		perror("ioctl rate error");
		return -1;
	}

	ret = ioctl(id, SNDCTL_DSP_SETFMT, &format);
	if ( ret == -1 ) {
		perror("ioctl format error");
		return -1;
	}

	ret = ioctl(id, SNDCTL_DSP_STEREO, &channels);
	if ( ret == -1 ) {
		perror("ioctl channel error");
		return -1;
	}

	return id;
}

/*******************************************************************
 * Save MP3 Filename
 *******************************************************************/
int mp3_file()
{
        FILE *fp = fopen("../mp3/mp3.txt", "w+");

        init_link("../mp3/music/",fp, ".mp3");

        fclose(fp);

        return 0;
}

/*******************************************************************
 * Save Area
 *******************************************************************/
void save_area(fb_info fb_inf, int start_x, int start_y, int width, int height, u16_t (*array)[width])
{
	int i, j;

	for (i = 0; i < height; i++)
		for (j = 0; j < width; j++)
			array[i][j] = ((u16_t *)fb_inf.fbmem)[fb_inf.w * (start_y + i) + (start_x + j)];
}

/*******************************************************************
 * Recover Area
 *******************************************************************/
void recover_area(fb_info fb_inf, int start_x, int start_y, int width, int height, u16_t (*array)[width])
{
	int i, j;

	for (i = 0; i < height; i++)
		for (j = 0; j < width; j++)
			((u16_t *)fb_inf.fbmem)[fb_inf.w * (start_y + i) + (start_x + j)] = array[i][j];
}

/*******************************************************************
 * Play
 *******************************************************************/
void play(int id, char *filename)
{
	int fd_mp3;

	while(1)
	{
		if((fd_mp3 = open(filename, O_RDONLY)) < 0){
			fprintf(stderr, "Open mp3 %s\n", strerror(errno));
			return;
		}

		struct stat stat;
		void *fdm;

		if((fstat(fd_mp3, &stat) == -1) || (stat.st_size == 0))
		{
			fprintf(stderr, "Error stat file");
			return;
		}

		fdm = mmap(0, stat.st_size, PROT_READ, MAP_SHARED, fd_mp3, 0);

		if (fdm == NULL)
		{
			fprintf(stderr, "mmap file %s\n", strerror(errno));
			exit(1);
		}

		decode(fdm, stat.st_size, id);
		munmap(fdm, stat.st_size);
	}
}

/*******************************************************************
 * Display List Border
 *******************************************************************/
void disp_mp3_border(fb_info fb_inf)
{
	int i = 0, j = 0;
	fb_info jpeg_inf;
	fb_info new_inf;
	int x = LIST_X*fb_inf.w;
	int y = LIST_Y*fb_inf.h;

	new_inf.w = 320.0/800*fb_inf.w;
	new_inf.h = 145.0/480*fb_inf.h;

	u8_t *buf24 = decode_jpeg("../mp3/frame/list.jpg", &jpeg_inf);
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
 * List MP3 Filename
 *******************************************************************/
int list_name(fb_info fb_inf, int page_num, char *str)
{
	int x = LIST_X*fb_inf.w;
	int y = LIST_Y*fb_inf.h;
	char filename[50];
	char tmp[50];
	int i;

	if (!strcmp(str, "prev") && page_num == 1) return 1;

	FILE *fp = fopen("../mp3/mp3.txt", "r");

	if (init_ft("../font/stsong.ttf", 14) != 0){
		fprintf(stderr, "Error initial font\n")	;
		return -1;
	}

	if (!strcmp(str, "prev"))
	{
		position = (page_num - 2) * 5 + 1;

		for (i = 0; i < (page_num-2) * 5; i++)
			fgets(tmp, sizeof(tmp), fp);
	}
	else
	{
		for (i = 0; i < (page_num-1) * 5; i++)
			fgets(tmp, sizeof(tmp), fp);
	}

	if (feof(fp)) return 1;

	if (strcmp(str, "list") != 0)
	{
		recover_area(fb_inf, x, y, 320.0/800*fb_inf.w, 145.0/480*fb_inf.h, mp3_border);
		disp_mp3_border(fb_inf);
	}

	for(i = 0; i < 100 && fgets(tmp, sizeof(tmp), fp) != NULL; i += 20)
	{
		bzero(filename, sizeof(filename));
		itoa(filename, position);
		cut_suffix(tmp);
		strcat(filename, tmp);
		display_string(filename, x+13, y+30+i, fb_inf, 0xffffff);
		position++;
	}

	fclose(fp);

	return 0;
}

/*******************************************************************
 * Prev Song
 *******************************************************************/
void prev_song(fb_info fb_inf, int *page_num)
{
	if (!list_name(fb_inf, *page_num, "prev"))
		(*page_num)--;
}

/*******************************************************************
 * Next Song
 *******************************************************************/
void next_song(fb_info fb_inf, int *page_num)
{
	if (!list_name(fb_inf, (*page_num)+1, "next"))
		(*page_num)++;
}

/*******************************************************************
 * Initialize Mp3 List Name Point
 *******************************************************************/
void init_name_point(fb_info fb_inf)
{
	int x = LIST_X*fb_inf.w + 13;
	int y = LIST_Y*fb_inf.h + 30;
	int i;

	for (i = 0; i < 5; i++)
	{
		coord_t[i].s_x = x;
		coord_t[i].s_y = y - 10;
		coord_t[i].e_x = x + 320;
		coord_t[i].e_y = y;
		y += 20;
	}
}

/*******************************************************************
 * Mp3 List
 *******************************************************************/
int list(fb_info fb_inf, char *str)
{
	int x = LIST_X*fb_inf.w;
	int y = LIST_Y*fb_inf.h;

	if (!strcmp(str, "list"))
	{
		save_area(fb_inf, x, y, 320.0/800*fb_inf.w, 145.0/480*fb_inf.h, mp3_border);
		disp_mp3_border(fb_inf);
		position = 1;
		list_name(fb_inf, 1, "list");
		init_name_point(fb_inf);
	}
	else if (!strcmp(str, "hide"))
		recover_area(fb_inf, x, y, 320.0/800*fb_inf.w, 145.0/480*fb_inf.h, mp3_border);

	return 0;
}

/*******************************************************************
 * Which Song Click
 *******************************************************************/
int click_song(int x, int y)
{
	int i; 

	for (i = 0; i < 5; i++)
		if (x >= coord_t[i].s_x && x <= coord_t[i].e_x && y >= coord_t[i].s_y && y <= coord_t[i].e_y)
			return (i+1);

	return 0;
}

/*******************************************************************
 * Play Click Song
 *******************************************************************/
void play_song(fb_info fb_inf, int page_num, int num)
{
	int id = set_dsp();
	int start_x = NAME_X*fb_inf.w;	
	int start_y = CUR_Y*fb_inf.h - 13;	
	int x = PAUSE_X*fb_inf.w;
	int y = PAUSE_Y*fb_inf.h;

	FILE *fp = fopen("../mp3/mp3.txt", "r");	
	char tmp[50];
	char filename[50];
	int i;

	strcpy(filename, "../mp3/music/");

	for (i = 0; i < (page_num-1)*5+num-1; i++)
		fgets(tmp, sizeof(tmp), fp);

	fgets(tmp, sizeof(tmp), fp);
	strcat(filename, tmp);
	filename[strlen(filename) - 1] = 0;	
	fclose(fp);

	fp = fopen("../mp3/mp3_tmp.txt", "w+");	//save current song
	fputs(tmp, fp);
	fclose(fp);

	recover_area(fb_inf, x, y, PAUSE_WIDTH*fb_inf.w, PAUSE_HEIGHT*fb_inf.h, pause_bpp);
	recover_area(fb_inf, start_x, start_y, CUR_NAME_WIDTH*fb_inf.w, CUR_NAME_HEIGHT*fb_inf.h, name_bpp);
	cut_suffix(tmp);
	display_string(tmp, NAME_X*fb_inf.w, NAME_Y*fb_inf.h, fb_inf, 0x8080);
	play(id, filename);
}

/*******************************************************************
 * Draw Button
 *******************************************************************/
void draw_button(fb_info fb_inf, char *str)
{
	int i, j;
	int x = PAUSE_X*fb_inf.w;
	int y = PAUSE_Y*fb_inf.h;
	char *filename = NULL;
	fb_info jpeg_inf;
	fb_info new_inf;

	new_inf.w = 76.0/800*fb_inf.w;
	new_inf.h = 36.0/480*fb_inf.h;

	if (!strcmp(str, "play"))
		filename = "../mp3/frame/play.jpg";
	else
	{
		recover_area(fb_inf, x, y, PAUSE_WIDTH*fb_inf.w, PAUSE_HEIGHT*fb_inf.h, pause_bpp);
		return;
	}

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
 * Assist For MP3 Menu Area
 *******************************************************************/
int mp3_area_assist(int c_x, int c_y, int p_x, int p_y, int width, int height)
{
	if (c_y <= p_y+height && c_y >= p_y && c_x <= p_x+width && c_x >= p_x)
		return 1;

	return 0;
}

/*******************************************************************
 * Which Area Mouse Click
 *******************************************************************/
int mp3_area(fb_info fb_inf, int x, int y)
{
	if (mp3_area_assist(x, y, PREV_X*fb_inf.w, PREV_Y*fb_inf.h, 70.0/800*fb_inf.w, 20.0/480*fb_inf.h))
	{
		return MP3_PREV;
	}
	else if (mp3_area_assist(x, y, NEXT_X*fb_inf.w, NEXT_Y*fb_inf.h, 70.0/800*fb_inf.w, 20.0/480*fb_inf.h))
	{
		return MP3_NEXT;
	}
	else if (mp3_area_assist(x, y, PAUSE_X*fb_inf.w, PAUSE_Y*fb_inf.h, 70.0/800*fb_inf.w, 20.0/480*fb_inf.h))
	{
		return MP3_PAUSE;
	}
	else if (mp3_area_assist(x, y, LIST_BUTTON_X*fb_inf.w, LIST_BUTTON_Y*fb_inf.h, 30.0/800*fb_inf.w, 25.0/480*fb_inf.h))
	{
		return MP3_LIST;
	}
	else if (mp3_area_assist(x, y, MODE_X*fb_inf.w, MODE_Y*fb_inf.h, 25.0/800*fb_inf.w, 25.0/480*fb_inf.h))
	{
		return MP3_MODE;
	}
	else if (mp3_area_assist(x, y, MP3_PREV_X*fb_inf.w, MP3_PREV_Y*fb_inf.h, 20.0/800*fb_inf.w, 20.0/480*fb_inf.h))
	{
		return MP3_PAGE_PREV;
	}
	else if (mp3_area_assist(x, y, MP3_NEXT_X*fb_inf.w, MP3_NEXT_Y*fb_inf.h, 30.0/800*fb_inf.w, 20.0/480*fb_inf.h))
	{
		return MP3_PAGE_NEXT;
	}
	else
		return 0;
}

/*******************************************************************
 * Draw Mp3 Menu
 *******************************************************************/
void draw_mp3(fb_info fb_inf, int *page_num, int pause_flag)
{
	FILE *fp = fopen("../mp3/mp3_tmp.txt", "r");
	char tmp[80];	
	fgets(tmp, sizeof(tmp), fp);			// get first mp3 file for printing screen
	fclose(fp);

	*page_num = 1;					// reset to the first page everytime draw mp3

	if (init_ft("../font/stsong.ttf", 14) != 0){
		fprintf(stderr, "Error initial font\n")	;
		return;
	}

	int i, j;
	fb_info jpeg_inf;
	int start_x = NAME_X*fb_inf.w;	
	int start_y = NAME_Y*fb_inf.h - 13;

	u8_t *buf24 = decode_jpeg("../mp3/frame/frame.jpg", &jpeg_inf);
	u8_t *scale_buf = scale24(buf24, fb_inf, jpeg_inf);
	u16_t *buf16 = rgb24to32(scale_buf, fb_inf);

	for(i = 0; i < fb_inf.h; i++)
		for (j = 0; j < fb_inf.w; j++)
			fb_pixel(fb_inf, j, i, buf16[j + i * fb_inf.w]);

	free(buf24);
	free(scale_buf);
	free(buf16);

	save_area(fb_inf, start_x, start_y, CUR_NAME_WIDTH*fb_inf.w, CUR_NAME_HEIGHT*fb_inf.h, name_bpp);
	start_x = PAUSE_X*fb_inf.w;	
	start_y = PAUSE_Y*fb_inf.h;
	save_area(fb_inf, start_x, start_y, PAUSE_WIDTH*fb_inf.w, PAUSE_HEIGHT*fb_inf.h, pause_bpp);

	if (pause_flag)		// if mp3 exits with PAUSE, then draw mp3 again must keep this status
		draw_button(fb_inf, "play");

	display_string("当前播放:", CUR_X*fb_inf.w, CUR_Y*fb_inf.h, fb_inf, 0x8080);
	cut_suffix(tmp);
	display_string(tmp, NAME_X*fb_inf.w, NAME_Y*fb_inf.h, fb_inf, 0x8080);
}

/*******************************************************************
 * Pickup Filename From Mp3 File
 *******************************************************************/
void mp3_filename(fb_info fb_inf, char *filename, char *mode)
{
	int count = 0;
	char str[80];
	char tmp[80];
	char prev_tmp[80];

	FILE *fp = fopen("../mp3/mp3.txt", "r");
	FILE *fp2 = fopen("../mp3/mp3_tmp.txt", "r");

	strcpy(filename, "../mp3/music/");
	fgets(str, sizeof(str), fp2);
	fgets(tmp, sizeof(tmp), fp);

	while (strcmp(tmp, str) != 0 && !feof(fp))
	{
		strcpy(prev_tmp, tmp);			//save current song's prev song
		fgets(tmp, sizeof(tmp), fp);
		count++;
	}

	if ((!count && !strcmp(mode, "prev")) || feof(fp)) 
	{
		strcat(filename, tmp);	
		filename[strlen(filename) - 1] = 0;
		cut_suffix(tmp);
		display_string(tmp, NAME_X*fb_inf.w, NAME_Y*fb_inf.h, fb_inf, 0x8080);
		return;
	}

	if (!strcmp(mode, "prev"))
		fseek(fp, -(strlen(tmp)+strlen(prev_tmp)), SEEK_CUR);	//seek file pointer from CURRENT
	fgets(tmp, sizeof(tmp), fp);

	fclose(fp);
	fclose(fp2);

	fp2 = fopen("../mp3/mp3_tmp.txt", "w+");	//save current song
	fputs(tmp, fp2);
	fclose(fp2);

	int start_x = NAME_X*fb_inf.w;	
	int start_y = NAME_Y*fb_inf.h - 13;	

	strcat(filename, tmp);	
	filename[strlen(filename) - 1] = 0;

	recover_area(fb_inf, start_x, start_y, CUR_NAME_WIDTH*fb_inf.w, CUR_NAME_HEIGHT*fb_inf.h, name_bpp);
	cut_suffix(tmp);
	display_string(tmp, NAME_X*fb_inf.w, NAME_Y*fb_inf.h, fb_inf, 0x8080);	
}

/*******************************************************************
 * Next Song Or Prev Song
 *******************************************************************/
void exchange_song(fb_info fb_inf, char *mode)
{
	char filename[80];
	int id = set_dsp();
	int x = PAUSE_X*fb_inf.w;
	int y = PAUSE_Y*fb_inf.h;

	mp3_filename(fb_inf, filename, mode);	

	recover_area(fb_inf, x, y, PAUSE_WIDTH*fb_inf.w, PAUSE_HEIGHT*fb_inf.h, pause_bpp);

	play(id, filename);
}

/*******************************************************************
 * Start Mp3 Player
 *******************************************************************/
void start_mp3(fb_info fb_inf)
{
	int id = set_dsp();
	char tmp[80];
	char filename[80];

	mp3_file();

	FILE *fp = fopen("../mp3/mp3.txt", "r");
	FILE *fw = fopen("../mp3/mp3_tmp.txt", "w+");

	if (fp == NULL)
	{
		printf("mp3 file open error.\n");
		return;
	}	

	bzero(tmp, sizeof(tmp));
	bzero(filename, sizeof(filename));
	strcpy(filename, "../mp3/music/");
	fgets(tmp, sizeof(tmp), fp);
	strcat(filename, tmp);
	fputs(tmp, fw);
	filename[strlen(filename) - 1] = 0;
	
	fclose(fp);
	fclose(fw);
	
	play(id, filename);
}

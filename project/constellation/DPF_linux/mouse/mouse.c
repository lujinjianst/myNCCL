#include "mouse_in.h"

/*******************************************************************
 * Initialize Mouse
 *******************************************************************/
int init_mouse()
{
	int fd;

	if((fd = open(MOUSE_DEVICE, O_RDWR)) < 0)
	{
		fprintf(stderr, "Error mouse open:%s\n", strerror(errno));
		exit(1);
	}
	
	return fd;
}

/*******************************************************************
 *Save Mouse
 *******************************************************************/
void save_mouse(fb_info fb_inf, int start_x, int start_y, int x, int y)
{
	int i,j;
	
	for (i = 0; i < y; i++)
		for (j = 0; j < x; j++)			
			buf[i*x+j] = ((u16_t *)fb_inf.fbmem)[fb_inf.w*(start_y+i)+start_x+j];
}

/*******************************************************************
 *Recover the Mouse Area
 *******************************************************************/
void recover(fb_info fb_inf, int start_x, int start_y, int x, int y)
{
	int i,j;
	
	for (i = 0; i < y; i++)
		for (j = 0; j < x; j++)			
			fb_pixel(fb_inf, start_x+j, start_y+i, buf[i*x+j]);
}

/*******************************************************************
 *Draw Mouse
 *******************************************************************/
void draw_mouse(fb_info fb_inf, int start_x, int start_y, int x, int y)
{
	int i,j;
	
	for (i = 0; i < y; i++)
		for (j = 0; j < x; j++)
			if (cursor_pixel[i*x+j] != T__)
				fb_pixel(fb_inf, start_x + j, start_y + i,cursor_pixel[i*x+j]);
}

/*******************************************************************
 * Mouse Can't Out of The Screen
 *******************************************************************/
void check_pow(fb_info fb_inf, int *x, int *y, int width, int height)
{
		if (*x < 0)	
			*x = 0;
		if (*y < 0)
			*y = 0;
		if (*x+width >= fb_inf.w-1)
			*x = fb_inf.w - C_WIDTH;
		if (*y+height >= fb_inf.h-1)
			*y = fb_inf.h - C_HEIGHT;
}

/*******************************************************************
 * Save Menu Area
 *******************************************************************/
void save_menu_area(fb_info fb_inf)
{
	int i, j;
	int start_x = 20.0/1024*fb_inf.w;
	int end_y = 330.0/768*fb_inf.h;
	int start_y = 40.0/768*fb_inf.h;
	int end_x = 100.0/1024*fb_inf.w;

	for (i = 0; i < end_y-start_y; i++)
		for (j = 0; j < end_x-start_x; j++)
			menu_bpp[i][j] = ((u16_t *)fb_inf.fbmem)[fb_inf.w * (start_y + i) + (start_x + j)];
}

/*******************************************************************
 * Recover Menu Area
 *******************************************************************/
void recover_menu_area(fb_info fb_inf)
{
	int i, j;
	int start_x = 20.0/1024*fb_inf.w;
	int end_y = 330.0/768*fb_inf.h;
	int start_y = 40.0/768*fb_inf.h;
	int end_x = 100.0/1024*fb_inf.w;

	for (i = 0; i < end_y-start_y; i++)
		for (j = 0; j < end_x-start_x; j++)
			fb_pixel(fb_inf, start_x + j, start_y + i, menu_bpp[i][j]);
}

/*******************************************************************
 * Welcome Screen
 *******************************************************************/
int welcome_screen(fb_info fb_inf)
{
	fb_info jpeg_inf;	
	u8_t *buf24; 
	u8_t * scale_buf; 
	u16_t *buf16;

	if (init_ft("../font/fanxinshu.TTF", 32) != 0){
		fprintf(stderr, "Error initial font\n")	;
		return 1;
	}

	buf24 = decode_jpeg("../jpeg/welcome/welcome.jpg", &jpeg_inf);
	scale_buf = scale24(buf24, fb_inf, jpeg_inf);
	buf16 = rgb24to32(scale_buf, fb_inf);	

	left_right(fb_inf, buf16);
	save_menu_area(fb_inf);

	display_string("音乐", (int)(MUSIC_X*fb_inf.w), (int)(MUSIC_Y*fb_inf.h), fb_inf, COLOR_A);
	display_string("预览", (int)(PREVIEW_X*fb_inf.w), (int)(PREVIEW_Y*fb_inf.h), fb_inf, COLOR_A);
	display_string("幻灯", (int)(SLIDE_X*fb_inf.w), (int)(SLIDE_Y*fb_inf.h), fb_inf, COLOR_A);
	display_string("退出", (int)(EXIT_X*fb_inf.w), (int)(EXIT_Y*fb_inf.h), fb_inf, COLOR_A);

	free(buf24);
	free(scale_buf);
	free(buf16);

	return 0;
}

/*******************************************************************
 * Assist For Menu Area
 *******************************************************************/
int area_little(int c_x, int c_y, int p_x, int p_y, int width, int height)
{
	if (c_y <= p_y && c_y >= p_y-height && c_x <= p_x+width && c_x >= p_x)
		return 1;

	return 0;
}

/*******************************************************************
 * Menu Area
 *******************************************************************/
int menu_area(fb_info fb_inf, int x, int y, int *flag)
{
	if (flag[0] == 0)
	{
		if (area_little(x, y, MUSIC_X*fb_inf.w, MUSIC_Y*fb_inf.h, 50, 40))
		{
			display_string("音乐", (int)(MUSIC_X*fb_inf.w), (int)(MUSIC_Y*fb_inf.h), fb_inf, COLOR_B);
			return MUSIC;
		}
		else if (area_little(x, y, PREVIEW_X*fb_inf.w, PREVIEW_Y*fb_inf.h, 50, 40))
		{
			display_string("预览", (int)(PREVIEW_X*fb_inf.w), (int)(PREVIEW_Y*fb_inf.h), fb_inf, COLOR_B);
			return PREVIEW;
		}
		else if (area_little(x, y, SLIDE_X*fb_inf.w, SLIDE_Y*fb_inf.h, 50, 40))
		{
			display_string("幻灯", (int)(SLIDE_X*fb_inf.w), (int)(SLIDE_Y*fb_inf.h), fb_inf, COLOR_B);
			return SLIDE;
		}
		else if (area_little(x, y, EXIT_X*fb_inf.w, EXIT_Y*fb_inf.h, 50, 40))
		{
			display_string("退出", (int)(EXIT_X*fb_inf.w), (int)(EXIT_Y*fb_inf.h), fb_inf, COLOR_B);
			return EXIT;
		}
	}

	return 0;
} 

/*******************************************************************
 * Move Leave The Words Recovering Its Source Color 
 *******************************************************************/
void mouse_leave(fb_info fb_inf, int x, int y, int flag, int *tag)
{
	if (tag[0] == 0)
	{
		if (!area_little(x, y, MUSIC_X*fb_inf.w, MUSIC_Y*fb_inf.h, 50, 40) && flag == MUSIC)
			display_string("音乐", (int)(MUSIC_X*fb_inf.w), (int)(MUSIC_Y*fb_inf.h), fb_inf, COLOR_A);

		else if (!area_little(x, y, PREVIEW_X*fb_inf.w, PREVIEW_Y*fb_inf.h, 50, 40) && flag == PREVIEW)
			display_string("预览", (int)(PREVIEW_X*fb_inf.w), (int)(PREVIEW_Y*fb_inf.h), fb_inf, COLOR_A);

		else if (!area_little(x, y, SLIDE_X*fb_inf.w, SLIDE_Y*fb_inf.h, 50, 40) && flag == SLIDE)
			display_string("幻灯", (int)(SLIDE_X*fb_inf.w), (int)(SLIDE_Y*fb_inf.h), fb_inf, COLOR_A);

		else if (!area_little(x, y, EXIT_X*fb_inf.w, EXIT_Y*fb_inf.h, 50, 40) && flag == EXIT)
			display_string("退出", (int)(EXIT_X*fb_inf.w), (int)(EXIT_Y*fb_inf.h), fb_inf, COLOR_A);
	}
}

/*******************************************************************
 * Page Area
 *******************************************************************/
int page_area(fb_info fb_inf, int x, int y)
{
	if (area_little(x, y, UP_X*fb_inf.w, UP_Y*fb_inf.h, 60, 20))
	{
		return PAGE_UP;
	}
	else if (area_little(x, y, DOWN_X*fb_inf.w, DOWN_Y*fb_inf.h, 60, 20))
	{
		return PAGE_DOWN;
	}
	else
		return 0;
}

/*******************************************************************
 * Slide Operate
 *******************************************************************/
void slide_operate(fb_info fb_inf, pid_t *pid, int x, int y, int click, int *flag, int *page_num)
{
	if (!(flag[0]) && click == 1 && menu_area(fb_inf, x, y, flag) == SLIDE)
	{
		flag[0] = 1;
		flag[2] = 2;
		recover_menu_area(fb_inf);
		save_mouse(fb_inf, x, y, C_WIDTH, C_HEIGHT);
		*pid = fork();
		if (*pid == 0)
		{
			display_jpeg(fb_inf);
			return;
		}
	}
	else if (2 == click && (flag[0] == 1))
	{
		if (flag[1] != 1)
		{
			kill(*pid, SIGUSR1);
			wait(NULL);
		}
		flag[0] = 0;
		flag[1] = 0;
		flag[2] = 0;
		*page_num = 1;
		welcome_screen(fb_inf);
		save_mouse(fb_inf, x, y, C_WIDTH, C_HEIGHT);
	}			
}

/*******************************************************************
 * Preview Operate
 *******************************************************************/
void preview_operate(fb_info fb_inf, int x, int y, int click, int *flag, int *page_num)
{
	int pic_num = 0;

	if (!(flag[0]) && click == 1 && menu_area(fb_inf, x, y, flag) == PREVIEW)
	{
		flag[0] = 1;
		flag[1] = 1;
		recover(fb_inf, x, y, C_WIDTH, C_HEIGHT);
		recover_menu_area(fb_inf);
		preview(fb_inf, *page_num);
		save_mouse(fb_inf, x, y, C_WIDTH, C_HEIGHT);
		return;
	}

	if (click == 1 && flag[0] == 1 && flag[2] == 0)
	{
		if ((pic_num = which_pic_click(fb_inf, x, y)) != 0)
		{
	                recover(fb_inf, x, y, C_WIDTH, C_HEIGHT);
			if(picture_enlarge(fb_inf, *page_num, pic_num)) return;

			save_mouse(fb_inf, x, y, C_WIDTH, C_HEIGHT);
			flag[2] = 1;
		}
		else if (page_area(fb_inf, x, y) == PAGE_UP)	
		{
			if (*page_num > 1)
			{
				(*page_num)--;
				page_prev(fb_inf, page_num);
			}
		}
		else if (page_area(fb_inf, x, y) == PAGE_DOWN)	
		{
			(*page_num)++;
			page_next(fb_inf, page_num);
		}
	}
	else if (click == 1 && flag[0] == 1 && flag[2] == 1)
	{
		if (enlarge_area(fb_inf, x, y))
		{
			flag[2] = 0;
			recover(fb_inf, x, y, C_WIDTH, C_HEIGHT);
			recover_enlarge_pic(fb_inf);
			save_mouse(fb_inf, x, y, C_WIDTH, C_HEIGHT);
		}
	}
}

/*******************************************************************
 * Music
 *******************************************************************/
void music(fb_info fb_inf, int x, int y, int click, pid_t *mp3_id, int *flag, int *page_num)
{
	int mp3_song_ret = 0;

	if (!(flag[0]) && click == 1 && menu_area(fb_inf, x, y, flag) == MUSIC)
	{
		flag[0] = 1;
		flag[1] = 1;
		flag[2] = 3;
		flag[4] = 0;			// reset list flag

		recover_menu_area(fb_inf);
		save_mouse(fb_inf, x, y, C_WIDTH, C_HEIGHT);
		draw_mp3(fb_inf, page_num, flag[3]);
	}
	else if (click == 1 && flag[0] == 1 && flag[2] == 3 && mp3_area(fb_inf, x, y) == MP3_PREV)
	{
		kill(*mp3_id, SIGKILL);
		wait(NULL);

		flag[3] = 0;			// reset mp3 pause flag

		*mp3_id = fork();
		if (*mp3_id == 0)
		{
			*mp3_id = getpid();
			exchange_song(fb_inf, "prev");
		}
	}
	else if (click == 1 && flag[0] == 1 && flag[2] == 3 && mp3_area(fb_inf, x, y) == MP3_NEXT)
	{
		kill(*mp3_id, SIGKILL);
		wait(NULL);
		flag[3] = 0;
		*mp3_id = fork();
		if (*mp3_id == 0)
		{
			*mp3_id = getpid();
			exchange_song(fb_inf, "next");
		}
	}
	else if (click == 1 && flag[0] == 1 && flag[2] == 3 && flag[3] == 0 && mp3_area(fb_inf, x, y) == MP3_PAUSE)
	{
		recover(fb_inf, x, y, C_WIDTH, C_HEIGHT);
		draw_button(fb_inf, "play");
		save_mouse(fb_inf, x, y, C_WIDTH, C_HEIGHT);
		kill(*mp3_id, SIGTSTP);
		flag[3] = 1;
	}
	else if (click == 1 && flag[0] == 1 && flag[2] == 3 && flag[3] == 1 && mp3_area(fb_inf, x, y) == MP3_PAUSE)
	{
		recover(fb_inf, x, y, C_WIDTH, C_HEIGHT);
		draw_button(fb_inf, "pause");
		save_mouse(fb_inf, x, y, C_WIDTH, C_HEIGHT);
		kill(*mp3_id, SIGCONT);
		flag[3] = 0;
	}
	else if (click == 1 && flag[0] == 1 && flag[2] == 3 && flag[4] == 0 && mp3_area(fb_inf, x, y) == MP3_LIST)
	{
		*page_num = 1;
		flag[4] = 1;
		recover(fb_inf, x, y, C_WIDTH, C_HEIGHT);
		list(fb_inf, "list");
		save_mouse(fb_inf, x, y, C_WIDTH, C_HEIGHT);
	}
	else if (click == 1 && flag[0] == 1 && flag[2] == 3 && flag[4] == 1 && mp3_area(fb_inf, x, y) == MP3_LIST)
	{
		recover(fb_inf, x, y, C_WIDTH, C_HEIGHT);
		list(fb_inf, "hide");
		flag[4] = 0;
		save_mouse(fb_inf, x, y, C_WIDTH, C_HEIGHT);
	}
	else if (click == 1 && flag[0] == 1 && flag[2] == 3 && mp3_area(fb_inf, x, y) == MP3_MODE)
	{
		
	}

	if (click == 1 && flag[0] == 1 && flag[2] == 3 && flag[4] == 1 && mp3_area(fb_inf, x, y) == MP3_PAGE_PREV)
	{
		prev_song(fb_inf, page_num);
	}
	else if (click == 1 && flag[0] == 1 && flag[2] == 3 && flag[4] == 1 && mp3_area(fb_inf, x, y) == MP3_PAGE_NEXT)
	{
		next_song(fb_inf, page_num);
	}
	else if (click == 1 && flag[0] == 1 && flag[2] == 3 && flag[4] == 1 && (mp3_song_ret = click_song(x, y)) != 0)
	{
		kill(*mp3_id, SIGKILL);
		wait(NULL);

		flag[3] = 0;			// reset mp3 pause flag
		*mp3_id = fork();
		if (*mp3_id == 0)
		{
			*mp3_id = getpid();
			play_song(fb_inf, *page_num, mp3_song_ret);
		}
	}
}

/*******************************************************************
 * Exit
 *******************************************************************/
int exit_dpf(fb_info fb_inf, int x, int y, int click, int *flag)
{
	if (click == 1 && flag[0] == 0 && menu_area(fb_inf, x, y, flag) == EXIT)
		return 1;
	
	return 0;
}

/*******************************************************************
 * Init Volumn
 *******************************************************************/
int init_volumn()
{
	int mixer_fd = open("/dev/mixer", O_RDWR);

	if (mixer_fd == -1)
	{
		perror("/dev/mixer init error.");
		return -1;
	}

	return mixer_fd;
}

/*******************************************************************
 * Volumn Control
 *******************************************************************/
void volumn_control(int mixer_fd, int roll, int *vol)
{
	if (roll == 1 && *vol > 0x0202)
		*vol -= 0x0202;

	else if (roll == -1 && *vol < 0x6464)
		*vol += 0x0202;

	if (ioctl(mixer_fd, MIXER_WRITE(SOUND_MIXER_WRITE_VOLUME), vol) == -1) 
	{
		perror("volumn control error.");
		return;
	}
}

/*******************************************************************
 * Mouse Control
 *******************************************************************/
int mouse_operate(fb_info fb_inf, pid_t *mp3_id)
{
	int fd = init_mouse();
	int mixer_fd = init_volumn();
	int vol = 0x6464;
	int ret = 0, page_num = 1, flag[5], mp3_page_num = 1;
	int m_x = fb_inf.w/2, m_y = fb_inf.h/2;
	s8_t buf[] = {0xf3, 0xc8, 0xf3, 0x64, 0xf3, 0x50};
	pid_t pid;
	flag[0] = 0;			// slide Or preview flag
	flag[1] = 0;			// terminate preview flag
	flag[2] = 0;			// enlarge picture Or cancle mouse in slide mode flag
	flag[3] = 0;			// mp3 pause And play flag
	flag[4] = 0;			// mp3 list flag

	if (write(fd, buf, sizeof(buf)) < sizeof(buf))
		fprintf(stderr, "Error write to mice device:%s\n", strerror(errno));

	save_mouse(fb_inf, m_x, m_y, C_WIDTH, C_HEIGHT);
	draw_mouse(fb_inf, m_x, m_y, C_WIDTH, C_HEIGHT);		

	while(1)	
	{					
		read(fd, buf, sizeof(fd));		
		mevent.button = buf[0] & 7;
		mevent.dx = buf[1];
		mevent.dy = -buf[2];
		mevent.dz = buf[3];			

		if (flag[2] != 2)				//screening mouse int slide mode
	                recover(fb_inf, m_x, m_y, C_WIDTH, C_HEIGHT);
		m_x += mevent.dx;
		m_y += mevent.dy;	

		if (flag[0] == 0 && flag[1] == 0)
			mouse_leave(fb_inf, m_x, m_y, ret, flag);	

		if (mixer_fd != -1)
			volumn_control(mixer_fd, mevent.dz, &vol);

		check_pow(fb_inf, &m_x, &m_y, C_WIDTH, C_HEIGHT);

		if (flag[2] != 2)				//screening mouse int slide mode
		{		
			save_mouse(fb_inf, m_x, m_y, C_WIDTH, C_HEIGHT);		
			draw_mouse(fb_inf, m_x, m_y, C_WIDTH, C_HEIGHT);
		}

		ret = menu_area(fb_inf, m_x, m_y, flag);
		preview_operate(fb_inf, m_x, m_y, mevent.button, flag, &page_num);		
		slide_operate(fb_inf, &pid, m_x, m_y, mevent.button, flag, &page_num);
		music(fb_inf, m_x, m_y, mevent.button, mp3_id, flag, &mp3_page_num);

		if (exit_dpf(fb_inf, m_x, m_y, mevent.button, flag))
		{
			close(mixer_fd);
			return 1;
		}
	}		
}

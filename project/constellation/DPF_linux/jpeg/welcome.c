#include "welcome_in.h"

/****************************************************************
 * draw line 
 *****************************************************************/
int draw_fb_line(fb_info fb_inf, int x1, int y1, int x2, int y2, u16_t *color)
{
	int dx = x2 - x1;
	int dy = y2 - y1;
	int p;
	int inc;

	inc = ((dx * dy) >= 0) ? 1 : -1;

	if(abs(dx) > abs(dy))
	{
		if(dx < 0)
		{
			swap(&x1, &x2);
			swap(&y1, &y2);
			dx = -dx;
			dy = -dy;
		}
		dy = (dy > 0) ? dy : -dy;
		p = 2 * dy - dx;
		while(x1++ <= x2)
		{
			if(!(x1-1<0 ||(x1-1>=fb_inf.w) || y1<0 ||y1>=fb_inf.h))
			{
				fb_pixel(fb_inf,x1 -1, y1, color[fb_inf.w*y1 + x1-1]);
			}
			if(p < 0)
			{
				p +=2 * dy;
			}
			else
			{
				y1 +=inc;
				p += 2* (dy -dx);
			}
		}
	}
	else
	{
		if(dy < 0)
		{
			swap(&x1,&x2);
			swap(&y1,&y2);
			dx = -dx;
			dy = -dy;
		}
		dx = (dx > 0 ) ? dx : -dx;
		p = 2 * dx - dy;
		while(y1++ < y2)
		{
			if(!(x1-1<0 ||x1>=fb_inf.w || y1-1 < 0 || y1-1 >= fb_inf.h))
			{
				fb_pixel(fb_inf,x1, y1 -1, color[fb_inf.w*(y1-1) + x1]);
			}
			if(p <0)
			{
				p +=2 *dx;
			}
			else
			{
				x1 += inc;
				p += 2 *(dx -dy);
			}
		}
	}
	return 0;
} 

/****************************************************************
 * draw five star 
 *****************************************************************/
void five_star(fb_info fb_inf,int center_x, int center_y, int r, double angle, u16_t *color)
{
	int a[5],b[5];
	int i;
	double pi =3.14159;
	for(i=0;i<5; i++)
	{
		a[i]=center_x + r * sin((angle + 72.0*i) * pi /180);
		b[i]=center_y - r * cos((angle + 72.0*i)*pi/180);//  + is down with, - is positive
	}
	for(i=0; i<3; i++)
	{
		draw_fb_line(fb_inf,a[i],b[i],a[i+2],b[i+2],color);
	}
	draw_fb_line(fb_inf,a[4],b[4],a[1],b[1],color);
	draw_fb_line(fb_inf,a[3],b[3],a[0],b[0],color);

}

/*******************************************************************
 * Display Background
 *******************************************************************/
int disp_background(char *filename, fb_info fb_inf)
{
	fb_info jpeg_inf;

	u8_t *buf24 = decode_jpeg(filename, &jpeg_inf);
	u8_t * scale_buf = scale24(buf24, fb_inf, jpeg_inf);
	u16_t *buf16 = rgb24to32(scale_buf, fb_inf);

	int i, j;

	for(i = 0; i < fb_inf.h; i++)
		for(j = 0; j < fb_inf.w; j++)
			fb_pixel(fb_inf, j, i, buf16[j + i * fb_inf.w]);

	free(buf24);
	free(scale_buf);
	free(buf16);

	return 0;
}

/*******************************************************************
 * Display Constellation
 *******************************************************************/
int disp_constellation(char *filename, fb_info fb_inf)
{
	fb_info jpeg_inf;

	u8_t *buf24 = decode_jpeg(filename, &jpeg_inf);
	u8_t * scale_buf = scale24(buf24, fb_inf, jpeg_inf);
	u16_t *buf16 = rgb24to32(scale_buf, fb_inf);

	int i;
	double angle;
	int tmp=fb_inf.w;
	angle =0;

	for(i = 0; i < tmp-RADIUS0*fb_inf.w; i++){
		five_star(fb_inf,COORDINET0_X*fb_inf.w,COORDINET0_Y*fb_inf.h, i, angle, buf16);
		angle = angle + 30;
		usleep(10000);
	}
	usleep(10000);
	angle =0;
	for(i = 0; i < tmp-RADIUS1*fb_inf.w; i++){
		five_star(fb_inf,COORDINET1_X*fb_inf.w,COORDINET1_Y*fb_inf.h, i, angle, buf16);
		angle = angle + 40;
		usleep(7000);
	}
	angle =0;
	usleep(7000);
	for(i = 0; i < tmp-RADIUS2*fb_inf.w; i++){
		five_star(fb_inf,COORDINET2_X*fb_inf.w,COORDINET2_Y*fb_inf.h, i,angle, buf16);
		angle = angle + 50;
		usleep(6000);
	}
	usleep(7000);
	for(i = 0; i < tmp-RADIUS3*fb_inf.w; i++){
		five_star(fb_inf,COORDINET3_X*fb_inf.w,COORDINET3_Y*fb_inf.h, i, angle, buf16);
		angle = angle + 60;
		usleep(5000);
	}
	usleep(5000);
	angle =0;
	for(i = 0; i < tmp-RADIUS4*fb_inf.w; i++){
		five_star(fb_inf,COORDINET4_X*fb_inf.w,COORDINET4_Y*fb_inf.h, i, angle, buf16);
		angle = angle + 40;
		usleep(4000);
	}
	angle =0;
	usleep(4000);
	for(i = 0; i < tmp-RADIUS5*fb_inf.w; i++){
		five_star(fb_inf,COORDINET5_X*fb_inf.w,COORDINET5_Y*fb_inf.h,i,angle, buf16);
		angle = angle + 30;
		usleep(3000);
	}
	angle =0;
	usleep(3000);
	for(i = 0; i < tmp-RADIUS6*fb_inf.w; i++){
		five_star(fb_inf,COORDINET6_X*fb_inf.w,COORDINET6_Y*fb_inf.h, i, angle, buf16);
		angle = angle + 30;
		usleep(2000);
	}
	angle =0;
	usleep(2000);
	for(i = 0; i < tmp-RADIUS7*fb_inf.w; i++){
		five_star(fb_inf,COORDINET7_X*fb_inf.w,COORDINET7_Y*fb_inf.h, i, angle, buf16);
		angle = angle + 30;
		usleep(1000);
	}
	angle =0;
	usleep(1000);
	for(i = 0; i < tmp-RADIUS8*fb_inf.w; i++){
		five_star(fb_inf,COORDINET8_X*fb_inf.w,COORDINET8_Y*fb_inf.h, i,angle, buf16);
		angle = angle + 30;
		usleep(500);
	}

	angle =0;
	usleep(2000);
	for(i = 0; i < tmp-RADIUS9*fb_inf.w; i++){
		five_star(fb_inf,COORDINET9_X*fb_inf.w,COORDINET9_Y*fb_inf.h, i,angle, buf16);

		angle = angle + 45;

		usleep(600);
	}
	angle=0;
	usleep(1000);
	for(i = 0; i < tmp-RADIUS10*fb_inf.w; i++){
		five_star(fb_inf,COORDINET10_X*fb_inf.w,COORDINET10_Y*fb_inf.h, i, angle, buf16);
		angle = angle + 45;
		usleep(1000);
	}

	angle=0;
	usleep(1000);
	for(i = 0; i < tmp-RADIUS11*fb_inf.w; i++){
		five_star(fb_inf,COORDINET11_X*fb_inf.w,COORDINET11_Y*fb_inf.h, i, angle, buf16);
		angle = angle + 60;
		usleep(1000);
	}
	for(i=fb_inf.h-1;i>=fb_inf.h/2-100;i--)
	{
		draw_fb_line(fb_inf, fb_inf.w/2, fb_inf.h-1, fb_inf.w-1, i, buf16);
		usleep(10000);

	}

	free(buf24);
	free(scale_buf);
	free(buf16);

	return 0;
}

/*******************************************************************
 * Print Exit Screen
 *******************************************************************/
int exit_screen(fb_info fb_inf)
{	
	int i,j;
	fb_info jpeg_inf;	

	u8_t *buf24 = decode_jpeg("../jpeg/end.jpg", &jpeg_inf);
	u8_t * scale_buf = scale24(buf24, fb_inf, jpeg_inf);
	u32_t *buf32 = rgb24to32(scale_buf, fb_inf);	

	for(i = fb_inf.h/2; i < fb_inf.h; ++i)
	{
		for (j = 0; j < fb_inf.w; ++j)
		{
			fb_pixel(fb_inf, j, fb_inf.h-i-1, buf32[j + (fb_inf.h-1-i) * fb_inf.w]);
		}
		for (j = 0; j < fb_inf.w; ++j)
		{
			fb_pixel(fb_inf, j, i, buf32[j + i * fb_inf.w]);
		}
	}

	sleep(1);
	for(i = 0; i < fb_inf.h/2; i++)
	{
		for (j = 0; j < fb_inf.w; ++j)
		{
			fb_pixel(fb_inf, j, i, 0x0);
		}
		for (j = 0; j < fb_inf.w; ++j)
		{
			fb_pixel(fb_inf, j, fb_inf.h-i-1,0x0);
		}

	}
	
	free(buf24);
	free(scale_buf);
	free(buf32);
	
	return 0;
}

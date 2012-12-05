#include "jpeg_in.h"

/***********************************Chess Effects**************************************/

/* Draw Line */
void draw_line(fb_info fb_inf, u16_t *buf16, int row, int start, int end)
{
	int i = 0;

	for (i = start; i < end; i++)
		fb_pixel(fb_inf, i, row, buf16[fb_inf.w * row + i]);
}

/* Draw Line Interleave Full of The Screen */
void chess_square(fb_info fb_inf, u16_t *buf16, int flag, int row, int width, int height)
{
	int i, k; 
	int end_i = fb_inf.h/height;
	int end_k = fb_inf.w/width;

	for (i = 0; i < end_i; i++)
	{
		for (k = 0; k < end_k; k++)
		{
			if (flag == 1)
			{
				if (i % 2 == 0 && k % 2 == 0)
					draw_line(fb_inf, buf16, height*i+row, width*k, width*(k+1));
				else if (i % 2 != 0 && k % 2 != 0)
					draw_line(fb_inf, buf16, height*i+row, width*k, width*(k+1));
			}
			else if (flag == 2)
			{
				if (i % 2 == 0 && k % 2 != 0)
					draw_line(fb_inf, buf16, height*i+row, width*k, width*(k+1));
				else if (i % 2 != 0 && k % 2 == 0)
					draw_line(fb_inf, buf16, height*i+row, width*k, width*(k+1));
			}
		}
	}
}

/* Draw Chess Effects */
void chess(fb_info fb_inf, u16_t *buf16)
{
	int i = 0; 
	int width = fb_inf.w/16;
	int height = fb_inf.h/12;

	for (i = 0; i < fb_inf.h/12; i++)
	{
		chess_square(fb_inf, buf16, 1, i, width, height);
		usleep(2000);
	}

	for (i = 0; i < fb_inf.h/12; i++)
	{
		chess_square(fb_inf, buf16, 2, i, width, height);
		usleep(2000);
	}
}

/********************************Top Left Corner Effects*************************************/

/* Draw Picture Largen Step by Step From Top Left Corner */
void draw_pic(u16_t *buf16, int width, int height, fb_info fb_inf)
{
	int i, j;

	for(i = 0; i < height; i++)
		for (j = 0; j < width; j++)
			fb_pixel(fb_inf, j, i, buf16[fb_inf.w-1-width+j + (fb_inf.h-1-height+i) * fb_inf.w]);
}

/* Draw From Top Left Corner */
void top_left_corner(fb_info fb_inf, u16_t *buf16)
{
	int i;

	for (i = 1; i < fb_inf.h; i++)
		draw_pic(buf16, 1.33*i, i, fb_inf);
}

/*********************************Left to Right Effects***************************************/

/* Draw From Left Right */
void left_right(fb_info fb_inf, u16_t *buf16)
{
	int i, j;

	for (i = 1; i <= fb_inf.w; i += 2)
	{
		for (j = 0; j < fb_inf.h; j++)
		{
			fb_pixel(fb_inf, i, j, buf16[fb_inf.w * j + i]);
			fb_pixel(fb_inf, fb_inf.w-i-1, j, buf16[fb_inf.w * j + fb_inf.w-i-1]);
		}
		usleep(100);
	}	
}

/************************************Circle Effects******************************************/

/* Draw Circle */
void circle(fb_info fb_inf, u16_t *buf16)
{
	int i, j, t;
	int k = sqrt(pow(fb_inf.w/2, 2) + pow(fb_inf.h/2, 2)) + 10;
	int center_x = fb_inf.w/2, center_y = fb_inf.h/2;

	for (t = 0; t < k; t += 10)	
		for(i = 0; i < fb_inf.h; i++)
			for(j = 0; j < fb_inf.w; j++)
				if(pow(i-center_y, 2) + pow(j-center_x, 2) <= (t * t))
					fb_pixel(fb_inf, j, i, buf16[j + i * fb_inf.w]);
}

/************************************Rand Line Effects***************************************/

/* Rand Line */	
void rand_line(fb_info fb_inf, u16_t *buf16)
{
	int i, k = 0;
	int array[fb_inf.h];

	for (i = 0; i < fb_inf.h; i++)
		array[i] = i;

	srand((unsigned)time(NULL));	

	for (i = 0; i < fb_inf.h; i++)
	{
		k = rand() % fb_inf.h;

		if (array[k] != -1)
		{
			draw_line(fb_inf, buf16, array[k], 0, fb_inf.w-1);
			array[k] = -1;
			usleep(20);
		}
		else i--;
	}
}

/************************************Fan_Shaped Effects***************************************/

/* Swap */
int swap(int *x, int *y)
{
	int tmp;

	tmp = *x;
	*x = *y;
	*y = tmp;

	return 0;
}

/* Draw Line From One Point to Another */
int line(fb_info fb_inf, u16_t *buf16, int x1, int y1, int x2, int y2)
{
	int dx = x2 - x1;
	int dy = y2 - y1;
	int p;
	int inc;

	inc = ((dx *dy) >= 0) ? 1:-1;

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
		p = 2 * dy -dx;
		while(x1++ <= x2)
		{
			fb_pixel(fb_inf, y1, x1-1, buf16[(y1-1) + x1 * fb_inf.w]);

			if(p < 0)
				p += 2 * dy;
			else{
				y1 += inc;
				p += 2 * (dy - dx);
			}
		}
	}else{
		if(dy < 0)
		{
			swap(&x1, &x2);
			swap(&y1, &y2);
			dx = -dx;
			dy = -dy;
		}
		dx = (dx > 0) ? dx : -dx;
		p = 2 * dx -dy;
		while(y1++ < y2)
		{
			fb_pixel(fb_inf, y1-1, x1, buf16[y1 + x1 * fb_inf.w]);

			if(p < 0)
				p += 2 * dx;
			else{
				x1 += inc;
				p += 2 * (dx -dy);
			}                           
		}
	}
	return 0;
}

/* Fan Shaped */
void fan_shaped(fb_info fb_inf, u16_t *buf16)
{
	int x1=0, y1=0, x2=fb_inf.h-2, y2=fb_inf.w-2, x3=0, y3=fb_inf.w-2, x4=fb_inf.h-2, y4=0;
	
	while(y3 > 0)
	{
		line(fb_inf, buf16, x1, y1, x2, y2);
		line(fb_inf, buf16, x3, y3, x4, y4);

		if(x1 < fb_inf.h) x1++;
		else x1 = fb_inf.h-1;

		if(x2 >= 0) x2--;
		else x2 = 0;

		y3--; y4++;
	}
}

/**********************************Fan Shaped Circle Effects*************************************/

/* Fan Shaped Circle */
void fan_shaped_circle(fb_info fb_inf, u16_t *buf32)
{
	int x1=fb_inf.w/2, y1=fb_inf.h/2; 
	int i=fb_inf.w/2;
	int j= 0;
	int tmp =0;

	while(i>0)
	{ 
		line(fb_inf,buf32,y1,x1,0,i);
		line(fb_inf, buf32,y1,x1, 0,x1+tmp);
		tmp++;
		i--;
	}
	tmp=0;
	while(j<=fb_inf.h-1)
	{
		line(fb_inf,buf32,y1,x1,j,0);
		line(fb_inf, buf32,y1,x1, j,fb_inf.w-1);
		j++;

		while(j>fb_inf.h-2 && tmp <x1)
		{
			line(fb_inf,buf32,y1,x1,j,tmp);
			line(fb_inf, buf32,y1,x1, j,fb_inf.w-1-tmp);
			tmp++;
		}
	}
}

/**********************************Box Decrease Effects*************************************/

/* draw row line */
int draw_rline(const fb_info fb_inf, u16_t *buf32,int x,int y,int len)
{
	int i;
	for(i=0;i<len;i++)
	{
		//fb_pixel(fb_inf, x+i, y, buf32[fb_inf.w * (x+i)+y]);
		fb_pixel(fb_inf, x+i, y, buf32[fb_inf.w * y+x+i]);
	}
	return 0;
}

/* draw col line */
int draw_hline(const fb_info fb_inf, u16_t  *buf32,int x,int y,int len)
{
	int i;
	for(i=0;i<len;i++)
	{
		fb_pixel(fb_inf, x, y+i, buf32[fb_inf.w *(y+i)+x]);

	}
	return 0;
}

/* from full screen to center */
void slide_corner(fb_info fb_inf, u16_t  *buf32)
{
	int tmp = 0;
	int i=0;
	int j=0;
	while(tmp<400.0/1024*fb_inf.w)
	{  
		draw_rline(fb_inf,buf32,i,j,fb_inf.w-1);

		draw_hline(fb_inf,buf32,i,j,fb_inf.h-1-i);

		draw_rline(fb_inf,buf32,j,fb_inf.h-i-1,fb_inf.w-i-1);

		draw_hline(fb_inf,buf32,fb_inf.w-i-1,j,fb_inf.h-i-1);

		usleep(7000);

		i++;
		j++;
		tmp++;
	}
}

/**********************************Clockwise Rotate Effects*************************************/

/* clockwise */
void clock_wise(fb_info fb_inf,u16_t *buf32)
{
	int x1=fb_inf.w/2, y1=fb_inf.h/2; 
	int i=fb_inf.w/2;
	int j= 0;
	int tmp =0;

	while(tmp<x1)
	{ 
		line(fb_inf, buf32,y1,x1, 0,x1+tmp);
		tmp++;
	}

	tmp=0;

	while(j<=fb_inf.h-1)
	{
		line(fb_inf, buf32,y1,x1, j,fb_inf.w-1);
		j++;
	}

	while(tmp<fb_inf.w)
	{

		line(fb_inf, buf32,y1,x1, fb_inf.h-1,fb_inf.w-1-tmp);
		tmp++;
	}

	j=fb_inf.h-1;

	while(j>0)
	{
		line(fb_inf,buf32,y1,x1,j,0);
		j--;
	}

	i=0;

	while(i<x1)
	{ 
		line(fb_inf,buf32,y1,x1,0,i);
		i++;
	}

	return ;
}

/**********************************Rand Point Effects*************************************/

/* rand point */
void Dissolve(fb_info fb_inf, u16_t  *buf32)
{
	int i,j, k = 0,k1=0,x;
	int array[fb_inf.w][fb_inf.h];

	for (i = 0; i < fb_inf.w; i++)
		for (j = 0; j < fb_inf.h; j++)
		{ array[i][j] = j;}

	srand((unsigned)time(NULL));
	x=fb_inf.h*fb_inf.w;
	for (i = 0; i < x-200; i++)
	{
		k = rand() % fb_inf.h;
		k1 = rand() % fb_inf.w;

		if (array[k1][k] != -1)
		{

			fb_pixel(fb_inf,k1,k,buf32[k1+k*fb_inf.w]);
			array[k1][k] = -1;
		}
		else i--;
	}
}

/**********************************Many Line Rotate Effects*************************************/

/* many line rotate */
void Rotation(fb_info fb_inf, u16_t  *buf32)
{
	int j,i;
	for(i=1;i<=fb_inf.h-1;i+=40)
	{
		for(j=i;j<=i+20;j++)
		{
			if(fb_inf.h-j<0) break;
			line(fb_inf, buf32, j, 1, fb_inf.h-j, fb_inf.w-1);

		}
		usleep(1);
	}

	for(i=1;i<=fb_inf.w-1;i+=40)
	{
		for(j=i;j<=i+20;j++)
		{
			line(fb_inf, buf32,fb_inf.h-1, j, 1, fb_inf.w-j);
		}
		usleep(1);
	}

	for(i=21;i<=fb_inf.h-1;i+=40)
	{
		for(j=i;j<=i+20;j++)
		{
			line(fb_inf, buf32, j, 1, fb_inf.h-j, fb_inf.w-1);
		}
		usleep(1);
	}
	for(i=21;i<=fb_inf.w-1;i+=40)
	{
		for(j=i;j<=i+20;j++)
		{
			line(fb_inf, buf32, fb_inf.h-1, j, 1, fb_inf.w-j);
		}
		usleep(1);
	}

}

/**********************************Draw Five Star Effects*************************************/
/* draw line */
int draw_fb_line1(fb_info fb_inf, int x1, int y1, int x2, int y2, u16_t  * color)
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
		while((x1++) <= x2)
		{
			if(!(x1-1<0 ||x1-1>=fb_inf.w || y1<0 || y1>=fb_inf.h))
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

/* draw five star */
void five_star1(fb_info fb_inf,int center_x, int center_y, int r, double angle, u16_t  *color)
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
		draw_fb_line1(fb_inf,a[i],b[i],a[i+2],b[i+2],color);
	}
	draw_fb_line1(fb_inf,a[4],b[4],a[1],b[1],color);
	draw_fb_line1(fb_inf,a[3],b[3],a[0],b[0],color);
}

/**********************************Draw Any Star Effects*************************************/

/* draw any star */
void polygon_star(fb_info fb_inf,int center_x, int center_y, int r, int angle, int many, u16_t *color)
{
	int a[many],b[many];
	int i;
	double pi =3.14159;

	for(i=0;i<many; i++)
	{
		a[i]=center_x + r * sin((angle + (360.0/many)*i) * pi/180);
		b[i]=center_y - r * cos((angle + (360.0/many)*i) * pi/180);//  + is down with, - is positive
	}

	for(i=0; i<many-1; i++)
	{
		draw_fb_line1(fb_inf,a[i],b[i],a[i+1],b[i+1],color);
	}
	draw_fb_line1(fb_inf,a[i],b[i],a[0],b[0],color);

}

/********************************One Star Enlarge From Center Effects***********************************/

/* one star */
void display_fivestar(fb_info fb_inf, u16_t  *buf32)
{
	int i;
	int sumusleep = 500;
	double angle = 0;

	/* five star xuan zuan */
	for(i = 0; i < fb_inf.w+300; i++){
		five_star1(fb_inf,fb_inf.w/2, fb_inf.h/2, i, angle, buf32);
		angle = angle + 30;
		if (sumusleep > 300)
			usleep(sumusleep--);
	}

	return ;
}

/********************************Five Star Enlarge Effects***********************************/

/* five star */
void display_fivestar5(fb_info fb_inf, u16_t  *buf32)
{
	int i;
	double angle = 0;
	int m =6;
	int sumusleep = 500;
	int sumusleep2 = 20;
	for(i = 0; i < fb_inf.w/4; i++){
		five_star1(fb_inf,fb_inf.w/m, fb_inf.h/m, i, angle, buf32);
		five_star1(fb_inf,fb_inf.w/m*(m-1), fb_inf.h/m, i, angle, buf32);
		five_star1(fb_inf,fb_inf.w/m, fb_inf.h/m*(m-1), i, angle, buf32);
		five_star1(fb_inf,fb_inf.w/m*(m-1), fb_inf.h/m*(m-1), i, angle, buf32);
		angle = angle + 30;
		if (sumusleep2 > 0)
			usleep(sumusleep2--);
	}
	for(i = 0; i < fb_inf.w; i++){
		five_star1(fb_inf,fb_inf.w/2, fb_inf.h/2, i, angle, buf32);
		angle = angle + 30;
		if (sumusleep > 400)
			usleep(sumusleep--);
	}

	return ;
}

/********************************Five Triangle Enlarge Effects***********************************/

/* five triangle */
void display_threestar5(fb_info fb_inf, u16_t  *buf32)
{
	int i, j;
	for (j=1; j<fb_inf.w/2; j=j+3)
	{
		for(i = 0; i < 120; i++){
			polygon_star(fb_inf,fb_inf.w/4, fb_inf.h/4, j, i, 3 , buf32);
			polygon_star(fb_inf,fb_inf.w/4*3, fb_inf.h/4, j, i, 3 , buf32);
			polygon_star(fb_inf,fb_inf.w/4, fb_inf.h/4*3, j, i, 3 , buf32);
			polygon_star(fb_inf,fb_inf.w/4*3, fb_inf.h/4*3, j, i, 3 , buf32);
			polygon_star(fb_inf,fb_inf.w/2, fb_inf.h/2, j, i, 3 , buf32);
			if (i % 10 ==0)
				usleep(1);
		}
		if (j>30)
			j=j+30;
	}
	return ;
}

#include "common.h"

/*******************************************************************
 *Init Framebuffer
 *******************************************************************/
int init_frambuffer(fb_info *fb_inf)
{	
	int fd,prot;
	size_t length;
	struct fb_var_screeninfo fb_var;

	if ((fd = open(FB_DEVICE, O_RDWR)) < 0)
	{
		fprintf(stderr, "Open %s failed:%s\n", FB_DEVICE, strerror(errno));
		return -1;
	}

	if (ioctl(fd, FBIOGET_VSCREENINFO, &fb_var) < 0)
	{
		fprintf(stderr, "fb ioctl failed:%s\n", strerror(errno));
		return -1;
	}
	
	fb_inf->w = fb_var.xres;
	fb_inf->h = fb_var.yres;
	fb_inf->bpp = fb_var.bits_per_pixel;

	length = fb_inf->w * fb_inf->h * fb_inf->bpp / 8;
	prot = 	PROT_READ | PROT_WRITE;
	fb_inf->fbmem = mmap(0, length, prot, MAP_SHARED, fd, 0); 
	if (fb_inf->fbmem == MAP_FAILED)
	{
		fprintf(stderr, "fb mmap failed:%s\n", strerror(errno));
		return -1;
	}
	
	close(fd);

	return 0;
}

/*******************************************************************
 *Put Color in Memory
 *******************************************************************/
int fb_pixel(fb_info fb_inf, int x, int y, int color)
{
	u8_t *pos = (u8_t *)fb_inf.fbmem + (fb_inf.w * y + x) * fb_inf.bpp/8;

	switch (fb_inf.bpp)
	{
	case 32:
		*(pos+3) = color >> 24;
	case 24:
		*(pos+2) = color >> 16;
	case 16:
		*(pos+1) = color >> 8;
	case 8:
		*pos = color;
		return 0;
	default:
		return -1;
	}

	return -1;
}

/*******************************************************************
 * Integer to String
 *******************************************************************/
void itoa(char *src, int num)
{
	int i = 0, j = 0;
	char ch[5];
	char tmp = 0;
	bzero(ch, sizeof(ch));

	for (i = 0; num; num /= 10)
		ch[i++] = num % 10 + '0'; 

	ch[i] = '\0';

	for (i = i-1, j = 0; j < i; i--, j++)
	{
		tmp = ch[i];
		ch[i] = ch[j];
		ch[j] = tmp;
	}

	strcat(src, ch);
	strcat(src, ".");
}

/*******************************************************************
 * Read Filename List
 *******************************************************************/
int init_link(const char *pathname, FILE *fp, char file_type[])
{
	DIR *dp;
	struct dirent *sdir;

	if((dp = opendir(pathname)) == NULL)
		return -1;

	while((sdir = readdir(dp)) != NULL)
		if(sdir->d_type == DT_REG)
		{
			if (strstr(sdir->d_name, file_type) != NULL)
			{
				strcat(sdir->d_name, "\n");
				fwrite(sdir->d_name,strlen(sdir->d_name),1, fp);
			}
		}

	closedir(dp);

	return 0;
}

/*******************************************************************
 * Cut File Suffix
 *******************************************************************/
void cut_suffix(char *str)
{
	int count = 0;
	char *p = str;

	while (*(p++) != '.')	
		count++;

	str[count] = '\0';
}

#include "font.h"

static FT_Library library;
static FT_Face face;

/* default font */
static char *fontfile;
static int psize = 32;

static u16_t s_font_utf8_to_unicode (const unsigned char *utf8, int *len)
{
	unsigned short unicode;
	unicode = utf8[0];
	if (unicode >= 0xF0)
	{
		unicode = (unsigned short) (utf8[0] & 0x07) << 18;
		unicode |= (unsigned short) (utf8[1] & 0x3F) << 12;
		unicode |= (unsigned short) (utf8[2] & 0x3F) << 6;
		unicode |= (unsigned short) (utf8[3] & 0x3F);
		*len = 4;
	}
	else if (unicode >= 0xE0)
	{
		unicode = (unsigned short) (utf8[0] & 0x0F) << 12;
		unicode |= (unsigned short) (utf8[1] & 0x3F) << 6;
		unicode |= (unsigned short) (utf8[2] & 0x3F);
		*len = 3;
	}
	else if (unicode >= 0xC0)
	{
		unicode = (unsigned short) (utf8[0] & 0x1F) << 6;
		unicode |= (unsigned short) (utf8[1] & 0x3F);
		*len = 2;
	}
	else {
		*len = 1;
	}
	return unicode;
}

int init_ft (const char *file, int size)
{
	/* XXX: font size */
	if(size != 0)
		psize = size;

	/* XXX: font file */
	if (file != NULL)
		fontfile = (char *)file;
	
	if (FT_Init_FreeType (&library)
	    || FT_New_Face (library, fontfile, 0, &face)
	    || FT_Set_Pixel_Sizes (face, psize, 0)) 	{
		perror("Error initial font file");
		
		return 1;
	}

	return 0;
}

int display_font(const char *code,int *len,int x,int y,fb_info fb, u32_t color)
{
	unsigned int ucode;
	FT_UInt glyph_index;
	int row, pixel;

	ucode = s_font_utf8_to_unicode ((u8_t*)code, len);

	if ((glyph_index = FT_Get_Char_Index (face, ucode)) == 0)
		return 2;

	if (FT_Load_Glyph (face, glyph_index, FT_LOAD_DEFAULT))	
		return 3;

	if (FT_Render_Glyph (face->glyph, FT_RENDER_MODE_MONO))	
		return 4;
 
	y -= face->glyph->bitmap_top;

	for (row = 0; row < face->glyph->bitmap.rows; ++row,y++)	{
		/* FIXME: why?? */
//		for (pixel = 0; pixel < face->glyph->bitmap_left; ++pixel)
//		;            
		for (pixel = 0; pixel < face->glyph->bitmap.width; ++pixel)		{
			if (face->glyph->bitmap.buffer[row * face->glyph->bitmap.pitch + pixel / 8]
			    & (0xC0 >> (pixel % 8)))			

				fb_pixel(fb, x+pixel, y, color);
		}
	}

	return 0;
}

/* display string */
int display_string (const char * buf, int x, int y, fb_info fb_inf,u32_t color)
{
	int len;

	while (buf[0] != '\0') 	{	
		if (display_font(buf,&len,x,y,fb_inf, color)) return 1;
		buf += len;
		x += psize;
	}

	return 0;
}


//< init structs and row/col pointers
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdarg.h>
#include <limits.h>



#include "../cfg/cfg.h"



#define PNG_DEBUG 3
#include <png.h>

#define FRM 20


#define COL_TYPE 1
#define BIT_DEPTH 1

typedef struct Img {
	I h;
	I w;
	png_byte col;
	png_byte b_depth;
	png_bytep *row_pointers;
}	pImg;

typedef pImg* img;

void abort_(const char * s, ...)
{
		va_list args;
		va_start(args, s);
		vfprintf(stderr, s, args);
		fprintf(stderr, "\n");
		va_end(args);
		abort();
}



// int width, height;

int number_of_passes;
png_structp png_ptr;
png_infop info_ptr;





static pImg STR;

static img IMG = &STR;


static C file[PATH_MAX + 1];


img read_png_file(S file_name)				//<	read png file file_name and return struct 
{
		I y;
		char header[8];	// 8 is the maximum size that can be checked
		// C new[PATH_MAX + 1];
		img img_ = malloc(SZ(pImg));												//<	allocate structure
		png_bytep* rows;



		/* open file and test for it being a png */
		FILE *fp = fopen(file_name, "rb");




		if (!fp)
				abort_("[read_png_file] File %s could not be opened for reading", file_name);

		fread(header, 1, 8, fp);

		if (png_sig_cmp((png_const_bytep)header, 0, 8))
				abort_("[read_png_file] File %s is not recognized as a PNG file", file_name);

		/* initialize stuff */
		png_ptr = png_create_read_struct(PNG_LIBPNG_VER_STRING, NULL, NULL, NULL);

		if (!png_ptr)
				abort_("[read_png_file] png_create_read_struct failed");

		info_ptr = png_create_info_struct(png_ptr);

		if (!info_ptr)
				abort_("[read_png_file] png_create_info_struct failed");

		if (setjmp(png_jmpbuf(png_ptr)))
				abort_("[read_png_file] Error during init_io");

		png_init_io(png_ptr, fp);
		png_set_sig_bytes(png_ptr, 8);

		png_read_info(png_ptr, info_ptr);

		img_->w = png_get_image_width(png_ptr, info_ptr);
		img_->h = png_get_image_height(png_ptr, info_ptr);
		img_->col = png_get_color_type(png_ptr, info_ptr);
		img_->b_depth = png_get_bit_depth(png_ptr, info_ptr);

		number_of_passes = png_set_interlace_handling(png_ptr);
		png_read_update_info(png_ptr, info_ptr);

		/* read file */
		if (setjmp(png_jmpbuf(png_ptr)))
				abort_("[read_png_file] Error during read_image");

		rows = (png_bytep*) malloc(sizeof(png_bytep) * img_->h);					//< allocate row pointers

		for (y = 0; y < img_->h; y++)
				rows[y] = (png_byte*) malloc(png_get_rowbytes(png_ptr,info_ptr));	//<	allocate each row

		png_read_image(png_ptr, rows);

		img_->row_pointers = rows;													

		fclose(fp);
	
		R img_;
}


int main()
{
	O("GOD\n");
	img a = read_png_file("../../pic/dog/0/die_1.png");

	O("bit depth --> %d\ncolour type --> %d\n", a->b_depth, a->col);
	return 0;


}



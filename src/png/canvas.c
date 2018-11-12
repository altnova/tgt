//< init structs and row/col pointers
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdarg.h>
#include <limits.h>
#include "../___.h"
#include "../cfg.h"
#include "../base/mains.h"

#define PNG_DEBUG 3
#include <png.h>

#define FRM 20

ext I height;
ext I width;

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



void info_out(img img_)							//< write struct info into stdout
{
	O("IMG:\th --> %d;\t w --> %d;\n\tdep --> %d;\t col --> %d;\n\n", img_->h, img_->w, img_->b_depth, img_->col);
}

void copy_byte(png_byte *a, png_byte *b, I j)	//< copy j png_bytes from a to b
{
	for (I i = 0; i < j; i++)
		a[i] = b[i];
}

void free_img(img img_)							//<	free struct
{
	for (I i = 0; i < img_->h; i++)
		free(img_->row_pointers[i]);
	free(img_->row_pointers);
	free(img_);
}

img write_png_file(S file_name, img img_)		//<	write png file with name file_name with info from struct
{
	int y;
		/* create file */
		FILE *fp = fopen_(file_name, "wb");

		// O("WRITE '%s'\n", file_name);

		if (!fp)
				abort_("[write_png_file] File %s could not be opened for writing", file_name);

		/* initialize stuff */
		png_ptr = png_create_write_struct(PNG_LIBPNG_VER_STRING, NULL, NULL, NULL);

		if (!png_ptr)
				abort_("[write_png_file] png_create_write_struct failed");

		info_ptr = png_create_info_struct(png_ptr);
		if (!info_ptr)
				abort_("[write_png_file] png_create_info_struct failed");

		if (setjmp(png_jmpbuf(png_ptr)))
				abort_("[write_png_file] Error during init_io");

		png_init_io(png_ptr, fp);

		/* write header */
		if (setjmp(png_jmpbuf(png_ptr)))
				abort_("[write_png_file] Error during writing header");

		png_set_IHDR(png_ptr, info_ptr, img_->w, img_->h,
					 img_->b_depth, img_->col, PNG_INTERLACE_NONE,
					 PNG_COMPRESSION_TYPE_BASE, PNG_FILTER_TYPE_BASE);
 
		png_write_info(png_ptr, info_ptr);
 
		/* write bytes */
		if (setjmp(png_jmpbuf(png_ptr)))
				abort_("[write_png_file] Error during writing bytes");

		png_write_image(png_ptr, img_->row_pointers);


		/* end write */
		if (setjmp(png_jmpbuf(png_ptr)))
				abort_("[write_png_file] Error during end of write");

		png_write_end(png_ptr, NULL);
		fclose(fp);
		R img_;
}

//< struct init; png_bytep ROWS[H] ++; H png_byte rows[y] = (png_byte*) malloc(png_get_rowbytes(png_ptr,info_ptr));	
img read_png_file(S file_name)				//<	read png file file_name and return struct 
{
		I y;
		char header[8];	// 8 is the maximum size that can be checked
		// C new[PATH_MAX + 1];
		img img_ = malloc(SZ(pImg));												//<	allocate structure
		png_bytep* rows;


		/* open file and test for it being a png */
		FILE *fp = fopen_(file_name, "rb");
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


img dep_at_xy(I am, S a_filename, S* b_filename, UH* x_, UH* y_)			//< draw pic b into pic a at x;y
{
	I i, j, k, par = 0, l = 0;
	png_byte *a_row, *b_row;
	img img_a, img_b;

	img_a = read_png_file(a_filename);

	for (k = 0; k < am; k++) {
		img_b = read_png_file(b_filename[k]);
		par = 0;

		for (i = y_[k]; i < (y_[k] + img_b->h); i++) { 

			a_row = img_a->row_pointers[i];
			b_row = img_b->row_pointers[i - y_[k]];
			l++;
			j = x_[k];
			for (; (j < x_[k] + img_b->w) && (j < img_a->w); j++) {
				if (b_row[(j - x_[k] + 1) * 4 - 1]) {
					par++;
					copy_byte(&a_row[j*4], &b_row[(j - x_[k]) * 4], 4);
				}
			}
		}
		free_img(img_b);
	}

	R img_a;
}


void add_to_canvas(I am, S* filename, UH* x_, UH* y_)
{
	free_img(write_png_file("pic/canvas.png", dep_at_xy(am, "pic/canvas.png" , filename, x_, y_)));
}

void set_canvas()
{
	int y;
	img img_a, img_;
	S filename[2];
	UH x_[2];
	UH y_[2];

	png_bytep *rows;
	height = 300;
	width =800;

	rows = (png_bytep*) malloc(height * SZ(png_bytep));

	O("SET_CANVAS\n");

	filename[0] = "pic/obj/kennel.png";
	filename[1] = "pic/obj/board.png";

	for (y=0; y<height; y++)
		rows[y] = (png_byte*) malloc(SZ(png_byte) * width * 4);

	img_a = read_png_file("pic/obj/kennel.png");

	img_ = malloc(SZ(pImg));
	img_->h = height;
	img_->w = width;
	img_->row_pointers = rows;
	img_->col = img_a->col;
	img_->b_depth = img_a->b_depth;

	write_png_file("pic/canvas.png", img_);

	free_img(img_a);
	// free_img(img_);

	x_[0] = 40;
	y_[0] = 100;
	x_[1] = 400;
	y_[1] = 20; 

	img_ = dep_at_xy(2, "pic/canvas.png", filename, x_, y_);
	free_img(write_png_file("pic/canvas.png", img_));
}

void frame(I am, S* filename, UH* x_, UH* y_)
{
	img a =  dep_at_xy(am, "pic/canvas.png", filename, x_, y_);
	img b = write_png_file ("pic/tmp.png", a);
	free_img(b);
}

/*
I main()
{
	S filename[3];
	I i, j, x[3], y[3];
	C c = 'c';
	height = 200;
	width = 600;
	for (i = 0; i < 3; i++)
		filename[i] = malloc(SZ(C) * 50);
	strcpy(filename[0], "../../pic/dog/0/love_1.png");
	strcpy(filename[1], "../../pic/dog/0/die_1.png");
	strcpy(filename[2], "../../pic/dog/0/walk_r_1.png");
	x[0] = 150;
	x[1] = 150;
	x[2] = 300;
	y[0] = 80;
	y[1] = 10;
	y[2] = 20;

	set_canvas();
	// frame(1, filename, x, y);

	// for (i = 0; i < 3; i++)
		// free(filename[i]);

	R0;
}
*/
/*

I main()
{
	S filename[3];
	I i, j, x_[3], y_[3];
	C c = 'c';
	height = 200;
	width = 600;
	for (i = 0; i < 3; i++)
		filename[i] = malloc(SZ(C) * 50);
	strcpy(filename[0], "pic/dog/0/run_r_1.png");
	strcpy(filename[1], "pic/dog/0/die_1.png");
	strcpy(filename[2], "pic/dog/0/walk_r_1.png");
	x_[0] = 150;
	x_[1] = 150;
	x_[2] = 300;
	y_[0] = 80;
	y_[1] = 10;
	y_[2] = 20;

	set_canvas();
	frame(1, filename, x_, y_);
	for (i = 0; i < 3; i++)
		free(filename[i]);

	// free(filename);
	return 0;
}
*/

/*
I main()
{
	I i, j;

	S *strings;
	I *x = malloc(SZ(I) * 3);
	I *y = malloc(SZ(I) * 3);

	strings = malloc(SZ(S) * 3);
	for (i = 0; i < 3; i++)
		strings[i] = malloc(SZ(C) * 5);

	strcpy(strings[0],"abc\0");
	strcpy(strings[1], "def\0");
	strcpy(strings[2], "xyz\0");	
	O("BROKEN HEART\n");
	x[0] = 1;
	x[1] = 2;
	x[2] = 3;
	y[0] = 11;
	y[1] = 22;
	y[2] = 33;


	C str[30] = "some/abc.png";
	C buf[1000];
	// S filename[2];
	S filename = realpath("../../pic/tmp.png", NULL);
	// filename[1] = realpath("../../png/tmp.png", buf);
	// printf("path is '%s'\n", realpath("src/png/canvas.c", buf));

	O("path1: '%s'\npath2: ''\n", filename);

	// O("%s\n", colour(str));
			
   R0;
}*/
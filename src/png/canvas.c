//<!! solve height/width problem !!
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdarg.h>
#include "../___.h"
#include "../cfg.h"

#define PNG_DEBUG 3
#include <png.h>

#define FRM 20

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

int x, y;

int a_width, a_height, width, height;
png_byte a_color_type, color_type;
png_byte a_bit_depth, bit_depth;

int number_of_passes;

png_structp png_ptr;

png_infop info_ptr;



// png_byte* a_row, *a_ptr;
// png_byte* b_row, *b_ptr;
// png_byte* row, *ptr;




void info_out(img img_)
{
	O("IMG:\th --> %d;\t w --> %d;\n\tdep --> %d;\t col --> %d;\n\n", img_->h, img_->w, img_->b_depth, img_->col);
}


void copy_byte(png_byte *a, png_byte *b, I j)
{
	for (I i = 0; i < j; i++)
		a[i] = b[i];
}


void free_img(img img_)
{
	for (I i = 0; i < img_->h; i++)
		free(img_->row_pointers[i]);
	free(img_->row_pointers);
	free(img_);
}

void write_png_file(S file_name, img img_)
{
		/* create file */
		FILE *fp = fopen(file_name, "wb");
		I w = img_->w, h = img_->h;

		png_bytep* row_p = img_->row_pointers;
		png_byte b_d = img_->b_depth;
		png_byte col = img_->col;


		if (!fp)
				abort_("[write_png_file] File %s could not be opened for writing", file_name);

		// info_out(img_);
		/* initialize stuff */
		png_ptr = png_create_write_struct(PNG_LIBPNG_VER_STRING, NULL, NULL, NULL);

		// info_out(img_);
		if (!png_ptr)
				abort_("[write_png_file] png_create_write_struct failed");

			
		info_ptr = png_create_info_struct(png_ptr);
		if (!info_ptr)
				abort_("[write_png_file] png_create_info_struct failed");

		if (setjmp(png_jmpbuf(png_ptr)))
				abort_("[write_png_file] Error during init_io");

		png_init_io(png_ptr, fp);

		// info_out(img);

		/* write header */
		if (setjmp(png_jmpbuf(png_ptr)))
				abort_("[write_png_file] Error during writing header");

		// O("WRITE %s --> w: %d  h: %d\tbd: %d  col_t: %d\n", file_name, img->w, img->h, img->b_depth, img->col);
			// info_out(img_);
		png_set_IHDR(png_ptr, info_ptr, img_->w, img_->h,
					 8, 6, PNG_INTERLACE_NONE,
					 PNG_COMPRESSION_TYPE_BASE, PNG_FILTER_TYPE_BASE);
 
		png_write_info(png_ptr, info_ptr);
 
		/* write bytes */
		if (setjmp(png_jmpbuf(png_ptr)))
				abort_("[write_png_file] Error during writing bytes");

		O("PNG_WRITE_IMAGE\n");
		png_write_image(png_ptr, img_->row_pointers);

		O("HALF DONE\n");
		fflush(stdout);
		/* end write */
		if (setjmp(png_jmpbuf(png_ptr)))
				abort_("[write_png_file] Error during end of write");

		png_write_end(png_ptr, NULL);
		O("PNG '%s' WRITE END\n", file_name);
		fclose(fp);
}


img read_png_file(char* file_name)
{
		I i;
		char header[8];	// 8 is the maximum size that can be checked

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
		
		O("READ:  '%s' ", file_name);
		for (i = 0; i < (48 - strlen(file_name) - 10)/8 + 1; i++)
			O("\t");
		fflush(stdout);
		O("-->\t\tw: %d\th: %d\tbd: %d  col_t: %d\n", img_->w, img_->h, img_->b_depth, img_->col);

		R img_;
}


img dep_at_xy(I am, char* a_filename, S* b_filename, I* x_, I* y_)				//< draw pic b into pic a at x;y
{
	I i, j, k;
	png_byte *a_row, *b_row;
	img img_a, img_b;

	O("[dep_at_xy\n");

	img_a = read_png_file(a_filename);

	for (k = 0; k < am; k++) {
		img_b = read_png_file(b_filename[k]);

		for (i = y_[k]; i < (y_[k] + img_b->h); i++) { 
			a_row = img_a->row_pointers[i];
			b_row = img_b->row_pointers[i - y_[k]];

			for (j = x_[k]; j < (x_[k] + img_b->w) && j < img_a->w; j++)
				copy_byte(&a_row[j*4], &b_row[(j - x_[k]) * 4], 4);
		}

		free_img(img_b);
	}

	R img_a;
}


void set_canvas()								//<	set blank canvas into pic/tmp.png
{
	pImg _img;
	img img_a, img_b, img_;
	png_byte *a_row, *b_row, *row;
	png_bytep *rows;

	img_ = malloc(SZ(pImg));
	img_->h = height;
	img_->w = width;

	rows = (png_bytep*) malloc(SZ(png_bytep) * height);
	for (y=0; y<height; y++)
		rows[y] = (png_byte*) malloc(4 * width * SZ(png_byte));

	img_->row_pointers = rows;


	img_a = read_png_file("../../pic/obj/kennel.png");
	img_b = read_png_file("../../pic/obj/board.png");

	img_->col = img_a->col;
	img_->b_depth = img_a->b_depth;

	for (y = 0; y < height; y++) {
		row = img_->row_pointers[y];

		a_row = img_a->row_pointers[y - (height - img_a->h - FRM)];
		b_row = img_b->row_pointers[y - (height - img_b->h - FRM)];

		for (x = 0; x < width; x++) {
			if (y < (height - FRM) && (y >= (height - img_a->h - FRM)) && (x > FRM) && (x <= (FRM + img_a->w))) 	{							//< kennel area
				copy_byte(&(row[x*4]), &(a_row[(x-FRM)*4]), 4);
			}
			else {
				if ( (y < (height - FRM)) && (y >= (height - img_b->h - FRM)) && (x >= (width - FRM - img_b->w)) && (x < (width - FRM))) {	//< board area

					copy_byte(&(row[x*4]), &(b_row[(x-width+FRM+img_b->w)*4]), 4);
				}
				else {
					row[x*4] = 0;
					row[x*4 + 1] = 0;
					row[x*4 + 2] = 0;
					row[x*4 + 3] = 0;
				}
			}
		}
	}
	O("OUT OF ITER\n");

	write_png_file("../../pic/canvas.png", img_);
	O("CANVAS WRITTEN\n");

	free_img(img_a);
	free_img(img_b);
	free_img(img_);
	O("ALL REALLOCATED\n");
}



void frame(I am, S* filename, I* x_, I* y_)
{
	write_png_file("../../pic/tmp.png", dep_at_xy(am, "../../pic/canvas.png", filename, x_, y_));		//< take base from canvas.png, modify it and put into tmp.png
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
	x[0] = 0;
	x[1] = 150;
	x[2] = 300;
	y[0] = 0;
	y[1] = 10;
	y[2] = 20;

	set_canvas();
	frame(3, filename, x, y);

	for (i = 0; i < 3; i++)
		free(filename[i]);

	R0;
}

*/

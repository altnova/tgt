//< init structs and row/col pointers
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdarg.h>
#include <limits.h>


#define PNG_DEBUG 3
#include <png.h>

#define FRM 20


#define COL_TYPE 6
#define BIT_DEPTH 8//< init structs and row/col pointers


#include "../cfg/cfg.h"
#include "../bsc/mains.h"


// I height;
// I width;


typedef struct Img {
	I h;
	I w;
	png_byte col;
	png_byte b_depth;
	png_bytep *row_pointers;
}	pImg;

typedef pImg* img;

static pImg glob;
static img GLOB_IMG = &glob;		//< used only for making struct; than must be copied

static pImg pass;
static img GLOB_PASS = &pass;



static png_bytep* glorow_s;
static png_bytep* pass_rows;

static png_byte* row_;
static png_byte* row;



// int width, height;

static int number_of_passes;
static png_structp png_ptr;
static png_infop info_ptr;



V abort_(const char * s, ...);

V info_out(img img_);							//< write struct info into stdout

V copy_byte(png_byte *a, png_byte *b, I j);		//< copy j png_bytes from a to b

V free_img(img img_);							//<	free struct

V copy_img(img a, img b);							//< a into b



/*	pass one struct at a time */
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

		//< png_destroy_read_struct(png_structpp png_ptr_ptr, png_infopp info_ptr_ptr, png_infopp end_info_ptr_ptr);

		//< void png_destroy_info_struct(png_structp png_ptr, png_infopp info_ptr_ptr);

		png_destroy_write_struct(&png_ptr, &info_ptr);
		// png_destroy_info_struct(png_ptr, &info_ptr);

		fclose(fp);
		R img_;
}

/* return one struct than you can copy 	*/
//< struct init; png_bytep ROWS[H] ++; H png_byte rows[y] = (png_byte*) malloc(png_get_rowbytes(png_ptr,info_ptr));	

img read_png_file(S file_name, img img_)				//<	read png file file_name and return struct 
{
		I y;
		char header[8];	// 8 is the maximum size that can be checked

		png_bytep* rows;

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

		// free(png_ptr);
		// free(info_ptr);

		png_destroy_read_struct(&png_ptr, &info_ptr, NULL);

		fclose(fp);
	
		R img_;
}

/* 	read one static, than one a time 	*/
//< RETURNS GLOB_IMG
img dep_at_xy(I am, S a_filename, S* b_filename, UH* x_, UH* y_)			//< draw pic b into pic a at x;y
{
	I i, j, k, par, par_, l = 0;
	// png_byte *row, *row_;

	GLOB_IMG = read_png_file(a_filename, GLOB_IMG);

	for (k = 0; k < am; k++) {						//< for each img
		GLOB_PASS = read_png_file(b_filename[k], GLOB_PASS);
		par = y_[k];

		for (i = par; i < (par + GLOB_PASS->h) && i < GLOB_IMG->h; i++) { 
			row = GLOB_IMG->row_pointers[i];

			row_ = GLOB_PASS->row_pointers[i - par];
			l++;
			par_ = x_[k];
			for (j = par_; (j < par_ + GLOB_PASS->w) && (j < GLOB_IMG->w); j++) {
				if (row_[(j - par_ + 1) * 4 - 1]) 
					copy_byte(&row[j*4], &row_[(j - par_) * 4], 4);
			}
		}
		free_img(GLOB_PASS);
	}

	R GLOB_IMG;
}

V add_to_canvas(I am, S* filename, UH* x_, UH* y_)
{
	free_img(write_png_file("pic/canvas.png", dep_at_xy(am, "pic/canvas.png" , filename, x_, y_)));
}

V set_canvas()
{
	int y;

	S* filename = malloc(SZ(S) * 2);
	UH *x_ = malloc(SZ(UH) * 2);
	UH *y_ = malloc(SZ(UH) * 2);

	png_bytep *rows;

	rows = (png_bytep*) malloc(height * SZ(png_bytep));

	for (y=0; y<height; y++)
		rows[y] = (png_byte*) malloc(SZ(png_byte) * width * 4);

	filename[0] = malloc(SZ(C) * 50);
	filename[1] = malloc(SZ(C) * 50);

	filename[0] = "pic/obj/kennel.png";
	filename[1] = "pic/obj/board.png";

	GLOB_IMG->h = height;
	GLOB_IMG->w = width;
	GLOB_IMG->row_pointers = rows;
	GLOB_IMG->col = COL_TYPE;
	GLOB_IMG->b_depth = BIT_DEPTH;

	write_png_file("pic/canvas.png", GLOB_IMG);

	x_[0] = 40;
	y_[0] = 100;
	x_[1] = 400;
	y_[1] = 20; 

	GLOB_IMG = dep_at_xy(2, "pic/canvas.png", filename, x_, y_);
	
	write_png_file("pic/canvas.png", GLOB_IMG);

	free_img(GLOB_IMG);

	free(filename);

	free(x_);
	free(y_);
}

V frame(I am, S* filename, UH* x_, UH* y_)						//< make compelete tmp.png for display 
{
	free_img(write_png_file ("pic/tmp.png", dep_at_xy(am, "pic/canvas.png", filename, x_, y_)));						//< save it 
}




/*

I main()
{
	S filename[3];
	I i, j, *x = malloc(SZ(I) * 3), *y = malloc(SZ(I) * 3);
	C c = 'c';
	height = 200;
	width = 600;
	for (i = 0; i < 3; i++)
		filename[i] = malloc(SZ(C) * 50);
	strcpy(filename[0], "pic/dog/0/love_1.png");
	strcpy(filename[1], "pic/dog/0/die_1.png");
	strcpy(filename[2], "pic/dog/0/walk_r_1.png");
	x[0] = 150;
	x[1] = 150;
	x[2] = 300;
	y[0] = 80;
	y[1] = 10;
	y[2] = 20;

	set_canvas();
	frame(3, filename, x, y);

	// for (i = 0; i < 3; i++)
		// free(filename[i]);

	R0;
}
*/



V abort_(const char * s, ...)
{
		va_list args;
		va_start(args, s);
		vfprintf(stderr, s, args);
		fprintf(stderr, "\n");
		va_end(args);
		abort();
}

V info_out(img img_)							//< write struct info into stdout
{

	O("IMG:\th --> %d;\t w --> %d;\n\tdep --> %d;\t col --> %d;\n\n", img_->h, img_->w, img_->b_depth, img_->col);
}

V copy_byte(png_byte *a, png_byte *b, I j)	//< copy j png_bytes from a to b
{
	for (I i = 0; i < j; i++) {
		// O("a[i] --> %d; b[i] --> %d\n", a[i], b[i]);
		a[i] = b[i];
	}
}

V free_img(img img_)							//<	free struct
{
	for (I i = 0; i < img_->h; i++)
		free(img_->row_pointers[i]);
	free(img_->row_pointers);
	// free(img_);
}


V copy_img(img a, img b)						//< a into b
{
	b->h = a->h;
	b->w = a->w;
	b->col = a->col;
	b->b_depth = a->b_depth;
	b->row_pointers = a->row_pointers;

}


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



// static png_bytep* glorow_s;
// static png_bytep* pass_rows;

static png_byte* row_;
static png_byte* row;



// int width, height;

static int number_of_passes;
static png_structp png_ptr;
static png_infop info_ptr;


static pImg canvas;
static img CANVAS = &canvas;		//<!!!	!
static pImg canvas_cp;
static img TMP = &canvas_cp;

static UH x_c[2];
static UH y_c[2];


//< for a while
//////////////////////////////////////////
static C FNM[2][50];
static S addr_fnm_[4] = {FNM[0], FNM[1]};
static S* addr_fnm = addr_fnm_;
//////////////////////////////////////////

V abort_(const char * s, ...);

V info_out(img img_);							//< write struct info into stdout

V copy_byte(png_byte *a, png_byte *b, I j);		//< copy j png_bytes from a to b

V free_img(img img_);							//<	free struct

img copy_img(img a, img b);							//< a into b

img write_png_file(S file_name, img img_);
img read_png_file(S file_name, img img_);


/* 	read one static, than one a time 	*/
//< RETURNS GLOB_IMG
img dep_at_xy(I am, img a, S* b_filename, UH* x_, UH* y_)			//< draw pic b into pic a at x;y
{
	I i, j, k, par, par_, l = 0;

	// GLOB_IMG = read_png_file(a_filename, GLOB_IMG);

	copy_img(a, TMP);												//<	copy CANVAS into TMP

	for (k = 0; k < am; k++) {										//< for each img
		GLOB_PASS = read_png_file(b_filename[k], GLOB_PASS);
		par = y_[k];

		for (i = par; i < (par + GLOB_PASS->h) && i < TMP->h; i++) { 
			row = TMP->row_pointers[i];

			row_ = GLOB_PASS->row_pointers[i - par];
			l++;
			par_ = x_[k];
			for (j = par_; (j < par_ + GLOB_PASS->w) && (j < TMP->w); j++) {
				if (row_[(j - par_ + 1) * 4 - 1]) 
					copy_byte(&row[j*4], &row_[(j - par_) * 4], 4);
			}
		}
		free_img(GLOB_PASS);
	}

	R TMP;
}

V add_to_canvas(I am, S* filename, UH* x_, UH* y_)
{
	img a = dep_at_xy(am, CANVAS, filename, x_, y_);
	copy_img(a, CANVAS);
	free_img(a);

	// free_img(copy_img(dep_at_xy(am, CANVAS, filename, x_, y_), CANVAS));
	// free_img(write_png_file("pic/canvas.png", dep_at_xy(am, CANVAS, filename, x_, y_)));
}

V frame(I am, S* filename, UH* x_, UH* y_)						//< make compelete tmp.png for display 
{
	// img a = dep_at_xy(am, CANVAS, filename, x_, y_);
	// free_img(write_png_file("pic/tmp.png", a));

	free_img(write_png_file ("pic/tmp.png", dep_at_xy(am, CANVAS, filename, x_, y_)));						//< save it 
}

V set_canvas()
{
	int y;
	img tmp;
	// S* filename = malloc(SZ(S) * 2);
	// UH *x_ = malloc(SZ(UH) * 2);
	// UH *y_ = malloc(SZ(UH) * 2);

	png_bytep *rows;

	rows = (png_bytep*) malloc(height * SZ(png_bytep));

	for (y=0; y<height; y++)
		rows[y] = (png_byte*) malloc(SZ(png_byte) * width * 4);

	// filename[0] = malloc(SZ(C) * 50);
	// filename[1] = malloc(SZ(C) * 50);

	// filename[0] = "pic/obj/kennel.png";
	// filename[1] = "pic/obj/board.png";

	arrcat(FNM[0], "pic/obj/kennel.png", 0);
	arrcat(FNM[1], "pic/obj/board.png", 0);

	CANVAS->h = height;
	CANVAS->w = width;
	CANVAS->row_pointers = rows;
	CANVAS->col = COL_TYPE;
	CANVAS->b_depth = BIT_DEPTH;

	// write_png_file("pic/canvas.png", GLOB_IMG);

	x_c[0] = 40;
	y_c[0] = 100;
	x_c[1] = 400;
	y_c[1] = 20; 


	tmp = dep_at_xy(2, CANVAS, addr_fnm, x_c, y_c);

	copy_img(tmp, CANVAS);

	free_img(tmp);

	// copy_img(dep_at_xy(2, CANVAS, filename, x_, y_), CANVAS);
	
	write_png_file("pic/canvas.png", CANVAS);

	// free_img(GLOB_IMG);

	// free(filename);

	// free(x_);
	// free(y_);
}

V end_canvas()
{
	free_img(CANVAS);
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
		// if (!i%100 && i) {
		// O("%d ", i);
		// fflush(stdout);		

		// }


		// O("%d ", i);
		// fflush(stdout);
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

img copy_img(img a, img b)						//< a into b
{
	I i, j;
	png_bytep *rows;
	b->h = a->h;
	b->w = a->w;
	b->col = a->col;
	b->b_depth = a->b_depth;

	rows = (png_bytep*) malloc(b->h * SZ(png_bytep));

	for (i = 0; i < b->h; i++){
		rows[i] = (png_byte*) malloc(SZ(png_byte) * b->w * 4);

		// O("broken at %d\n", i);
		// row = rows[i];
		// row_= a->row_pointers[i];

		copy_byte(rows[i], a->row_pointers[i], b->w * 4);
		// for (j = 0; j < b->w; j++)
			// copy_byte(&rows[i][j*4], &b->row_pointers[i][j*4], 4);
	}

	b->row_pointers = rows;

	R b;
}



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

		png_destroy_read_struct(&png_ptr, &info_ptr, NULL);

		fclose(fp);
	
		R img_;
}



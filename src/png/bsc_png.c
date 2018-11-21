//< basic png operations 
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
#define BIT_DEPTH 8

#include "bsc_png.h"
#include "../bsc/mains.h"

static int number_of_passes;
static png_structp png_ptr;
static png_infop info_ptr;


///////////////////////////////////////////////////////////////
//<				abort_(const char * s, ...)					>//
///////////////////////////////////////////////////////////////
//<		abort for canvas.c which prints list of args s 		>//
///////////////////////////////////////////////////////////////
V abort_(const char * s, ...)
{
		va_list args;
		va_start(args, s);
		vfprintf(stderr, s, args);
		fprintf(stderr, "\n");
		va_end(args);
		abort();
}

///////////////////////////////////////////////////////////////
//<					info_out(img img_)						>//
///////////////////////////////////////////////////////////////
//<			print img_ struct information					>//
///////////////////////////////////////////////////////////////
V info_out(img img_)											
{
	O("IMG:\th --> %d; w --> %d;\n", img_->h, img_->w);
	O("\tdep --> %d;\t col --> %d;\n\n", , img_->b_depth, img_->col);
}

///////////////////////////////////////////////////////////////
//<			copy_byte(png_byte *a, png_byte *b, I j)		>//
///////////////////////////////////////////////////////////////
//<		copy j elements from b png_byte array into a array	>//
///////////////////////////////////////////////////////////////
V copy_byte(png_byte *a, png_byte *b, I j)					
{
	for (I i = 0; i < j; i++) 
		a[i] = b[i];
}

///////////////////////////////////////////////////////////////
//<					free_img(img img_)						>//
///////////////////////////////////////////////////////////////
//<				free img_->row_pointers						>//
///////////////////////////////////////////////////////////////
V free_img(img img_)										
{
	for (I i = 0; i < img_->h; i++)
		free(img_->row_pointers[i]);
	free(img_->row_pointers);
}

///////////////////////////////////////////////////////////////
//<				copy_img(img a, img b)						>//
///////////////////////////////////////////////////////////////
//<		copy all data from img b into img a including 		>//
//<	including new allocation of row_pointers and copying	>//
//< 	whole b's idat chunk into a->row_pointers 			>//
///////////////////////////////////////////////////////////////
//<				return updated img a 						>//
///////////////////////////////////////////////////////////////
img copy_img(img a, img b)								
{
	I i, j;
	png_bytep *rows;
	a->h = b->h;
	a->w = b->w;
	a->col = b->col;
	a->b_depth = b->b_depth;

	rows = (png_bytep*) malloc(a->h * SZ(png_bytep));

	for (i = 0; i < a->h; i++){
		rows[i] = (png_byte*) malloc(SZ(png_byte) * a->w * 4);
		copy_byte(rows[i], b->row_pointers[i], a->w * 4);
	}

	a->row_pointers = rows;
	R a;
}

///////////////////////////////////////////////////////////////
//<			write_png_file(S file_name, img img_)			>//
///////////////////////////////////////////////////////////////
//<		write file_name png image with dat from img_ 		>//
//<	!!!	don't forget to free img_->row_pointers if you 	!!!	>//
//<	!!!			won't need img_ anymore 				!!!	>//
///////////////////////////////////////////////////////////////
//<						return img_ 						>//
///////////////////////////////////////////////////////////////
img write_png_file(S file_name, img img_)			
{
	FILE *fp = fopen_(file_name, "wb");

	if (!fp) {
		abort_("[write_png_file] File %s couldn't be opened for writing",
																 	file_name);
	}
	
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
	png_destroy_write_struct(&png_ptr, &info_ptr);
	fclose(fp);
	R img_;
}

///////////////////////////////////////////////////////////////
//<			read_png_file(S file_name, img img_)			>//
///////////////////////////////////////////////////////////////
//<			get info from png file_name into img_ 			>//
//<	!!!	don't forget to free img_->row_pointers if you 	!!!	>//
//<	!!!			won't need img_ anymore 				!!!	>//
//<	!!!	it allocates memory for img_->row_pointers 		!!!	>//
///////////////////////////////////////////////////////////////
//<						return img_ 						>//
///////////////////////////////////////////////////////////////
img read_png_file(S file_name, img img_)							//<	read png file file_name and return struct 
{
	I i;
	C header[8];	// 8 is the maximum size that can be checked
	png_bytep* rows;

	FILE *fp = fopen_(file_name, "rb");
	if (!fp)
			abort_("[read_png_file] File %s could not be opened for reading", 
																	file_name);

	fread(header, 1, 8, fp);

	if (png_sig_cmp((png_const_bytep)header, 0, 8))
			abort_("[read_png_file] File %s is not recognized as a PNG file", 
																	file_name);
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
	for (i = 0; i < img_->h; i++)
			rows[i] = (png_byte*) malloc(png_get_rowbytes(png_ptr,info_ptr));	//<	allocate each row
	
	png_read_image(png_ptr, rows);
	img_->row_pointers = rows;					

	png_destroy_read_struct(&png_ptr, &info_ptr, NULL);
	fclose(fp);
	R img_;
}


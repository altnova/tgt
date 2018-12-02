#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdarg.h>
#include <limits.h>

#define PNG_DEBUG 3
#include <png.h>



png_byte col;
png_byte b_depth;
// png_bytep *row_pointers;
// }	pImg;

int number_of_passes;
png_structp png_ptr;
png_infop info_ptr;


//<					img is pImg pointer 					>//
// typedef pImg* img;


void abort_(const char * s, ...)
{
		va_list args;
		va_start(args, s);
		vfprintf(stderr, s, args);
		fprintf(stderr, "\n");
		va_end(args);
		abort();
}

void read_png_file(char* file_name, png_bytep *row_pointers, int* w, int* h)
{
	int i;
	char header[8];	// 8 is the maximum size that can be checked
	png_bytep* rows;

	FILE *fp = fopen(file_name, "rb");
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
	
	*w = png_get_image_width(png_ptr, info_ptr);
	*h = png_get_image_height(png_ptr, info_ptr);
	col = png_get_color_type(png_ptr, info_ptr);
	b_depth = png_get_bit_depth(png_ptr, info_ptr);
	number_of_passes = png_set_interlace_handling(png_ptr);
	
	png_read_update_info(png_ptr, info_ptr);
	
	/* read file */
	if (setjmp(png_jmpbuf(png_ptr)))
			abort_("[read_png_file] Error during read_image");
	
	rows = (png_bytep*) malloc(sizeof(png_bytep) * (*h));					//< allocate row pointers
	for (i = 0; i < (*h); i++)
			rows[i] = (png_byte*) malloc(png_get_rowbytes(png_ptr,info_ptr));	//<	allocate each row
	
	png_read_image(png_ptr, rows);
	row_pointers = rows;					

	png_destroy_read_struct(&png_ptr, &info_ptr, NULL);
	fclose(fp);
	// R img_;
}


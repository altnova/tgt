
#include "../cfg/cfg.h"

typedef struct Img {
	I h;
	I w;
	png_byte col;
	png_byte b_depth;
	png_bytep *row_pointers;
}	pImg;

typedef pImg* img;


ext V abort_(const char * s, ...);

ext V info_out(img img_);												//< write struct info into stdout

ext V copy_byte(png_byte *a, png_byte *b, I j);							//< copy j png_bytes from a to b

ext V free_img(img img_);												//<	free struct

ext img copy_img(img b, img a);											//< a into b

ext img write_png_file(S file_name, img img_);

ext img read_png_file(S file_name, img img_);


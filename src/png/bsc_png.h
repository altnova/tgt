//< basic png operations 
#include "../cfg/cfg.h"


//<     *   *  *             * * *             *  *   *     >//
//<			pImg is a struct that contains info about .png 	>//
typedef struct Img {
	I h;
	I w;
	png_byte col;
	png_byte b_depth;
	png_bytep *row_pointers;
}	pImg;

//<					img is pImg pointer 					>//
typedef pImg* img;
//<     *   *  *             * * *             *  *   *     >//


//<     *   *  *             * * *             *  *   *     >//
//<             abort_(const char * s, ...)                 >//
//<     *   *  *             * * *             *  *   *     >//
//<      abort for canvas.c which prints list of args s     >//
//<     *   *  *             * * *             *  *   *     >//
ext V abort_(const char * s, ...);

//<     *   *  *             * * *             *  *   *     >//
//<                  info_out(img img_)                     >//
//<     *   *  *             * * *             *  *   *     >//
//<             print img_ struct information               >//
//<     *   *  *             * * *             *  *   *     >//
ext V info_out(img img_);												

//<     *   *  *             * * *             *  *   *     >//
//<         copy_byte(png_byte *a, png_byte *b, I j)        >//
//<     *   *  *             * * *             *  *   *     >//
//<     copy j elements from b png_byte array into a array  >//
//<     *   *  *             * * *             *  *   *     >//
ext V copy_byte(png_byte *a, png_byte *b, I j);							

//<     *   *  *             * * *             *  *   *     >//
//<                 free_img(img img_)                      >//
//<     *   *  *             * * *             *  *   *     >//
//<               free img_->row_pointers                   >//
//<     *   *  *             * * *             *  *   *     >//
ext V free_img(img img_);												

//<     *   *  *             * * *             *  *   *     >//
//<               copy_img(img a, img b)                    >//
//<     *   *  *             * * *             *  *   *     >//
//<     copy all data from img b into img a including       >//
//< including new allocation of row_pointers and copying    >//
//<     whole b's idat chunk into a->row_pointers           >//
//<     *   *  *             * * *             *  *   *     >//
//<                 return updated img a                    >//
//<     *   *  *             * * *             *  *   *     >//
ext img copy_img(img b, img a);											

//<     *   *  *             * * *             *  *   *     >//
//<         write_png_file(S file_name, img img_)           >//
//<     *   *  *             * * *             *  *   *     >//
//<     write file_name png image with dat from img_        >//
//< !!! don't forget to free img_->row_pointers if you  !!! >//
//< !!!         won't need img_ anymore                 !!! >//
//<     *   *  *             * * *             *  *   *     >//
//<                     return img_                         >//
//<     *   *  *             * * *             *  *   *     >//
ext img write_png_file(S file_name, img img_);

//<     *   *  *             * * *             *  *   *     >//
//<         read_png_file(S file_name, img img_)            >//
//<     *   *  *             * * *             *  *   *     >//
//<         get info from png file_name into img_           >//
//< !!! don't forget to free img_->row_pointers if you  !!! >//
//< !!!         won't need img_ anymore                 !!! >//
//< !!! it allocates memory for img_->row_pointers      !!! >//
//<     *   *  *             * * *             *  *   *     >//
//<                      return img_                        >//
//<     *   *  *             * * *             *  *   *     >//
ext img read_png_file(S file_name, img img_);


//<	compile .png for visualization
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

static pImg canvas;
static pImg canvas_cp;
static img CANVAS = &canvas;	
static img TMP = &canvas_cp;

static UH x_c[2];
static UH y_c[2];


//< for a while
///////////////////////////////////////////////////////////////
static C FNM[2][LINE_MAX_];
static S addr_fnm_[4] = {FNM[0], FNM[1]};
static S* addr_fnm = addr_fnm_;
///////////////////////////////////////////////////////////////

    
///////////////////////////////////////////////////////////////
//<  dep_at_xy(I am, img a, img b, S* file, UH* x_, UH* y_) >//
///////////////////////////////////////////////////////////////
//<     get idat chunk from img a, mount in file[i] at      >//
//<         x_[i] y_[i] and save it into img b              >//
//<                am is number of files                    >//
///////////////////////////////////////////////////////////////
//<                    return img b                         >//
///////////////////////////////////////////////////////////////
img dep_at_xy(I am, img a, img b, S* file, UH* x_, UH* y_)
{
	I i, j, k;
	png_byte *row_, *row;
	pImg tmp_;
	img tmp = &tmp_;

	copy_img(b, a);													//<	copy CANVAS into TMP

	for (k = 0; k < am; k++) {										//< for each img
		tmp = read_png_file(file[k], tmp);

		for (i = y_[k]; i < (y_[k] + tmp->h) && i < b->h; i++) { 
			row = b->row_pointers[i];
			row_ = tmp->row_pointers[i - y_[k]];

			for (j = x_[k]; (j < x_[k] + tmp->w) && (j < b->w); j++) 
				if (row_[(j - x_[k] + 1) * 4 - 1]) 					//<	copy only visible pix
					copy_byte(&row[j*4], &row_[(j - x_[k]) * 4], 4);
		}
		free_img(tmp);
	}
	R b;
}

///////////////////////////////////////////////////////////////
//<     add_to_canvas(I am, S* filename, UH* x_, UH* y_)    >//
///////////////////////////////////////////////////////////////
//<     update CANVAS and canvas.png                        >//
//<     mount into canvas.png and CANVAS filename[i] at     >//
//<                 x_[i] and y_[i]                         >//
//<             am is number of filenames                   >//
///////////////////////////////////////////////////////////////
V add_to_canvas(I am, S* filename, UH* x_, UH* y_)
{
	img a = dep_at_xy(am, CANVAS, TMP, filename, x_, y_);
	copy_img(CANVAS, a);
	free_img(a);
}

///////////////////////////////////////////////////////////////
//<         frame(I am, S* filename, UH* x_, UH* y_)        >//
///////////////////////////////////////////////////////////////
//<   create pic/tmp.png which is canvas.png with mounted   >//
//<            filename[i] pic at x_[i] y_[i]               >//
//<               am is amount of filename                  >//
///////////////////////////////////////////////////////////////
V frame(I am, S* filename, UH* x_, UH* y_)							
{
	free_img(write_png_file ("pic/tmp.png", dep_at_xy(am, CANVAS, TMP, filename, x_, y_)));						//< save it 
}

///////////////////////////////////////////////////////////////
//<                      set_canvas()                       >//
///////////////////////////////////////////////////////////////
//<     set canvas as CANVAS with basic elements            >//
//<     pic/canvas.png created for insurance                >//
///////////////////////////////////////////////////////////////	
V set_canvas()
{
	int i, j;
	img tmp;
	png_bytep *rows;

	rows = (png_bytep*) malloc(height * SZ(png_bytep));

	for (i = 0; i < height; i++) 
		rows[i] = (png_byte*) calloc(width * 4, SZ(png_byte));

	arrcat(FNM[0], "pic/obj/kennel.png", 0);
	arrcat(FNM[1], "pic/obj/board.png", 0);

	CANVAS->h = height;
	CANVAS->w = width;
	CANVAS->row_pointers = rows;
	CANVAS->col = COL_TYPE;
	CANVAS->b_depth = BIT_DEPTH;

	x_c[0] = crd->kennel_x;
	y_c[0] = crd->kennel_y;
	x_c[1] = crd->bar_x;
	y_c[1] = crd->bar_y; 

	tmp = dep_at_xy(2, CANVAS, tmp, addr_fnm, x_c, y_c);

	copy_img(CANVAS, tmp);
	free_img(tmp);
	write_png_file("pic/canvas.png", CANVAS);
}

///////////////////////////////////////////////////////////////
//<                      end_canvas()                       >//
///////////////////////////////////////////////////////////////
//<     free al allocated memory used to produce png img    >//
///////////////////////////////////////////////////////////////
V end_canvas()
{
	free_img(CANVAS);
	O("canvas free ok\n");
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

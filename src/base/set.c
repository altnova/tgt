//<	init structs
#include "../cfg.h"
#include "../___.h"
// #include <gtk/gtk.h>
#include <stdlib.h>
#include <limits.h>
#include <dirent.h>
#include <string.h>
#include <errno.h>



/*
typedef struct Coor 		//< coordinates of objects 
{	
	UH dir;					//< 1 -. RIGHT 	0 -. LEFT
	UH rad;
	UH kennel_x;
	UH kennel_y;
	UH bowl_x;
	UH bowl_y;
	UH dog_x;
	UH dog_y;
	UH bar_x;
	UH bar_y;
	UH sat_x;
	UH sat_y;
	UH int_x;
	UH int_y;
	UH cle_x;
	UH cle_y;
	UH dog_in_kennel_x;
	UH dog_in_kennel_y;
} pCoor;
*/

//< !!!!!!!!!!!!!!!!!
#define BAR_W 0 
#define NOM_W 0
#define D_LIM 0
#define DOG_H 0
#define NOM_H 0
#define KENNEL_H 0
#define BOWL_H 0
#define BAR_H 0

ext I height;
ext I width;

C NUM_INT[12];
C DOG_FILE[2000];
C FILENAME[2000];
S ADDR = FILENAME;
S* ADDR_ADDR = &ADDR;

I height_()
{
	I h = 300;
	R h;
}
I width_()
{
	I w = 900;
	R w;
}

/*
typedef struct Cnt_tm		//< counters
{
	I last_act;
	I satiety;
	I intellect;
	I cleanliness;
} pCounter;


typedef struct Dt 			//< dog info
{
	C satiety;
	C intellect;
	C cleanliness;
	C colour;
	C action;
} pDat;

*/

pDat DAT;
pCounter CNT;
pCoor COR;



V set_data(dat dt_main, tm_cnt cnt_main, coor crd_main)
{
	I height = height_();
	I width = width_();
	I down = width - 65;
	// pDat dt_main = {5, 5, 5, 2, 9};
	// pCounter cnt_main = {0, 0, 0, 0};
	// pCoor crd_main;

	

	// dat dt_main

	dt_main = &DAT;
	cnt_main = &CNT;
	crd_main = &COR;

	crd_main->dir = RIGHT;
	crd_main->rad = RANGE;

	cnt_main->last_act = 0;
	cnt_main->satiety = 0;
	cnt_main->intellect = 0;
	cnt_main->cleanliness = 0;

	dt_main->satiety = 5;
	dt_main->intellect = 5;
	dt_main->cleanliness = 5;
	dt_main->colour = 2;
	dt_main->action = 9;


		/*	x 	*/
	crd_main->kennel_x 	= L_LIM/2;					//< L_LIM == WIDTH/10; R_LIM = WIDTH*9/10
	crd_main->bowl_x 	= L_LIM/4;
	// crd_main->dog_x 	= 2 * L_LIM;
	crd_main->dog_x = 200;
	crd_main->bar_x 	= R_LIM;
	// crd_main->int_x 	= R_LIM + BAR_W - NOM_W;	//<	BAR_W ??? NOM_W ???
	crd_main->int_x 	= crd_main->int_x;
	crd_main->cle_x 	= crd_main->int_x;
	crd_main->sat_x 	= crd_main->int_x;

		/*	y 	*/
	crd_main->kennel_y 	= D_LIM - KENNEL_H;			//<	D_LIM ??? KENNEL_H		
	crd_main->bowl_y 	= D_LIM - BOWL_H;			//< BOWL_H ???
	// crd_main->dog_y 	= D_LIM - DOG_H;				//<	DOG_H ????
	crd_main->dog_y = 100;
	crd_main->bar_y 	= D_LIM - BAR_H;
	crd_main->int_y 	= crd_main->bar_y;
	crd_main->cle_y 	= crd_main->bar_y - NOM_H;
	crd_main->sat_y 	= crd_main->int_x;

	crd = crd_main;
	dt = dt_main;
	cnt = cnt_main;
}


V set_window()			//< fullscreen, transparent, click-trough
{

}
																	//!!!!!<	GTK+
V set_objects()		//< kennel, board, empty_bowl;
{

}

C last_c(S line, S needle, I len)
{
	I n_len = strlen(needle);
	I i = n_len - 1, j;

	for (j = len - 1, i = n_len - 1; i >= 0; j--, i--) {
			if (line[j] != needle[i]) {
				O("line[j] --> '%c'; needle[i] --> '%c'\n", line[j], needle[i]);
				R 0;
			}
	}

	R 1;
}

C first_c(S line, S needle, I len)
{
	I n_len = strlen(needle), i;

	for (i = 0; needle[i] && i < n_len && i < len; i++) {
		if (line[i] != needle[i]) {
			R 0;
		}
	}
	if (i == len)
		R 0;

	R 1;

}



C is_tgt(S path)
{
	I len = strlen(path);
	FILE *ptr;
	DIR *d;

	if (!last_c(path, "/tgt", len)) {
		O("invalid path to tgt!\n");
		R 0;
		// exit(0);
	}


	d = opendir(path);

	if (d != NULL) {
		if (errno != ENOTEMPTY)
			R 1;
		else {
			O("tgt directory is empty!\n");
			R 0;
		}

	}

	if (errno == ENOTDIR) {
		O("your tgt must be a directory!\n");
		R 0;
	}


	R 0;
}



C is_home(S path)
{
	I len = strlen(path);
	FILE *ptr;
	DIR *d;

	if (!first_c(path, "/home", len)) {
		O("no home directory!\n");
		// exit(0);
		R 0;
	}

	d = opendir(path);

	if (d != NULL) {
		if (errno != ENOTEMPTY)
			R 1;
		else {
			O("home directory is empty!\n");
			R 0;
		}
	}

	if (errno == ENOTDIR) {
		O("home must be directory!\n");
		R 0;
	}

	R 0; 
}


V check_env()
{
	S tgt_home = getenv("TGT_HOME"), home = getenv("HOME");
	if (tgt_home == NULL) {				//<	not null, exists, directory
		O("please, set env variable TGT_HOME\n");
		exit(1);
	}

	if (home == NULL) {
		O("please, set env var HOME\n");
		exit(0);
	}

	if (!is_tgt(tgt_home) || !is_home(home)) {
		O("go and fuck yourself\n");
		exit(1);
	}


}

/*tm_cnt cnt;
dat dt;
coor crd;
*/
V set_start(tm_cnt cnt_, dat dt_, coor crd_)
{
	check_env();
	set_data(dt_, cnt_, crd_);
	set_window();
	set_objects();
	
}
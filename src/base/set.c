#include "../cfg.h"
#include "../___.h"
// #include <gtk/gtk.h>
#include <stdlib.h>
#include <limits.h>


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
V set_data(dat dt_main, tm_cnt cnt_main, coor crd_main)
{
	I height = height_();
	I width = width_();
	I down = width - 65;
	// pDat dt_main = {5, 5, 5, 2, 9};
	// pCounter cnt_main = {0, 0, 0, 0};
	// pCoor crd_main;

	

	// dat dt_main

	dt_main = malloc(SZ(pDat));
	cnt_main = malloc(SZ(pCounter));
	crd_main = malloc(SZ(pCoor));

	crd_main->dir = RIGHT;
	crd_main->rad = RANGE;

	cnt_main->last_act = 0;
	cnt_main->satiety = 0;
	cnt_main->intellect = 0;
	cnt_main->cleanliness = 0;

	dt_main->satiety = 5;
	dt_main->intellect = 5;
	dt_main->cleanliness = 5;
	dt_main->colour = 5;
	dt_main->action = 9;


		/*	x 	*/
	crd_main->kennel_x 	= L_LIM/2;					//< L_LIM == WIDTH/10; R_LIM = WIDTH*9/10
	crd_main->bowl_x 	= L_LIM/4;
	// crd_main->dog_x 	= 2 * L_LIM;
	crd_main->dog_x = 200;
	crd_main->bar_x 	= R_LIM;
	crd_main->int_x 	= R_LIM + BAR_W - NOM_W;	//<	BAR_W ??? NOM_W ???
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


V check_env()
{
	if (getenv("TGT_HOME") == NULL) {				//<	not null, exists, directory
		O("hmm\n");
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
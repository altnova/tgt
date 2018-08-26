#include "cfg.h"
#include "___.h"

ext tm_cnt cnt;
ext dat dt;
ext coor crd;


/*
typedef struct Coor 		//< coordinates of objects 
{	
	UH dir;					//< 1 --> RIGHT 	0 --> LEFT
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

V set_data()
{
	I height = height_();
	I width = width_();
	I down = width - 65;
	pDat dt_main = {5, 5, 5, 2, 9};
	pCounter cnt_main = {0, 0, 0, 0};
	pCoor crd_main;

	crd_main->dir = 1;
	crd_main->rad = 30;

		/*	x 	*/
	crd_main->kennel_x 	= L_LIM/2;					//< L_LIM == WIDTH/10; R_LIM = WIDTH*9/10
	crd_main->bowl_x 	= L_LIM/4;
	crd_main->dog_x 	= 2 * L_LIM;
	crd_main->bar_x 	= R_LIM;
	crd_main->int_x 	= R_LIM + BAR_W - NOM_W;	//<	BAR_W ??? NOM_W ???
	crd_main->cle_x 	= crd_main->int_x;
	crd_main->sat_x 	= crd_main->int_x;

		/*	y 	*/
	crd_main->kennel_y 	= D_LIM - KENNEL_H;			//<	D_LIM ??? KENNEL_H		
	crd_main->bowl_y 	= D_LIM - BOWL_H;			//< BOWL_H ???
	crd_main->dog_y 	= D_LIM - DOG_H				//<	DOG_H ????
	crd_main->bar_y 	= D_LIM - BAR_H;
	crd_main->int_y 	= crd_main->bar_y;
	crd_main->cle_y 	= crd_main->bar_y - NOM_H;
	crd_main->sat_y 	= crd_main->int_x;

	crd = &crd_main;
	dt = &dt_main;
	cnt = &cnt_main;
}


V set_window();			//< fullscreen, transparent, click-trough

V set_objects();		//< kennel, board, empty_bowl;

V set_start()
{
	set_data();
	set_window();
	set_objects();
}
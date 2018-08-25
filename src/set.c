#include "cfg.h"
#include "___.h"

ext tm_cnt cnt;
ext dat dt;
ext coor crd;



/*
w = 1440
h = 900

down = 835 		[ h - 65]

l lim = 70		[w/20]	

r lim = 1370  	[w - l]

*/

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



V set_data()
{
	I height = height_();
	I width = width_();
	I down = width - 65;
	pDat dt_main = {5, 5, 5, 2, 9};
	pCounter cnt_main = {0, 0, 0, 0};
	pCoor crd_main;
/*													//< set coordinates 
	crd_main->dir = 1;
	crd_main->kennel_x = width/20 - 10;
	crd_main->kennel_y = down + 60;
	crd_main->rad = 30;
	crd_main->dog_x = width/20;
	crd_main->dog_y = down;

	crd_main->dog_in_kennel_x = crd_main->kennel_x + 20;
	crd_main->dog_in_kennel_y = down + 30;



	crd_main->bar_x = width/10;
	crd_main->bar_y = down - 60
	crd_main->sat_x = sat->bar_x + 30;
	crd_main->sat_y = sat->bar_y;
	crd_main->int_x = sat->bar_x + 30;
	crd_main->int_y = sat->bar_y - 20;
	crd_main->cle_x = sat->bar_x + 30;
	crd_main->cle_y = sat->bar_y - 40;

*/
	crd = &crd_main;
	dt = &dt_main;
	cnt = &cnt_main;
}


V set_window();

V set_objects();		//< kennel, board, empty_bowl;

V set_start()
{
	set_data();
	set_window();
	set_objects();
}
//<	set start data 
#include <stdlib.h>
#include <limits.h>
#include <dirent.h>
#include <string.h>
#include <errno.h>

#include "../cfg/cfg.h"
#include "../gui/win.h"
#include "../fld/wfile.h"
#include "mains.h"

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

//< set this part 
//< !!!!!!!!!!!!!!!!!
#define BAR_W 0 
#define NOM_W 0
#define D_LIM 0
#define DOG_H 0
#define NOM_H 0
#define KENNEL_H 0
#define BOWL_H 0
#define BAR_H 0
//<	!!!!!!!!!!!!!!!!!

tm_cnt cnt;
dat dt;
coor crd;

I stat_time[12] = 	{	1000, 	1000,	1000,   3000, 4000,   7000,	  7000, 	1000, 	  1000,  	 1000,   3000, 		0 };		//< /1000 --> get am in seconds 
S stat_name[12] = 	{	"sit", "run", "walk", "eat", "read_", "die", "rise", "sleep_1", "sleep_2", 	"love", "wc", "return"};

D_STAT d_stat;

I height;
I width;

C NUM_INT[12];
C DOG_FILE[2000];
C FILENAME[2000];
S ADDR = FILENAME;
S* ADDR_ADDR = &ADDR;

pDat DAT = {5, 5, 5, 2, 9};
pCounter CNT = {0,  0, 0, 0};
pCoor COR;

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
	height = height_();
	width = width_();
	I down = width - 65;

	dt_main = &DAT;
	cnt_main = &CNT;
	crd_main = &COR;

	crd_main->dir = RIGHT;
	crd_main->rad = RANGE;


		/*	x 	*/
	// crd_main->kennel_x 	= L_LIM/2;					//< L_LIM == WIDTH/10; R_LIM = WIDTH*9/10
	crd_main->kennel_x 	= 30;
	crd_main->bowl_x 	= L_LIM/4;
	// crd_main->dog_x 	= 2 * L_LIM;
	crd_main->dog_x = 200;
	// crd_main->bar_x 	= R_LIM;
	crd_main->bar_x 	= 600;
	// crd_main->int_x 	= R_LIM + BAR_W - NOM_W;	//<	BAR_W ??? NOM_W ???
	crd_main->int_x 	= crd_main->int_x;
	crd_main->cle_x 	= crd_main->int_x;
	crd_main->sat_x 	= crd_main->int_x;

		/*	y 	*/
	// crd_main->kennel_y 	= D_LIM - KENNEL_H;			//<	D_LIM ??? KENNEL_H		
	crd_main->kennel_y 	= 100;
	crd_main->bowl_y 	= D_LIM - BOWL_H;			//< BOWL_H ???
	// crd_main->dog_y 	= D_LIM - DOG_H;				//<	DOG_H ????
	crd_main->dog_y = 100;
	// crd_main->bar_y 	= D_LIM - BAR_H;
	crd_main->bar_y 	= 100;
	crd_main->int_y 	= crd_main->bar_y;
	crd_main->cle_y 	= crd_main->bar_y - NOM_H;
	crd_main->sat_y 	= crd_main->int_x;

	crd = crd_main;
	dt = dt_main;
	cnt = cnt_main;
}


V set_window()			//< fullscreen, transparent, click-trough
{

	/*	something from gui/win.c 	*/

}
																	//!!!!!<	GTK+
V set_objects()		//< kennel, board, empty_bowl;
{

}


C is_tgt(S path)
{
	I len = strlen(path);

	if (!subcheck_d(path, "", len))
		R 0;

	if (!subcheck_d(path, "/pic/dog/0", len))					//< pic/dog check
		R 0;
	if (!subcheck_d(path, "/pic/dog/1", len))
		R 0;
	if (!subcheck_d(path, "/pic/dog/2", len))
		R 0;
	if (!subcheck_d(path, "/pic/dog/3", len))
		R 0;
	if (!subcheck_d(path, "/pic/dog/4", len))
		R 0;

	if (!subcheck_d(path, "/pic/obj", len))						//< pic/obj check
		R 0;

	if (!subcheck_d(path, "/pic/brd", len))						//<	pic/brd check
		R 0;

	R 1;
}


C is_home(S path)
{
	I len = strlen(path);


	if (!subcheck_d(path, "", len))
		R 0;

	if (!subcheck_d(path, "/Desktop", len))			//< pic/dog check
		R 0;
	
	R 1;
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


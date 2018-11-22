//<	set start data 
#include <stdlib.h>
#include <limits.h>
#include <dirent.h>
#include <string.h>
#include <errno.h>

#include "../cfg/cfg.h"
#include "../gui/win.h"
#include "../fld/wfile.h"
#include "../png/canvas.h"
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


///////////////////////////////////////////////////////////////
//<                  global dog data structs                >//
tm_cnt cnt;
dat dt;
coor crd;

//< stat_time contains all intervals for each dog action    >//
I stat_time[12] = {	1000, 1000, 1000, 3000, 4000, 7000, 
					7000, 1000, 1000, 1000, 3000, 0 };		//< /1000 --> get am in seconds 
S stat_name[12] = {	"sit", "run", "walk", "eat", "read_", 
					"die","rise","slp_1","slp_2","love","wc","R"};

//<                 enum for dog actions                    >//
D_STAT d_stat;

//<				height and width of a screen				>//
I height;
I width;

//<                         buffers                         >//
C NUM_INT[12];
C DOG_FILE[LINE_MAX_];
C FILENAME[LINE_MAX_];
S ADDR = FILENAME;
S* ADDR_ADDR = &ADDR;

//<                     start dog data                     >//
pDat DAT = {5, 5, 5, 2, 9};
pCounter CNT = {0,  0, 0, 0};
pCoor COR;
//<                                                         >//
///////////////////////////////////////////////////////////////

/*
Cnt:		//< counters
{
	I last_act;
	I satiety;
	I intellect;
	I cleanliness;
} 

Dt:			//< dog info
{
	C satiety;
	C intellect;
	C cleanliness;
	C colour;
	C action;
} 
*/


///////////////////////////////////////////////////////////////
//< set_data(dat dt_main, tm_cnt cnt_main, coor crd_main)   >//
///////////////////////////////////////////////////////////////
//<     set global variables    for ex:                     >//
//<     width, height, all coordinates, struct pointers     >//
///////////////////////////////////////////////////////////////
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


	pDat DAT = {5, 5, 5, 2, 9};
	pCounter CNT = {0,  0, 0, 0};

	dt_main->satiety = 5;
	dt_main->intellect = 5;
	dt_main->cleanliness = 5;
	dt_main->colour = 2;
	dt_main->action = 9;

	cnt_main->last_act = 0;
	cnt_main->satiety = 0;
	cnt_main->intellect = 0;
	cnt_main->cleanliness = 0;


		/*	x 	*/
	// crd_main->kennel_x 	= L_LIM/2;					//< L_LIM == WIDTH/10; R_LIM = WIDTH*9/10
	crd_main->kennel_x 	= 30;
	crd_main->bowl_x 	= L_LIM/4;
	// crd_main->dog_x 	= 2 * L_LIM;
	crd_main->dog_x = 200;
	// crd_main->bar_x 	= R_LIM;
	crd_main->bar_x 	= 600;
	// crd_main->int_x 	= R_LIM + BAR_W - NOM_W;		//<	BAR_W ??? NOM_W ???
	crd_main->int_x 	= crd_main->int_x;
	crd_main->cle_x 	= crd_main->int_x;
	crd_main->sat_x 	= crd_main->int_x;

		/*	y 	*/
	// crd_main->kennel_y 	= D_LIM - KENNEL_H;			//<	D_LIM ??? KENNEL_H		
	crd_main->kennel_y 	= 100;
	crd_main->bowl_y 	= D_LIM - BOWL_H;				//< BOWL_H ???
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


///////////////////////////////////////////////////////////////
//<                     set_window()                        >//
///////////////////////////////////////////////////////////////
//<         send call to some c++ functions to set          >//
//<     fullscreen transparent and click-through window     >//
///////////////////////////////////////////////////////////////
V set_window()			
{

	/*	something from gui/win.c 	*/

}

///////////////////////////////////////////////////////////////
//<                    check_env()                          >//
///////////////////////////////////////////////////////////////
//<     check for TGT_HOME and HOME env var existence       >//
///////////////////////////////////////////////////////////////
V check_env()
{
	S tgt_home = getenv("TGT_HOME"), home = getenv("HOME");

	if (tgt_home == NULL) {											//<	not null, exists, directory
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

///////////////////////////////////////////////////////////////
//<     set_start(tm_cnt cnt_, dat dt_, coor crd_)          >//
///////////////////////////////////////////////////////////////
//<     main checks and set data into cnt_, dt_ and crd_    >//
///////////////////////////////////////////////////////////////
V set_start(tm_cnt cnt_, dat dt_, coor crd_)
{
	check_env();
	set_data(dt_, cnt_, crd_);
	set_window();
	set_canvas();
}


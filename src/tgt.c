#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include "cfg.h"
#include "___.h"
#include "params.h"
#include "logic/struct.h"

#include "base/set.h"

#include "logic/draw.h"
#include "png/canvas.h"
#include "base/mains.h"

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

I main()
{
	I i, j = -1;
	C dog = 'd';
	// srand(time(NULL));
	set_start(dt, cnt, crd);

	O("\n\t\t%sSTART%s\n\n", CWUL, CNRM);


	set_canvas();

	ITER = 0;
	MAIN_IT = 0;


	dt->action = love;

	for (MAIN_IT = 0; dt->action != rise && dt->action != die; MAIN_IT++) {
		
		set_main_action();									//< 					logic/struct.c

		draw(dog, dt->action);								//<	draw action 		logic/draw.c

		cnt_upd(cnt, dt->action);							//<	increase timers 	logic/struct.c

		event_check();										//< eat event to update dat and timers

		cnt_check();										//< checking timers for updating dat 
															//<						logic/struct.c
		ITER++;

		if (death())										//<	conditions of death
			break;
	}
	draw(dog, dt->action);
	p_dog_stat(cnt, dt);

	O("%d ITERATIONS DONE\n", MAIN_IT);

	O("\n\t%d feeding\n\t%d cleaning\n\t%d reading\n\t%d del_file\n\t%d spit_file\n\n", test_cnt[0], test_cnt[1], test_cnt[2], test_cnt[3], test_cnt[4]);

	O("\n\t\t%sEND%s\n\n", CWUL, CNRM);
	R0;
}









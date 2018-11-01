#include <stdio.h>
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

I stat_time[12] = 	{	250000, 250000,250000, 750000,1000000, 1750000,1750000, 250000, 	250000,  	250000, 750000, 	0};		//< div /2
S stat_name[12] = 	{	"sit", "run", "walk", "eat", "read_", "die", "rise", "sleep_1", "sleep_2", 	"love", "wc", "return"};

D_STAT d_stat;

I height;
I width;


I main()
{

	I i, j = -1, k = 0;
	set_start(dt, cnt, crd);

	set_canvas();
	// R0;


	// set_main_action();
	// draw("dog", dt->action);
	


	for (i = 0; i < 100 && dt->action != rise && dt->action != die; i++) {
		
		set_main_action();									//< 					logic/struct.c
		if (j != dt->action && j != -1)
			k = i;
		j = dt->action;

		draw("dog", dt->action);							//<	draw action 		logic/draw.c
		cnt_upd(cnt, dt->action);							//<	increase timers 	logic/struct.c

		event_check();									//< eat event to update dat and timers
		cnt_check();										//< checking timers for updating dat 
															//<						logic/struct.c

		// R 0;
		if (death())										//<	conditions of death
			break;
	}
	
	 p_dog_stat(cnt, dt);

	 O("AT %d ACT CHANGED\n", k);
	O("DIE draw action %s\n", stat_name[dt->action]);
	O("END\n");
	R0;
}









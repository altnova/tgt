//<	C par[4] ++[draw.c/draw];
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

//<	C par[4] ++;
I main()
{
	I i, j = -1, k = 0, l;
	S dog = malloc(SZ(C) *4);
	// srand(time(NULL));
	set_start(dt, cnt, crd);

	set_canvas();
	// R0;

	strcpy(dog, "dog");
	// set_main_action();
	// draw("dog", dt->action);
	
	dt->action = love;


	for (i = 0; dt->action != rise && dt->action != die; i++) {
		
		set_main_action();									//< 					logic/struct.c


		draw(dog, dt->action);								//<	draw action 		logic/draw.c
		cnt_upd(cnt, dt->action);							//<	increase timers 	logic/struct.c

		event_check();										//< eat event to update dat and timers
		cnt_check();										//< checking timers for updating dat 
															//<						logic/struct.c

		// R 0;
		if (death())										//<	conditions of death
			break;
	}
	draw(dog, dt->action);
	p_dog_stat(cnt, dt);
	free(dog);
	O("%d ITERATIONS DONE\n", i);
	O("DIE draw action %s\n", stat_name[dt->action]);
	O("END\n");
	R0;
}









#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include "cfg.h"

#include "../lgc/struct.h"
#include "../bsc/set.h"
#include "../lgc/draw.h"
#include "../png/canvas.h"
#include "../bsc/mains.h"



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
		
		set_main_action();									//< 					lgc/struct.c

		draw(dog, dt->action);								//<	draw action 		lgc/draw.c

		cnt_upd(cnt, dt->action);							//<	increase timers 	lgc/struct.c

		event_check();										//< eat event to update dat and timers

		cnt_check();										//< checking timers for updating dat 
															//<						lgc/struct.c
		ITER++;

		if (death())										//<	conditions of death
			break;
	}
	draw(dog, dt->action);
	p_dog_stat(cnt, dt);

	end_canvas();

	O("%d ITERATIONS DONE\n", MAIN_IT);

	O("\n\t%d feeding\n\t%d cleaning\n\t%d reading\n\t%d del_file\n\t%d spit_file\n\n", test_cnt[0], test_cnt[1], test_cnt[2], test_cnt[3], test_cnt[4]);

	O("\n\t\t%sEND%s\n\n", CWUL, CNRM);
	R0;
}









#include <stdio.h>
#include "cfg.h"
#include "___.h"
#include "params.h"
#include "logic/struct.h"

#include "base/set.h"
#include "logic/draw.h"

tm_cnt cnt;
dat dt;
coor crd;

I stat_time[12] = 	{	1000000, 1000000, 1000000, 	1000000, 1000000, 1000000, 1000000, 1000000, 1000000, 1000000, 1000000, 0};
S stat_name[12] = 	{	"sit", "run", "walk", "eat", "read_", "die", "rise", "sleep_1", "sleep_2", 	"love", "wc", "return"};

D_STAT d_stat;



I main()
{
	set_start(dt, cnt, crd);

	W(dt->action != rise && dt->action != die) {
		
		set_main_action();									//< logic/struct.c
		draw("dog", dt->action);							//<	draw action 		[]
		cnt_upd(cnt, dt->action);							//<	increase timers

		// event_check();									//< eat event to update dat and timers
		cnt_check();										//< checking timers for updating dat

		if (death())										//<	conditions of death
			break;
	}
	
	O("DIE draw action %s\n", stat_name[dt->action]);
	O("END\n");
	R0;
}









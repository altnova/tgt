#include <stdio.h>
#include "base/___.h"
#include "struct.h"
#include "base/cfg.h"
#include "set.h"
#include "draw.h"

tm_cnt cnt;
dat dt;
coor crd;

I main()
{
	
	set_start(dt, cnt, crd)

	W(dt->action != rise && dt->action != die) {
		
		set_main_action();
		draw("dog", dt->action);			//<	draw action
		cnt_upd(dt->action);								//<	increase timers

		// event_check();								//< eat event to update dat and timers
		cnt_check();										//< checking timers for updating dat

		if (death())									//<	conditions of death
			break;
	}
	
	O("DIE draw action %s\n", stat_name[dt->action]);
	O("END\n");
	R0;
}






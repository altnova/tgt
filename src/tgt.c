#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dos.h>
#include <unistd.h>
#include "h/draw.h"
#include "h/esfile.h"
#include "h/___.h"
#include "h/struct.h"
#include "h/cfg.h"




I main()
{
	pDat dt_main = {5, 5, 5, 2, 9, 0, 0};
	pCounter cnt_main = {0, 0, 0, 0};
	dat dt = &dt_main;
	counter cnt = &cnt_main;


	W(dt->action != rise && dt->action != die) {
		set_main_action(cnt, dt);
		O("draw action %s\n", stat_name[dt->action]);			//<	draw action
		cnt_upd(cnt, dt->action);								//<	increase timers

		// event_check(cnt, dt);								//< eat event to update dat and timers
		cnt_check(cnt, dt);										//< checking timers for updating dat

		if (params_check(dt))									//<	conditions of death
			break;
	}
	
	O("DIE draw action %s\n", stat_name[dt->action]);
	O("END\n");
	R0;
}






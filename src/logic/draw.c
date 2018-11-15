//< C FILENAME[PATH_MAX] ++;
#include <stdlib.h>
#include <string.h>
#include "../___.h"
#include "../cfg.h"

#include "../params.h"
#include "../gui/win.h"
#include "../visual/del_s.h"
#include "../png/canvas.h"

#include "../base/mains.h"

#include "../globals.h"

//< C FILENAME[PATH_MAX] ++;
V board_show(C key, C obj)		//<	change params on board (through canvas.png)
{
	UH x, y;

	arrcat(FILENAME, "pic/brd/nom_0.png\0", 0);

	O("\n%s[board_show()]%s\t", CWHT, CNRM);
	O("'%c' --> '%c' + 'obj'(%d)\n\n", obj + FILENAME[12], FILENAME[12], obj);
	fflush(stdout);
	FILENAME[12] += obj;


	SW(key)													//<	set filename and crd
	{
		CS('s', {x = crd->sat_x; y = crd->sat_y;});
		CS('i', {x = crd->int_x; y = crd->int_y;});
		CS('c', {x = crd->cle_x; y = crd->cle_y;});
	}

	add_to_canvas(1, &ADDR, &x, &y);

}

V dog_show(I obj)				//< choose type of action to show
{
	// O("[dog_show(%s)]\n", stat_name[obj]);
	SW(obj) {
		CS(sit, 	{dog_sit(		stat_time	[obj]);		} );
		CS(run, 	{dog_run(		stat_time	[obj]);		} );
		CS(walk, 	{dog_walk(		stat_time	[obj]);		} );
		CS(eat, 	{dog_eat(		stat_time	[obj]);		} );
		CS(read_, 	{dog_read(		stat_time	[obj]);		} );
		CS(die, 	{dog_die(		stat_time	[obj]);		} );
		CS(rise, 	{dog_rise(		stat_time	[obj]);		} );
		CS(sleep_1, {dog_sleep_1(	stat_time	[obj]);		} );
		CS(sleep_2, {dog_sleep_2(	stat_time	[obj]);		} );
		CS(love, 	{dog_love(		stat_time	[obj]);		} );
		CS(poop, 	{dog_poop(		stat_time	[obj]);		} );
		CS(return_, {dog_return(					 );		} );
	}
}

V draw(C key, I obj)			//<	change canvas or tmp.png?
{
	(key == 'd') ? dog_show(obj) : board_show(key, obj);
}

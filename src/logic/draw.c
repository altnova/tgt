//< C FILENAME[PATH_MAX] ++;
#include <stdlib.h>
#include <string.h>
#include "../___.h"
#include "../cfg.h"

#include "../params.h"
#include "../gui/win.h"
#include "../visual/del_s.h"
#include "../png/canvas.h"


//< C FILENAME[PATH_MAX] ++;
V board_show(C key, C obj)		//<	change params on board (through canvas.png)
{
	UH x, y;
	// C filename[21] = { '.', '.', '/', 'p', 'i', 'c', '/', 'b', 'r', 'd', '/', 'n', 'o', 'm', '_', '0', '.', 'p', 'n', 'g', '\0'};
/*	S filename = "pic/brd/nom_0.png\0";
	O("iM IN BOARD SHOW\n");
	O("%d --> 0(%d) + 'obj'(%d)\n", obj + filename[12], filename[12], obj);
	fflush(stdout);
	filename[12] = filename[12] + obj;*/

	S filename = malloc(SZ(C) * 25);
	strcpy(filename, "pic/brd/nom_0.png\0");

	O("\n%s[board_show()]%s\t", CWHT, CNRM);
	O("'%c' --> '%c' + 'obj'(%d)\n\n", obj + filename[12], filename[12], obj);
	fflush(stdout);
	filename[12] += obj;


	SW(key)													//<	set filename and crd
	{
		CS('s', {x = crd->sat_x; y = crd->sat_y;});
		CS('i', {x = crd->int_x; y = crd->int_y;});
		CS('c', {x = crd->cle_x; y = crd->cle_y;});
	}

	add_to_canvas(1, &filename, &x, &y);
	free(filename);
}

V dog_show(I obj)				//< choose type of action to show
{
	// O("[dog_show(%s)]\n", stat_name[obj]);
	SW(obj) {
		CS(sit, 	{dog_sit(		stat_time		[obj]);			} );
		CS(run, 	{dog_run(		stat_time		[obj]);			} );
		CS(walk, 	{dog_walk(		stat_time		[obj]);			} );
		CS(eat, 	{dog_eat(		stat_time		[obj]);			} );
		CS(read_, 	{dog_read(		stat_time		[obj]);			} );
		CS(die, 	{dog_die(		stat_time		[obj]);			} );
		CS(rise, 	{dog_rise(		stat_time		[obj]);			} );
		CS(sleep_1, {dog_sleep_1(	stat_time		[obj]);			} );
		CS(sleep_2, {dog_sleep_2(	stat_time		[obj]);			} );
		CS(love, 	{dog_love(		stat_time		[obj]);			} );
		CS(poop, 	{dog_poop(		stat_time		[obj]);			} );
		CS(return_, {dog_return(						 );			} );
	}
}

V draw(S key, I obj)			//<	change canvas or tmp.png?
{
	C c = key[0];
	(c == 'd') ? dog_show(obj) : board_show(key[0], obj);
}


#include "del.h"
// #include <stdarg.h>

V board_show(C key, I obj)
{
	UH x, y;
	C filename[21] = { '.', '.', '/', 'p', 'i', 'c', '/', 'b', 'r', 'd', '/', 'n', 'o', 'm', '_', '0', '.', 'p', 'n', 'g', '\0'};
	filename[15] += obj;
	// filename[11] = key;
/*
	SW(key)													//<	set filename and coor
	{
		CS('s', {filename[12] = 'a'; filename[13] = 't'; x = coor->sat_x; y = coor->sat_y;});
		CS('i', {filename[12] = 'n'; filename[13] = 't'; x = coor->int_x; y = coor->int_y;});
		CS('c', {filename[12] = 'l'; filename[13] = 'e'; x = coor->cle_x; y = coor->cle_y;});
	}
*/
	SW(key)													//<	set filename and coor
	{
		CS('s', {x = coor->sat_x; y = coor->sat_y;});
		CS('i', {x = coor->int_x; y = coor->int_y;});
		CS('c', {x = coor->cle_x; y = coor->cle_y;});
	}


	depict(filename, x, y);
}

/*
V iter_depict(I num, ...)    	//<	for ex 	4 125 18 filename_1 filename_2
{
	va_list valist;
	I i;
	va_start(valist, num);

	for (i = 0; i < num; i++) 
		O("%s\n", va_arg(valist, S));
}
*/

/*
enum d_stat {		sit, run, walk, eat, read_, die, rise, 	sleep_1, 	sleep_2, 	love, 	poop};
I stat_time[11] = {	500, 500, 500, 	500, 500, 	500, 500, 	500, 		500, 		500, 	5000};
*/

V dog_show(I obj)
{
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
	}
}

V draw(S key, I obj)
{
	if (key[0] == 'd')
		dog_show(obj);
	else 
		board_show(key[0], obj);
}

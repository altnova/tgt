#include "../___.h"

#include "../visual/del_s.h"
#include "../gui/win.h"
#include "../cfg.h"

#include "../params.h"


// ext coor crd;

/*ext D_STAT d_stat;
ext I stat_time[12];
ext S stat_name[12];
*/

V board_show(C key, I obj)
{
	UH x, y;
	// C filename[21] = { '.', '.', '/', 'p', 'i', 'c', '/', 'b', 'r', 'd', '/', 'n', 'o', 'm', '_', '0', '.', 'p', 'n', 'g', '\0'};
	C filename[21] = "../../pic/brd/nom_0.png";
	filename[15] += obj;

	SW(key)													//<	set filename and crd
	{
		CS('s', {x = crd->sat_x; y = crd->sat_y;});
		CS('i', {x = crd->int_x; y = crd->int_y;});
		CS('c', {x = crd->cle_x; y = crd->cle_y;});
	}

	depict(1, &filename, &x, &y);
}

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
		CS(return_, {dog_return(						 );			} );
	}
}

V draw(S key, I obj)
{
	(key[0] == 'd') ? dog_show(obj) : board_show(key[0], obj);
}

#include <unistd.h>
#include "../base/cfg.h"
#include "../struct.h"
#include "../mains.h"

ext dat dt;
ext coor crd;

V depict(S filename, I x, I y)										//<!!! 	GTK+
{
	O("%s\t\tx-> %d y->%d", filename, x, y);
}


V this_way(I pause, S file_1, S file_2, S act, I way)
{
	depict(colour(file_1, dt), crd->dog_x, crd->dog_y);
	crd->dir = way;
	if (way)
		crd->dog_x += (act[0] == 'r') ? DIFRUN : DIFWALK;
	else 
		crd->dog_x -= (act[0] == 'r') ? DIFRUN : DIFWALK;

	usleep(pause/2);
	depict(colour(file_2, dt), crd->dog_x, crd->dog_y);
	usleep(pause/2);
}


V dog_sit(I pause)
{
	depict(colour("../../pic/dog/sit_1.png", dt), crd->dog_x, crd->dog_y);
	usleep(pause/2);
	depict(colour("../../pic/dog/sit_2.png", dt), crd->dog_x, crd->dog_y);
	usleep(pause/2);
}

V dog_run(I pause)
{
	(crd->dog_x <= L_LIM || (crd->dog_x < R_LIM && crd->dir)) 	?						
				this_way(pause, "../../pic/dog/run_r_1.png", "../../pic/dog/run_r_2.png", "run", RIGHT)		//<	run RIGHT
																:
				this_way(pause, "../../pic/dog/run_l_1.png", "../../pic/dog/run_l_2.png", "run", LEFT);		//< run LEFT
}

V dog_walk(I pause)
{

	(crd->dog_x <= L_LIM || (crd->dog_x < R_LIM && crd->dir)) 	?
				this_way(pause, "../../pic/dog/walk_r_1.png", "../../pic/dog/walk_r_2.png", "walk", RIGHT)	//< walk RIGHT
																:
				this_way(pause, "../../pic/dog/walk_l_1.png", "../../pic/dog/walk_l_2.png", "walk", LEFT);	//<	walk LEFT
}

/*

V dog_run_back()
{
	W(crd->dog_x > L_LIM) {
		dog_run(run);
		cnt_upd(run);
	}
}
V dog_walk_back()								
{
	W(crd->dog_x > L_LIM) {
		dog_walk(walk);
		cnt_upd(walk);
	}
}
*/
V dog_return()
{
	// (dt->satiety > STLIM && dt->cleanliness > CLLIM) 	? dog_run_back() :  dog_walk_back();
	(dt->satiety > STLIM && dt->cleanliness > CLLIM) 	? 	W(crd->dog_x > L_LIM) {
																dog_run(run);
																cnt_upd(run);} 
														:  	W(crd->dog_x > L_LIM) {
																dog_walk(walk);
																cnt_upd(walk);};
}


V dog_sleep_1(I pause)
{
	depict(colour("../../pic/dog/sleep_1_1.png", dt), crd->dog_x, crd->dog_y);
	usleep(pause/2);
	depict(colour("../../pic/dog/sleep_1_2.png", dt), crd->dog_x, crd->dog_y);
	usleep(pause/2);
}

V dog_sleep_2(I pause)
{
	dog_return();

	depict(colour("../../pic/dog/sleep_2_1.png", dt), crd->dog_x, crd->dog_y);
	usleep(pause/2);
	depict(colour("../../pic/dog/sleep_2_2.png", dt), crd->dog_x, crd->dog_y);
	usleep(pause/2);
}
												//<	both needs running back
V dog_eat(I pause)
{
	I i, p = pause/6;
	depict("../../pic/obj/bowl_full.png", crd->bowl_x, crd->bowl_y);
	dog_return();

	DO(3, 	{  	depict(colour("../../pic/dog/eat_1.png", dt), crd->dog_x, crd->dog_y);
				usleep(p);
				depict(colour("../../pic/dog/eat_2.png", dt), crd->dog_x, crd->dog_y);
				usleep(p);});
	depict("../../pic/obj/bowl_empty.png", crd->bowl_x, crd->bowl_y);
}

V dog_read(I pause)
{
	I i, p = pause/12;
	DO(3,  {	depict(colour("../../pic/dog/read_1.png", dt), crd->dog_x, crd->dog_y);
				usleep(p);
				depict(colour("../../pic/dog/read_2.png", dt), crd->dog_x, crd->dog_y);
				usleep(p);
				depict(colour("../../pic/dog/read_3.png", dt), crd->dog_x, crd->dog_y);
				usleep(p);
				depict(colour("../../pic/dog/read_4.png", dt), crd->dog_x, crd->dog_y);
				usleep(p);})
}

V dog_die(I pause)				//< 	??????
{
	I i, p = pause/12;
	C filename[23] = { '.', '.', '/', '.', '.', '/', 'p', 'i', 'c', '/', 'd', 'o', 'g', '/', 'd', 'i', 'e', '_', 'n', '.', 'p', 'n', 'g'};

	DO(9, { filename[18] = i + '0' + 1;
			depict(colour(filename, dt), crd->dog_x, crd->dog_y);
			if (i > 5)
				crd->dog_y -= DIFY;
			usleep(p);});
}

V dog_rise(I pause)				//<		??????
{
	I i, p = pause/12;
	C filename[24] = {'.', '.', '/', '.', '.', '/', 'p', 'i', 'c', '/', 'd', 'o', 'g', '/', 'r', 'i', 's', 'e', '_', 'n', '.', 'p', 'n', 'g'};

	DO(9, {	filename[19] = i + '0';
			depict(colour(filename, dt), crd->dog_x, crd->dog_y);
			crd->dog_y -= DIFY;
			usleep(p);});
}

V dog_love(I pause)
{
	I i, p = pause/6;
	DO(2, {	depict(colour("../../pic/dog/love_1.png", dt), crd->dog_x, crd->dog_y);
			usleep(p);
			depict(colour("../../pic/dog/love_2.png", dt), crd->dog_x, crd->dog_y);
			usleep(p);
			depict(colour("../../pic/dog/love_3.png", dt), crd->dog_x, crd->dog_y);
			usleep(p);});
}

V dog_poop(I pause)
{
	depict(colour("../../pic/dog/poop_1.png", dt), crd->dog_x, crd->dog_y);
	usleep(pause/3);
	depict(colour("../../pic/dog/poop_2.png", dt), crd->dog_x, crd->dog_y);
	usleep(pause/3);
	depict(colour("../../pic/dog/poop_3.png", dt), crd->dog_x, crd->dog_y);
	usleep(pause/3);
}
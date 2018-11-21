//<	calculation method for choosing which pic to depict 
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

#include "../cfg/cfg.h"

#include "../lgc/struct.h"
#include "../bsc/mains.h"
#include "../gui/win.h"
#include "../png/canvas.h"


///////////////////////////////////////////////////////////////
//<	col_dep_slp(S file, C c, I am, S* f, UH* x, UH* y, I p)	>//
///////////////////////////////////////////////////////////////
//<			colour() depict() and usleep()					>//
//<			S file	-- 	file name to pass to colour()		>//
//<			C c   	-- 	colour number to pass to colour()	>//
//<			I am 	-- 	amount of files for depict()		>//
//<			S* f 	--	list of files for depict()			>//
//<			UH* x 	--	list of x coors for depict()		>//
//<			UH* y 	--	list of y coors for depict() 		>//
//<			I p 	--	pause for usleep					>//
///////////////////////////////////////////////////////////////
V col_dep_slp(S file, C c, I am, S* f, UH* x, UH* y, I p)
{
	colour(file, c);
	depict(am, f, x, y);
	usleep(p * SEC);
}

///////////////////////////////////////////////////////////////
//<		this_way(I pause, S file_1, S file_2, S act, I way)	>//
///////////////////////////////////////////////////////////////
//<			choose which way to run 						>//
//<			modify coordinates 								>//
//<			S file_1 --> walk_?_1 or run_?_1 				>//
//<			S file_2 --> walk_?_2 or run_?_2 				>//
//<			S act 	 --> name of dog act 					>//
//<			I way 	 --> direction [1/0]					>//	
///////////////////////////////////////////////////////////////
V this_way(I pause, S file_1, S file_2, S act, I way)			
{
	col_dep_slp(file_1, dt->colour, 1, ADDR_ADDR, &crd->dog_x, &crd->dog_y, pause/2);
	crd->dir = way;

	if (way)
		crd->dog_x += (act[0] == 'r') ? DIFRUN : DIFWALK;
	else 
		crd->dog_x -= (act[0] == 'r') ? DIFRUN : DIFWALK;

	col_dep_slp(file_2, dt->colour, 1, ADDR_ADDR, &crd->dog_x, &crd->dog_y, pause/2);
}

///////////////////////////////////////////////////////////////
//<					dog_sir(I pause)						>//
///////////////////////////////////////////////////////////////
//<			depict dog act sit with total pause I pause		>//
///////////////////////////////////////////////////////////////
V dog_sit(I pause)						
{
	col_dep_slp("pic/dog/sit_1.png", dt->colour, 1, ADDR_ADDR, &crd->dog_x, &crd->dog_y, pause/2);
	col_dep_slp("pic/dog/sit_2.png", dt->colour, 1, ADDR_ADDR, &crd->dog_x, &crd->dog_y, pause/2);
}

///////////////////////////////////////////////////////////////
//<					dog_run(I pause)						>//
///////////////////////////////////////////////////////////////
//<			depict dog act run with total pause I pause		>//
///////////////////////////////////////////////////////////////
V dog_run(I pause)
{
	(crd->dog_x <= L_LIM || (crd->dog_x < R_LIM && crd->dir)) 	?						
				this_way((pause*SEC), 	"pic/dog/run_r_1.png", 
										"pic/dog/run_r_2.png", "run", RIGHT)		//<	run RIGHT
																:
				this_way((pause*SEC), 	"pic/dog/run_l_1.png", 
										"pic/dog/run_l_2.png", "run", LEFT);		//< run LEFT
}

///////////////////////////////////////////////////////////////
//<					dog_walk(I pause)						>//
///////////////////////////////////////////////////////////////
//<			depict dog act walk with total pause I pause	>//
///////////////////////////////////////////////////////////////
V dog_walk(I pause)
{
	(crd->dog_x <= L_LIM || (crd->dog_x < R_LIM && crd->dir)) 	?
				this_way((pause*SEC), 	"pic/dog/walk_r_1.png", 
										"pic/dog/walk_r_2.png", "walk", RIGHT)	//< walk RIGHT
																:
				this_way((pause*SEC), 	"pic/dog/walk_l_1.png", 
										"pic/dog/walk_l_2.png", "walk", LEFT);	//<	walk LEFT
}

///////////////////////////////////////////////////////////////
//<						dog_return()						>//
///////////////////////////////////////////////////////////////
//<			choose the way of comming back to kennel 		>//
//<					depends on tirednes						>//
///////////////////////////////////////////////////////////////
V dog_return()
{
	// (dt->satiety > STLIM && dt->cleanliness > CLLIM) 	? dog_run_back() :  dog_walk_back();
	/*
	(dt->satiety > STLIM && dt->cleanliness > CLLIM) 	? 	W(crd->dog_x > L_LIM) {
																dog_run(run);
																cnt_upd(run);} 
														:  	W(crd->dog_x > L_LIM) {
																dog_walk(walk);
																cnt_upd(walk);};
																*/
	if (dt->satiety > STLIM && dt->cleanliness > CLLIM) {
		W(crd->dog_x > L_LIM) {
			dog_run(run);
			cnt_upd(cnt, run);
		}
	}
	else {
		W(crd->dog_x > L_LIM) {
			dog_walk(walk);
			cnt_upd(cnt, walk);
		}
	}
}

///////////////////////////////////////////////////////////////
//<					dog_sleep_1(I pause)					>//
///////////////////////////////////////////////////////////////
//<		depict dog act sleep_1 with total pause I pause		>//
///////////////////////////////////////////////////////////////
V dog_sleep_1(I pause)									//< outside [no strength to return]
{
	col_dep_slp("pic/dog/sleep_1_1.png", dt->colour, 1, ADDR_ADDR, 
										&crd->dog_x, &crd->dog_y, pause/2);
	col_dep_slp("pic/dog/sleep_1_2.png", dt->colour, 1, ADDR_ADDR, 
										&crd->dog_x, &crd->dog_y, pause/2);
}

///////////////////////////////////////////////////////////////
//<					dog_sleep_2(I pause)					>//
///////////////////////////////////////////////////////////////
//<		depict dog act sleep_2 with total pause I pause		>//
///////////////////////////////////////////////////////////////
V dog_sleep_2(I pause)									//< in kennel
{
	dog_return();

	col_dep_slp("pic/dog/sleep_2_1.png", dt->colour, 1, ADDR_ADDR, 
										&crd->dog_x, &crd->dog_y, pause/2);
	col_dep_slp("pic/dog/sleep_2_2.png", dt->colour, 1, ADDR_ADDR, 
										&crd->dog_x, &crd->dog_y, pause/2);
}

///////////////////////////////////////////////////////////////
//<					dog_eat(I pause)						>//
///////////////////////////////////////////////////////////////
//<			depict dog act eat with total pause I pause		>//
///////////////////////////////////////////////////////////////
V dog_eat(I pause)
{
	I i, p = pause/7;
	UH x[2], y[2];

	arrcat(FILENAME, "pic/obj/bowl_full.png", 0);
	add_to_canvas(1, ADDR_ADDR, &crd->kennel_x, &crd->kennel_y);

	O("%s DOG_RETURN%s && %sDOG_EAT%s\n", CBLU, CNRM, CRED, CNRM);

	dog_return();
	usleep(p*SEC);

	DO(3, 	{  	
			col_dep_slp("pic/dog/eat_1.png", dt->colour, 1, ADDR_ADDR, 
											&crd->dog_x, &crd->dog_y, p);
			col_dep_slp("pic/dog/eat_2.png", dt->colour, 1, ADDR_ADDR, 
											&crd->dog_x, &crd->dog_y, p);});

	set_canvas();
}

///////////////////////////////////////////////////////////////
//<					dog_read(I pause)						>//
///////////////////////////////////////////////////////////////
//<			depict dog act read with total pause I pause	>//
///////////////////////////////////////////////////////////////
V dog_read(I pause)
{
	I i, p = pause/12;

	O("%s DOG_READ%s\n", CBLU, CNRM);

	DO(3,  {	
			col_dep_slp("pic/dog/read_1.png", dt->colour, 1, ADDR_ADDR, 
												&crd->dog_x, &crd->dog_y, p);
			col_dep_slp("pic/dog/read_2.png", dt->colour, 1, ADDR_ADDR, 
												&crd->dog_x, &crd->dog_y, p);
			col_dep_slp("pic/dog/read_3.png", dt->colour, 1, ADDR_ADDR, 
												&crd->dog_x, &crd->dog_y, p);
			col_dep_slp("pic/dog/read_4.png", dt->colour, 1, ADDR_ADDR, 
												&crd->dog_x, &crd->dog_y, p);});
}

///////////////////////////////////////////////////////////////
//<					dog_die(I pause)						>//
///////////////////////////////////////////////////////////////
//<			depict dog act die with total pause I pause		>//
///////////////////////////////////////////////////////////////
V dog_die(I pause)			
{
	I i, p = pause/9, len;

	arrcat(DOG_FILE, "pic/dog/die_n.png", 0);
	O("%s DOG_DIE%s\n", CRED, CNRM);

	DO(9, { 
			DOG_FILE[12] = i + '1';
			col_dep_slp(DOG_FILE, dt->colour, 1, ADDR_ADDR, 
									&crd->dog_x, &crd->dog_y, p);});			
}

///////////////////////////////////////////////////////////////
//<					dog_rise(I pause)						>//
///////////////////////////////////////////////////////////////
//<			depict dog act rise with total pause I pause	>//
///////////////////////////////////////////////////////////////
V dog_rise(I pause)				
{
	I i, p = pause/9;

	arrcat(DOG_FILE, "pic/dog/rise_n.png", 0);

	O("%s DOG_RISE%s\n", CRED, CNRM);

	DO(9, {	
			DOG_FILE[19] = i + '1';
			col_dep_slp(DOG_FILE, dt->colour, 1, ADDR_ADDR, 
									&crd->dog_x, &crd->dog_y, p);});
}

///////////////////////////////////////////////////////////////
//<					dog_love(I pause)						>//
///////////////////////////////////////////////////////////////
//<			depict dog act love with total pause I pause	>//
///////////////////////////////////////////////////////////////
V dog_love(I pause)
{
	I i, p = pause/6;
	
	O("%sDOG_LOVE%s\n", CBLU, CNRM);
	DO(3, {	
			col_dep_slp("pic/dog/love_1.png", dt->colour, 1, ADDR_ADDR, 
											&crd->dog_x, &crd->dog_y, p);
			col_dep_slp("pic/dog/love_2.png", dt->colour, 1, ADDR_ADDR, 
											&crd->dog_x, &crd->dog_y, p);});
}

///////////////////////////////////////////////////////////////
//<					dog_poop(I pause)						>//
///////////////////////////////////////////////////////////////
//<			depict dog act poop with total pause I pause	>//
///////////////////////////////////////////////////////////////
V dog_poop(I pause)
{
	O("%s DOG_UNPLEASED%s\n", CRED, CNRM);

	col_dep_slp("pic/dog/poop_1.png", dt->colour, 1, ADDR_ADDR, 
										&crd->dog_x, &crd->dog_y, pause/3);
	col_dep_slp("pic/dog/poop_2.png", dt->colour, 1, ADDR_ADDR, 
										&crd->dog_x, &crd->dog_y, pause/3);
	col_dep_slp("pic/dog/poop_3.png", dt->colour, 1, ADDR_ADDR, 
										&crd->dog_x, &crd->dog_y, pause/3);
}

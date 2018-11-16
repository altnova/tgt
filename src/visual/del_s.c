//< C STR[?] ++ (used few times parallel); C FILENAME[?] ++ (used few times parallel); C STRS[?][?] ++;
//<```	free arg for colour 
//<	
#include <stdlib.h>

#include <unistd.h>
#include <string.h>
#include "../cfg/cfg.h"

#include "../logic/struct.h"
#include "../base/mains.h"
#include "../params.h"
#include "../gui/win.h"
#include "../png/canvas.h"



V this_way(I pause, S file_1, S file_2, S act, I way)			//< which way to move
{
	colour(file_1, dt->colour);
	depict(1, ADDR_ADDR,  &crd->dog_x, &crd->dog_y);
	crd->dir = way;
	if (way)
		crd->dog_x += (act[0] == 'r') ? DIFRUN : DIFWALK;
	else 
		crd->dog_x -= (act[0] == 'r') ? DIFRUN : DIFWALK;

	colour(file_2, dt->colour);
	usleep((pause*SEC)/2);
	depict(1, ADDR_ADDR, &crd->dog_x, &crd->dog_y);
	usleep((pause*SEC)/2);
}

V dog_sit(I pause)						
{
	colour("pic/dog/sit_1.png", dt->colour);
	depict(1, ADDR_ADDR, &crd->dog_x, &crd->dog_y);
	usleep((pause*SEC)/2);
	colour("pic/dog/sit_2.png", dt->colour);
	depict(1, ADDR_ADDR, &crd->dog_x, &crd->dog_y);
	usleep((pause*SEC)/2);
}

V dog_run(I pause)
{
	(crd->dog_x <= L_LIM || (crd->dog_x < R_LIM && crd->dir)) 	?						
				this_way((pause*SEC), "pic/dog/run_r_1.png", "pic/dog/run_r_2.png", "run", RIGHT)		//<	run RIGHT
																:
				this_way((pause*SEC), "pic/dog/run_l_1.png", "pic/dog/run_l_2.png", "run", LEFT);		//< run LEFT
}

V dog_walk(I pause)
{
	(crd->dog_x <= L_LIM || (crd->dog_x < R_LIM && crd->dir)) 	?
				this_way((pause*SEC), "pic/dog/walk_r_1.png", "pic/dog/walk_r_2.png", "walk", RIGHT)	//< walk RIGHT
																:
				this_way((pause*SEC), "pic/dog/walk_l_1.png", "pic/dog/walk_l_2.png", "walk", LEFT);	//<	walk LEFT
}

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

V dog_sleep_1(I pause)									//< outside [no strength to return]
{
	colour("pic/dog/sleep_1_1.png", dt->colour);
	depict(1, ADDR_ADDR, &crd->dog_x, &crd->dog_y);
	usleep((pause*SEC)/2);
	colour("pic/dog/sleep_1_2.png", dt->colour);
	depict(1, ADDR_ADDR, &crd->dog_x, &crd->dog_y);
	usleep((pause*SEC)/2);
}

V dog_sleep_2(I pause)									//< in kennel
{
	
	colour("pic/dog/sleep_2_1.png", dt->colour);
	dog_return();
	depict(1, ADDR_ADDR, &crd->dog_x, &crd->dog_y);
	usleep((pause*SEC)/2);
	colour("pic/dog/sleep_2_2.png", dt->colour);
	depict(1, ADDR_ADDR, &crd->dog_x, &crd->dog_y);
	usleep((pause*SEC)/2);
}

												//<	both needs running back

//<	C STRS[?][?] ++;
V dog_eat(I pause)
{
	I i, p = pause/7;
	UH x[2], y[2];

	arrcat(FILENAME, "pic/obj/bowl_full.png", 0);

	// ADDR = FILENAME;
	add_to_canvas(1, ADDR_ADDR, &crd->kennel_x, &crd->kennel_y);

	O("%s DOG_RETURN%s && %sDOG_EAT%s\n", CBLU, CNRM, CRED, CNRM);

	dog_return();
	usleep(p*SEC);

	DO(3, 	{  	
				colour("pic/dog/eat_1.png", dt->colour);
				// strcpy(str[0], colour("pic/dog/eat_1.png", dt->colour));
				
				depict(1, ADDR_ADDR, &crd->dog_x, &crd->dog_y);
				usleep(p*SEC);

				// strcpy(str[0], colour("pic/dog/eat_1.png", dt->colour));
				colour("pic/dog/eat_2.png", dt->colour);
				depict(1, ADDR_ADDR, &crd->dog_x, &crd->dog_y);
				usleep(p*SEC);});

	set_canvas();
}

//< C FILENAME[?] ++;
V dog_read(I pause)
{
	I i, p = pause/12;

	O("%s DOG_READ%s\n", CBLU, CNRM);

	DO(3,  {	
				colour("pic/dog/read_1.png", dt->colour);
				depict(1, ADDR_ADDR, &crd->dog_x, &crd->dog_y);
				usleep(p*SEC);

				colour("pic/dog/read_2.png", dt->colour);
				depict(1, ADDR_ADDR, &crd->dog_x, &crd->dog_y);
				usleep(p*SEC);

				colour("pic/dog/read_3.png", dt->colour);
				depict(1, ADDR_ADDR, &crd->dog_x, &crd->dog_y);
				usleep(p*SEC);

				colour("pic/dog/read_4.png", dt->colour);
				depict(1, ADDR_ADDR, &crd->dog_x, &crd->dog_y);
				usleep(p*SEC);})

}

//< C STR[?] ++; C FILENAME[?] ++;
V dog_die(I pause)				//< 	??????
{
	I i, p = pause/9;

	arrcat(FILENAME, "pic/dog/die_n.png", 0);
	O("%s DOG_DIE%s\n", CRED, CNRM);

	DO(9, { FILENAME[18] = i + '1';
			colour(FILENAME, dt->colour);
			depict(1, ADDR_ADDR, &crd->dog_x, &crd->dog_y);

																			//< for a while
			// if (i > 5)
				// crd->dog_y -= DIFY;
			usleep(p*SEC);});
}

//< C STR[?] ++; C FILENAME[?] ++;
V dog_rise(I pause)				//<		??????
{
	I i, p = pause/9;

	arrcat(FILENAME, "pic/dog/rise_n.png", 0);

	O("%s DOG_RISE%s\n", CRED, CNRM);

	DO(9, {	FILENAME[19] = i + '1';
			colour(FILENAME, dt->colour);

			depict(1, ADDR_ADDR, &crd->dog_x, &crd->dog_y);
			usleep(p*SEC);});
}

//< C STR[?] ++; 
V dog_love(I pause)
{
	I i, p = pause/6;
	
	O("%sDOG_LOVE%s\n", CBLU, CNRM);
	DO(3, {	
			colour("pic/dog/love_1.png", dt->colour);
			depict(1, ADDR_ADDR, &crd->dog_x, &crd->dog_y);
			usleep(p*SEC);
			colour("pic/dog/love_2.png", dt->colour);
			depict(1, ADDR_ADDR, &crd->dog_x, &crd->dog_y);
			usleep(p*SEC);});
}

//< C STR[?] ++; 
V dog_poop(I pause)
{
	O("%s DOG_UNPLEASED%s\n", CRED, CNRM);

	colour("pic/dog/poop_1.png", dt->colour);
	depict(1, ADDR_ADDR, &crd->dog_x, &crd->dog_y);
	usleep((pause*SEC)/3);

	colour("pic/dog/poop_2.png", dt->colour);
	depict(1, ADDR_ADDR, &crd->dog_x, &crd->dog_y);
	usleep((pause*SEC)/3);

	colour("pic/dog/poop_3.png", dt->colour);
	depict(1, ADDR_ADDR, &crd->dog_x, &crd->dog_y);
	usleep((pause*SEC)/3);
}



//<```	free arg for colour 

#include <stdlib.h>

#include <unistd.h>
#include <string.h>
#include "../___.h"
#include "../cfg.h"
#include "../logic/struct.h"
#include "../base/mains.h"
#include "../params.h"
#include "../gui/win.h"

/*ext dat dt;
ext coor crd;
ext tm_cnt cnt;*/

/*ext D_STAT d_stat;
ext I stat_time[12];
ext S stat_name[12];
*/


V this_way(I pause, S file_1, S file_2, S act, I way)			//< which way to move
{
	S str = colour(file_1, dt->colour);
	depict(1, &str,  &crd->dog_x, &crd->dog_y);
	crd->dir = way;
	if (way)
		crd->dog_x += (act[0] == 'r') ? DIFRUN : DIFWALK;
	else 
		crd->dog_x -= (act[0] == 'r') ? DIFRUN : DIFWALK;

	str = colour(file_2, dt->colour);
	usleep((pause*SEC)/2);
	depict(1, &str, &crd->dog_x, &crd->dog_y);
	usleep((pause*SEC)/2);
}


V dog_sit(I pause)						
{
	S str = colour("pic/dog/sit_1.png", dt->colour);
	depict(1, &str, &crd->dog_x, &crd->dog_y);
	usleep((pause*SEC)/2);
	str = colour("pic/dog/sit_2.png", dt->colour);
	depict(1, &str, &crd->dog_x, &crd->dog_y);
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
	S str = colour("pic/dog/sleep_1_1.png", dt->colour);
	depict(1, &str, &crd->dog_x, &crd->dog_y);
	usleep((pause*SEC)/2);
	str = colour("pic/dog/sleep_1_2.png", dt->colour);
	depict(1, &str, &crd->dog_x, &crd->dog_y);
	usleep((pause*SEC)/2);
}

V dog_sleep_2(I pause)									//< in kennel
{
	
	S str = colour("pic/dog/sleep_2_1.png", dt->colour);
	dog_return();
	depict(1, &str, &crd->dog_x, &crd->dog_y);
	usleep((pause*SEC)/2);
	str = colour("pic/dog/sleep_2_2.png", dt->colour);
	depict(1, &str, &crd->dog_x, &crd->dog_y);
	usleep((pause*SEC)/2);
}
												//<	both needs running back
V dog_eat(I pause)
{
	I i, p = pause/7;
	UH x[2], y[2];
	S str_1 = colour("pic/dog/eat_1.png", dt->colour);
	S str_2 = colour("pic/dog/eat_2.png", dt->colour);

	S *str = malloc(SZ(S) * 2);
	str[0] = malloc(SZ(C) * 50);
	str[1] = malloc(SZ(C) * 50);

	strcpy(str[0], colour("pic/dog/eat_1.png", dt->colour));
	strcpy(str[1], "pic/obj/bowl_full.png");

	O("%s DOG_RETURN%s && %sDOG_EAT%s\n", CBLU, CNRM, CRED, CNRM);

	dog_return();
	usleep(p*SEC);

///////////////////////////////////////////////////////////////////////////////////////////

	x[0] = crd->dog_x;	
	x[1] = crd->bowl_x;
	y[0] = crd->dog_y;
	y[1] = crd->bowl_y;
	
	strcpy(str[1], "pic/obj/bowl_full.png");

	DO(3, 	{  	strcpy(str[0], colour("pic/dog/eat_1.png", dt->colour));
				
				depict(2, str, x, y);
				usleep(p*SEC);

				strcpy(str[0], colour("pic/dog/eat_1.png", dt->colour));

				depict(2, str, x, y);
				usleep(p*SEC);});
	strcpy(str[1], "pic/obj/bowl_empty.png");
	depict(2, str, x, y);
	free_array(str, 2);
}

V dog_read(I pause)
{
	I i, p = pause/12;
	S str = malloc(SZ(C) * 50);

	O("%s DOG_READ%s\n", CBLU, CNRM);

	DO(3,  {	
				strcpy(str, colour("pic/dog/read_1.png", dt->colour));
				depict(1, &str, &crd->dog_x, &crd->dog_y);
				usleep(p*SEC);

				strcpy(str, colour("pic/dog/read_2.png", dt->colour));
				depict(1, &str, &crd->dog_x, &crd->dog_y);
				usleep(p*SEC);

				strcpy(str, colour("pic/dog/read_3.png", dt->colour));
				depict(1, &str, &crd->dog_x, &crd->dog_y);
				usleep(p*SEC);

				strcpy(str, colour("pic/dog/read_4.png", dt->colour));
				depict(1, &str, &crd->dog_x, &crd->dog_y);
				usleep(p*SEC);})

	free(str);
}

V dog_die(I pause)				//< 	??????
{
	I i, p = pause/9;
	// C filename[23] = { '.', '.', '/', '.', '.', '/', 'p', 'i', 'c', '/', 'd', 'o', 'g', '/', 'd', 'i', 'e', '_', 'n', '.', 'p', 'n', 'g'};
	// C filename[23] = "pic/dog/die_n.png";

	S str = malloc(SZ(C) * 100), filename = malloc(SZ(C)* 23);
	strcpy(filename, "pic/dog/die_n.png");
	O("%s DOG_DIE%s\n", CRED, CNRM);

	DO(9, { filename[18] = i + '1';
			strcpy(str, colour(filename, dt->colour));
			depict(1, &str, &crd->dog_x, &crd->dog_y);

																			//< for a while
			// if (i > 5)
				// crd->dog_y -= DIFY;
			usleep(p*SEC);});
	free(str);
	free(filename);

}

V dog_rise(I pause)				//<		??????
{
	I i, p = pause/9;
	// C filename[24] = {'.', '.', '/', '.', '.', '/', 'p', 'i', 'c', '/', 'd', 'o', 'g', '/', 'r', 'i', 's', 'e', '_', 'n', '.', 'p', 'n', 'g'};
	// C filename[24] = "pic/dog/rise_n.png";
	S filename = malloc(SZ(C) * 24);
	S str = malloc(SZ(C) * 100);

	strcpy(filename, "pic/dog/rise_n.png");

	O("%s DOG_RISE%s\n", CRED, CNRM);

	DO(9, {	filename[19] = i + '1';
			strcpy(str, colour(filename, dt->colour));
			depict(1, &str, &crd->dog_x, &crd->dog_y);
			// crd->dog_y -= DIFY;											//< for a while
			usleep(p*SEC);});
	free(str);
	free(filename);
}

V dog_love(I pause)
{
	I i, p = pause/6;
	S str = malloc(SZ(C) * 100);
	O("%sDOG_LOVE%s\n", CBLU, CNRM);
	DO(3, {	strcpy(str, colour("pic/dog/love_1.png", dt->colour));
			depict(1, &str, &crd->dog_x, &crd->dog_y);
			usleep(p*SEC);
			strcpy(str, colour("pic/dog/love_2.png", dt->colour));
			depict(1, &str, &crd->dog_x, &crd->dog_y);
			usleep(p*SEC);});
	free(str);
}

V dog_poop(I pause)
{
	S str = malloc(SZ(C) * 100);

	O("%s DOG_UNPLEASED%s\n", CRED, CNRM);
	strcpy(str, colour("pic/dog/poop_1.png", dt->colour));
	depict(1, &str, &crd->dog_x, &crd->dog_y);
	usleep((pause*SEC)/3);
	strcpy(str, colour("pic/dog/poop_2.png", dt->colour));
	depict(1, &str, &crd->dog_x, &crd->dog_y);
	usleep((pause*SEC)/3);
	strcpy(str, colour("pic/dog/poop_3.png", dt->colour));
	depict(1, &str, &crd->dog_x, &crd->dog_y);
	usleep((pause*SEC)/3);
	free(str);
}
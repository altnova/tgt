#include <unistd.h>
#include "cfg.h"
#include "struct.h"

ext dat dt;
ext coor crd;

V depict(S filename, I x, I y)
{
	O("%s\t\tx-> %d y->%d", filename, x, y);
}

V dog_sit(I pause)
{
	depict("../pic/dog/sit_1.png", crd->dog_x, crd->dog_y);
	usleep(pause/2);
	depict("../pic/dog/sit_2.png", crd->dog_x, crd->dog_y);
	usleep(pause/2);
}

V dog_run(I pause)
{
	if (crd->dog_x <= L_LIM || (crd->dog_x < R_LIM && crd->dir)) {			//<	run RIGHT
		depict("../pic/dog/run_r_1.png", crd->dog_x, crd->dog_y);
		crd->dog_x += DIFRUN;
		crd->dir = RIGHT;
		usleep(pause/2);
		depict("../pic/dog/run_r_2.png", crd->dog_x), crd->dog_y;
		usleep(pause/2);
	}
	else {																	//<	run LEFT
		depict("../pic/dog/run_l_1.png", crd->dog_x, crd->dog_y);
		crd->dog_x -= DIFRUN;
		crd->dir = LEFT;										
		usleep(pause/2);
		depict("../pic/dog/run_l_2.png", crd->dog_x), crd->dog_y;
		usleep(pause/2);
	}
}

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


V dog_walk(I pause)
{
	if (crd->dog_x <= L_LIM || (crd->dog_x < R_LIM && crd->dir)) {			//<	walk RIGHT
		depict("../pic/dog/walk_r_1.png", crd->dog_x, crd->dog_y);
		crd->dog_x += DIFRUN;
		crd->dir = 1;
		usleep(pause/2);
		depict("../pic/dog/walk_r_2.png", crd->dog_x), crd->dog_y;
		usleep(pause/2);
	}
	else {																	//<	walk LEFT
		depict("../pic/dog/walk_l_1.png", crd->dog_x, crd->dog_y);
		crd->dog_x -= DIFWALK;
		crd->dir = 0;
		usleep(pause/2);
		depict("../pic/dog/walk_l_2.png", crd->dog_x), crd->dog_y;
		usleep(pause/2);
	}
}

V dog_sleep_1(I pause)
{
	depict("../pic/dog/sleep_1_1.png", crd->dog_x, crd->dog_y);
	usleep(pause/2);
	depict("../pic/dog/sleep_1_2.png", crd->dog_x, crd->dog_y);
	usleep(pause/2);
}

V dog_sleep_2(I pause)
{
	(dt->satiety > STLIM && dt->cleanliness > CLLIM) 	? dog_run_back() :  dog_walk_back();

	depict("../pic/dog/sleep_2_1.png", crd->dog_x, crd->dog_y);
	usleep(pause/2);
	depict("../pic/dog/sleep_2_2.png", crd->dog_x, crd->dog_y);
	usleep(pause/2);
}
												//<	both needs running back
V dog_eat(I pause)
{
	(dt->satiety > STLIM && dt->cleanliness > CLLIM) 	? dog_run_back() :  dog_walk_back();
	depict("../pic/dog/eat_1.png", crd->dog_x, crd->dog_y);
	usleep(pause/2);
	depict("../pic/dog/eat_2.png", crd->dog_x, crd->dog_y);
	usleep(pause/2);
}

V dog_read(I pause)
{
	I i, p = pause/12;
	for (i = 0; i < 3; i++) {
		depict("../pic/dog/read_1.png", crd->dog_x, crd->dog_y);
		usleep(p);
		depict("../pic/dog/read_2.png", crd->dog_x, crd->dog_y);
		usleep(p);
		depict("../pic/dog/read_3.png", crd->dog_x, crd->dog_y);
		usleep(p);
		depict("../pic/dog/read_4.png", crd->dog_x, crd->dog_y);
		usleep(p);
	}
}

V dog_die(I pause)				//< 	??????
{
	I i, p = pause/12;
	C filename[20] = {'.', '.', '/', 'p', 'i', 'c', '/', 'd', 'o', 'g', '/', 'd', 'i', 'e', '_', 'n', '.', 'p', 'n', 'g'};

	for (i = 1; i < 10; i++) {
		filename[15] = i + '0';
		depict(filename, crd->dog_x, crd->dog_y);
		if (i > 5)
			crd->dog_y -= DIFY;
		usleep(p);
	}
}

V dog_rise(I pause)				//<		??????
{
	I i, p = pause/12;
	C filename[21] = {'.', '.', '/', 'p', 'i', 'c', '/', 'd', 'o', 'g', '/', 'r', 'i', 's', 'e', '_', 'n', '.', 'p', 'n', 'g'};

	for (i = 1; i < 10; i++) {
		filename[16] = i + '0';
		depict(filename, crd->dog_x, crd->dog_y);
		crd->dog_y -= DIFY;
		usleep(p);
	}
}

V dog_love(I pause)
{
	I i, p = pause/6;
	for (i = 0; i < 2; i++) {
		depict("../pic/dog/love_1.png", crd->dog_x, crd->dog_y);
		usleep(p);
		depict("../pic/dog/love_2.png", crd->dog_x, crd->dog_y);
		usleep(p);
		depict("../pic/dog/love_3.png", crd->dog_x, crd->dog_y);
		usleep(p);	
	}
}

V dog_poop(I pause)
{
	depict("../pic/dog/poop_1.png", crd->dog_x, crd->dog_y);
	usleep(pause/3);
	depict("../pic/dog/poop_2.png", crd->dog_x, crd->dog_y);
	usleep(pause/3);
	depict("../pic/dog/poop_3.png", crd->dog_x, crd->dog_y);
	usleep(pause/3);
}
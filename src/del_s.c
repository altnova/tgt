
V depict(S filename, I x, I y)
{
	O("%s\t\tx-> %d y->%d", filename, x, y);
}


V dog_run_back();										//<	!!!!!!!!!

V dog_walk_back();										//<	!!!!!!!!!


V dog_sit(I pause)
{
	depict("../pic/dog/sit_1.png", coor->dog_x, coor->dog_y);
	delay(pause/2);
	depict("../pic/dog/sit_2.png", coor->dog_x, coor->dog_y);
	delay(pause/2);
}

V dog_run(I pause)
{
	if (coor->dog_x <= L_LIM || (coor->dog_x < R_LIM && coor->dir)) {
		depict("../pic/dog/run_r_1.png", coor->dog_x, coor->dog_y);
		coor->dog_x += DIFRUN;
		delay(pause/2);
		depict("../pic/dog/run_r_2.png", coor->dog_x), coor->dog_y;
		delay(pause/2);
	}
	else {
		depict("../pic/dog/run_l_1.png", coor->dog_x, coor->dog_y);
		coor->dog_x -= DIFRUN;
		delay(pause/2);
		depict("../pic/dog/run_l_2.png", coor->dog_x), coor->dog_y;
		delay(pause/2);
	}
}

V dog_walk(I pause)
{
	if (coor->dog_x <= L_LIM || (coor->dog_x < R_LIM && coor->dir)) {
		depict("../pic/dog/walk_r_1.png", coor->dog_x, coor->dog_y);
		coor->dog_x += DIFRUN;
		delay(pause/2);
		depict("../pic/dog/walk_r_2.png", coor->dog_x), coor->dog_y;
		delay(pause/2);
	}
	else {
		depict("../pic/dog/walk_l_1.png", coor->dog_x, coor->dog_y);
		coor->dog_x -= DIFWALK;
		delay(pause/2);
		depict("../pic/dog/walk_l_2.png", coor->dog_x), coor->dog_y;
		delay(pause/2);
	}
}

V dog_sleep_1(I pause)
{
	depict("../pic/dog/sleep_1_1.png", coor->dog_x, coor->dog_y);
	delay(pause/2);
	depict("../pic/dog/sleep_1_2.png", coor->dog_x, coor->dog_y);
	delay(pause/2);
}

V dog_sleep_2(I pause);			//<	???????
												//<	both needs running back
V dog_eat(I pause); 			//<	???????

V dog_read(I pause)
{
	I i, p = pause/12;
	for (i = 0; i < 3; i++) {
		depict("../pic/dog/read_1.png", coor->dog_x, coor->dog_y);
		delay(p);
		depict("../pic/dog/read_2.png", coor->dog_x, coor->dog_y);
		delay(p);
		depict("../pic/dog/read_3.png", coor->dog_x, coor->dog_y);
		delay(p);
		depict("../pic/dog/read_4.png", coor->dog_x, coor->dog_y);
		delay(p);
	}
}

V dog_die(I pause)				//< 	??????
{
	//< some 12 pics
}

V dog_rise(I pause)				//<		??????
{
	//< some 12 pics
}

V dog_love(I pause)
{
	I i, p = pause/6;
	for (i = 0; i < 2; i++) {
		depict("../pic/dog/love_1.png", coor->dog_x, coor->dog_y);
		delay(p);
		depict("../pic/dog/love_2.png", coor->dog_x, coor->dog_y);
		delay(p);
		depict("../pic/dog/love_3.png", coor->dog_x, coor->dog_y);
		delay(p);	
	}
}

V dog_poop(I pause)
{
	depict("../pic/dog/poop_1.png", coor->dog_x, coor->dog_y);
	delay(pause/3);
	depict("../pic/dog/poop_2.png", coor->dog_x, coor->dog_y);
	delay(pause/3);
	depict("../pic/dog/poop_3.png", coor->dog_x, coor->dog_y);
	delay(pause/3);
}
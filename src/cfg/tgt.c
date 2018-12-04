//<	main!
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include "cfg.h"

#include "../lgc/struct.h"
#include "../bsc/set.h"
#include "../lgc/draw.h"
#include "../png/canvas.h"
#include "../bsc/mains.h"


I main()
{
	I i, j = -1;
	C dog = 'd';

	// E set_m_max, draw_max, cnt_upd_max, file_max, click_max, cnt_chk_max, st_max;
	clock_t set_m_s,	set_m_p, 	set_m_a = 0;
	clock_t draw_s, 	draw_p, 	draw_a = 0;
	clock_t cnt_upd_s, 	cnt_upd_p, 	cnt_upd_a = 0;
	clock_t file_s, 	file_p, 	file_a = 0;
	clock_t click_s, 	click_p, 	click_a = 0;
	clock_t cnt_chk_s, 	cnt_chk_p,	cnt_chk_a = 0;
	clock_t st_s, 		st_p,		st_a = 0;
	// srand(time(NULL));

	O("\n\t\t%sSTART%s\n\n", CWUL, CNRM);

	st_s = clock();
	set_start(dt, cnt, crd);
	st_p = clock();
	st_a = st_p - st_s;



	O("\tit took %s%f %ss for set_start()\n", CRED, (float)st_a / (float)CLOCKS_PER_SEC, CNRM);

	ITER = 0;
	
	dt->action = love;

	for (MAIN_IT = 0; dt->action != rise && dt->action != die; MAIN_IT++) {

		set_m_s = clock();
		set_main_action();									//< 					lgc/struct.c
		set_m_p = clock();
		set_m_a = MAX((set_m_p - set_m_s), set_m_a);

		draw_s = clock();
		draw(dog, dt->action);								//<	draw action 		lgc/draw.c
		draw_p = clock();
		draw_a = MAX((draw_p - draw_s), draw_a);

		cnt_upd_s = clock();
		cnt_upd(cnt, dt->action);							//<	increase timers 	lgc/struct.c
		// event_check();										//< eat event to update dat and timers
		cnt_upd_p = clock();
		cnt_upd_a = MAX((cnt_upd_p - cnt_upd_s), cnt_upd_a);
		
		file_s = clock();
		file_check();
		file_p = clock();
		file_a = MAX((file_p - file_s), file_a);

		click_s = clock();
		click_check();
		click_p = clock();
		click_a = MAX((click_p - click_s), click_a);

		cnt_chk_s = clock();
		cnt_check();										//< checking timers for updating dat 
		cnt_chk_p = clock();								//<						lgc/struct.c
		cnt_chk_a = MAX((cnt_chk_p - cnt_chk_s), cnt_chk_a);

		ITER++;

		if (death())										//<	conditions of death
			break;
	}

	draw(dog, dt->action);
	p_dog_stat(cnt, dt);
	end_canvas();

	O("%d ITERATIONS DONE\n", MAIN_IT);

	O("\n\t%d feeding\n\t%d cleaning\n\t", test_cnt[0], test_cnt[1]);
	O("%d reading\n\t%d del_file\n\t", test_cnt[2], test_cnt[3]);
	O("%d spit_file\n\n", test_cnt[4]);

	O("\tmax set_main_action() takes %f s\n", (float)set_m_a / (float)CLOCKS_PER_SEC);
	O("\tmax draw() takes %f s\n", (float)draw_a / (float)CLOCKS_PER_SEC);
	O("\tmax cnt_upd() takes %f s\n", (float)cnt_upd_a / (float)CLOCKS_PER_SEC);
	O("\tmax file_check() takes %f s\n", (float)file_a / (float)CLOCKS_PER_SEC);
	O("\tmax click_check() takes %f s\n", (float)click_a / (float)CLOCKS_PER_SEC);
	O("\tmax cnt_check() takes %f s\n\n", (float)cnt_chk_a / (float)CLOCKS_PER_SEC);


	O("\n\t\t%sEND%s\n\n", CWUL, CNRM);
	R0;
}









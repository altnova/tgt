//< main checks for counters and click/file_input events
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <unistd.h>
#include <limits.h>

#include "../cfg/cfg.h"

#include "../lgc/draw.h"
#include "../fld/esfile.h"
#include "../bsc/mains.h"
#include "../fld/wfile.h"

I ITER = 0;
I MAIN_IT = 0;

I test_cnt[5] = {0, 0, 0, 0, 0};


V cnt_upd(tm_cnt cnt_, I act)										//< cnt++ for ex. after action
{
	cnt_->last_act += stat_time[act];
	
	if (cnt->last_act > MAX_CNT_LA)
		cnt->last_act = MAX_CNT_LA;
	
	cnt_->satiety += stat_time[act];
	cnt_->intellect += stat_time[act];
	cnt_->cleanliness += stat_time[act];
}

C death()															//<	conditions of exit 	
{    
	X(!dt->satiety || dt->satiety > MAX_ST, {	dt->action = die; 						//<	dog dies and program aborts if satiety == 0 || satiety > MAX_ST 
												if (!dt->satiety) 
													O("\n\tyour dog died of %sstarvation%s. stupid\n\n", CRED, CNRM); 
												else 
												O("\n\tyour dog died of %sgluttony%s. feckless\n\n", CBLU, CNRM);},
												1);

	X(dt->intellect >= MAX_IN || dt->cleanliness > MAX_CL, {dt->action = rise;			//< dog rises if intellect > MAX_IN || cleanliness > MAX_CL
															if (dt->intellect >= MAX_IN) 
																O("\n\the was much %ssmarter%s than you\n\n", CBLU, CNRM);
															else 
																O("\n\the was as %sclean%s as your virginity\n\n", CWHT, CNRM);},
															1);
	R 0;
}

V cnt_check()														//<	conditions of modifing dt in case of appropriate cnt
{
	C state;
	// O("[cnt_check()]\n");
	if (cnt->satiety >= MAX_CNT_ST) {								//<	check for satiety
		cnt->satiety = 0;
		state = 's';
		draw(state, --dt->satiety);
		p_dog_stat();
	}

	if (cnt->intellect >= MAX_CNT_IN) {								//<	check for intellect
		cnt->intellect = 0;
		dt->intellect = dt->intellect ? --dt->intellect : dt->intellect;
		state = 'i';
		draw(state, dt->intellect);
		p_dog_stat();
	}

	if (cnt->cleanliness >= MAX_CNT_CL) {							//< check for cleanliness 
		cnt->cleanliness = 0;
		dt->cleanliness = dt->cleanliness ? --dt->cleanliness : dt->cleanliness;
		state = 'c';
		draw(state, dt->cleanliness);
		dt->colour = dt->cleanliness/2;
		p_dog_stat();
	}
}


C set_main_action()													//< set main action if nothing special happens
{
	C act = dt->action;;
	// O("[set_main_action()]\n");

	X((cnt->last_act < MAX_CNT_LA), {
		dt->action = 	(dt->satiety > STLIM && dt->cleanliness > CLLIM) 	? run 	: 
						(dt->satiety > STLIM && dt->cleanliness <= CLLIM)	? walk	: sit;}, 0);

	cnt->last_act = MAX_CNT_LA;

	dt->action = 	(dt->satiety > STLIM && dt->cleanliness > CLLIM)	? sleep_2 	: 				//< sleep_1 --> sleep where you are;	sleep_2 --> go to kennel
					(dt->action != sleep_2) 							? sleep_1 	:	sleep_2;

	if (act != dt->action) {
		O("\n%s%s%s to %s%s%s\n%d iterations between\n\n", CBLU, stat_name[act], CNRM, CRED,stat_name[dt->action], CNRM, ITER);
		p_dog_stat();
		ITER = 0;
	}
}

V event_check()														//< user's commands 
{
	/* GET FILE */

	I type;
	C r, dog = 'd', st;
	// O("[event_check()]\n");


//< this part is only for testing; in future it will get name of a file, 
//<	that user dragged to kennel coordinates IF MACOS
//< and will get filename from console, check existance etc. IF LINUX
/////////////////////////////////////////////////////////////////////////
	arrcat(FILENAME, "123\0", 0);

	if (MAIN_IT%100 == 0 || MAIN_IT%50 == 0) {
		r = rand()%5;
		SW(r) {
			CS(1, {arrcat(FILENAME, "txt/FOOD.txt", 0);})			//<	0
			CS(2, {arrcat(FILENAME, "txt/bath.txt", 0);})			//<	1
			CS(3, {arrcat(FILENAME, "txt/big.txt", 0);})			//<	2
			CS(4, {arrcat(FILENAME, "txt/rude.txt", 0);})			//<	3
			CD:
				arrcat(FILENAME, "txt/mess.txt", 0);				//<	4
		}

		p_dog_stat();
	}

	if (1 && !access(FILENAME, F_OK)) {			//< GET_FILE instead of 1
/////////////////////////////////////////////////////////////////////////
		
		cnt->last_act = 0;
	
		O("%sfile: %s%s\n", CWUL, FILENAME, CNRM);
		type = input_type(FILENAME);
		SW(type) {
			CS(1, { 
				draw(dog, eat);
				cnt_upd(cnt, eat);
				dt->satiety++;
				cnt->satiety = 0; 
				test_cnt[0]++;
				st = 's';
				draw(st, dt->satiety);})
			CS(2, { 
				dt->cleanliness++;
				cnt->cleanliness = 0;
				test_cnt[1]++;
				dt->colour = dt->cleanliness/2;
				st = 'c';
				draw(st, dt->cleanliness);})
			CS(3, {
				draw(dog, read_);
				cnt_upd(cnt, read_);
				dt->intellect++;
				cnt->intellect = 0;
				test_cnt[2]++;
				st = 'i';
				draw(st, dt->intellect);})
			CS(4, { 
				test_cnt[3]++;
				dt->action = sit;
				eat_file();})								//< 	test mode

			CD:
				test_cnt[4]++;
				draw(dog, poop);
				cnt_upd(cnt, poop);
				spit_file("\n\n\n\t\tbad boy\n\n\n\n");
		}
	}

	//<	delte_file(FILENAME);
	

//<	in future this part will get click-event coordinates
//< if it's a dog coors --> act = love
////////////////////////////////////////////////////////////////////////
	/*GET CLICK EVENT*/
	
	/*
	if (click) {
		if (dog_click) {
		cnt->last_act = 0;
		draw(dog, love);
		cnt_upd(cnt, love);	
		}
		else {
			if (kennel_click)
				draw(dog, return_);
		}
	
	}
	*/
////////////////////////////////////////////////////////////////////////

}

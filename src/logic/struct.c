//< C FILENAME[PATH_MAX] ++; 
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include "../cfg.h"
#include "../params.h"
#include "../logic/draw.h"
#include "../file_edit/esfile.h"
#include "../___.h"
#include "../base/mains.h"
#include <unistd.h>
#include <limits.h>

C INPUT_FN[PATH_MAX + 1];

I ITER = 0;

V cnt_upd(tm_cnt cnt_, I act)										//< cnt++ for ex. after action
{
	// O("[cnt_upd()]\n");
	cnt_->last_act += stat_time[act];
	
	if (cnt->last_act > MAX_CNT_LA)
		cnt->last_act = MAX_CNT_LA;
	
	cnt_->satiety += stat_time[act];
	cnt_->intellect += stat_time[act];
	cnt_->cleanliness += stat_time[act];
}

C death()														//<	conditions of exit 	
{    

	if (!dt->satiety || dt->satiety > MAX_ST) {
		dt->action = die;
		if (!dt->satiety) 
			O("your dog died of starvation. stupid\n"); 
		else 
			O("your dog died of gluttony. feckless\n");
		R 1;
	}

	if (dt->intellect >= MAX_IN || dt->cleanliness > MAX_CL) {
		dt->action = rise;
		if (dt->intellect >= MAX_IN) 
			O("he was much smarter than you\n");
		else 
			O("he was as clean as your virginity\n");
		R 1;
	}
/*
	X(!dt->satiety || dt->satiety > MAX_ST, {dt->action = die;}, 1);					//<	dog dies and program aborts if satiety == 0 || satiety > MAX_ST        
	X(dt->intellect >= MAX_IN || dt->cleanliness > MAX_CL, {dt->action = rise;}, 1);			//< dog rises if intellect > MAX_IN || cleanliness > MAX_CL
	*/
	R 0;
}

V cnt_check()													//<	conditions of modifing dt in case of appropriate cnt
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


C set_main_action()								//< set main action if nothing special happens
{
	C act;
	// O("[set_main_action()]\n");
	
	act = dt->action;

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

//< C FILENAME[PATH_MAX] ++;
V event_check()									//< user's commands 
{
	/* GET FILE */

	// S file_input = malloc(SZ(C) * 100);						//< for ex
	I type;
	C r, dog = 'd';
	// O("[event_check()]\n");


	strcpy(INPUT_FN, "123");

	if (cnt->last_act >= MAX_CNT_LA) {
		r = rand()%5;
		SW(r) {
			CS(1, {strcpy(INPUT_FN, "txt/FOOD.txt");})
			CS(2, {strcpy(INPUT_FN, "txt/bath.txt");})
			CS(3, {strcpy(INPUT_FN, "txt/big.txt");})
			CS(4, {strcpy(INPUT_FN, "txt/rude.txt");})
			CD:
				strcpy(INPUT_FN, "txt/mess.txt");
		}

		// strcpy(INPUT_FN, "txt/FOOD.txt");
		p_dog_stat();
	}

	if (1 && !access(INPUT_FN, F_OK)) {			//< GET_FILE instead of 1
		cnt->last_act = 0;
	
		O("file: %s\n", INPUT_FN);
		type = input_type(INPUT_FN);
		SW(type) {
			CS(1, { 
				draw(dog, eat);
				cnt_upd(cnt, eat);
				dt->satiety++;
				cnt->satiety = 0; })
			CS(2, { 
				dt->cleanliness++;
				cnt->cleanliness = 0;
				dt->colour = dt->cleanliness/2;})
			CS(3, {
				draw(dog, read_);
				cnt_upd(cnt, read_);
				dt->intellect++;
				cnt->intellect = 0;})
			CS(4, { 
				dt->action = sit;
				eat_file();})								//< 	test mode

			CD:
				draw(dog, poop);
				cnt_upd(cnt, poop);
				spit_file("\n\n\n\t\tbad boy\n\n\n\n");
		}
	}

	// free(file_input);

	
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
	
	}*/
	// free(str);
	// free(dog);
}

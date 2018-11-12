//< C STAT[4] --; C STAT[4] ++; C FILENAME[PATH_MAX] ++; C LINE[?] ++;
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


V cnt_upd(tm_cnt cnt_, I act)										//< cnt++ for ex. after action
{
	// O("[cnt_upd()]\n");
	cnt_->last_act += stat_time[act];
	cnt_->satiety += stat_time[act];
	cnt_->intellect += stat_time[act];
	cnt_->cleanliness += stat_time[act];
}

C death()														//<	conditions of exit 	
{    
	X(!dt->satiety || dt->satiety > MAX_ST, {dt->action = die;}, 1);							//<	dog dies and program aborts if satiety == 0 || satiety > MAX_ST        
	X(dt->intellect >= MAX_IN || dt->cleanliness > MAX_CL, {dt->action = rise;}, 1);			//< dog rises if intellect > MAX_IN || cleanliness > MAX_CL
	R 0;
}

//<	C STAT[4] --;
V cnt_check()													//<	conditions of modifing dt in case of appropriate cnt
{
	S state = malloc(SZ(C) * 3);
	// O("[cnt_check()]\n");
	if (cnt->satiety >= MAX_CNT_ST) {								//<	check for satiety
		cnt->satiety = 0;
		strcpy(state, "st");
		draw(state, --dt->satiety);
	}

	if (cnt->intellect >= MAX_CNT_IN) {								//<	check for intellect
		cnt->intellect = 0;
		dt->intellect = dt->intellect ? --dt->intellect : dt->intellect;
		strcpy(state, "in");
		draw(state, dt->intellect);
	}

	if (cnt->cleanliness >= MAX_CNT_CL) {							//< check for cleanliness 
		cnt->cleanliness = 0;
		dt->cleanliness = dt->cleanliness ? --dt->cleanliness : dt->cleanliness;
		strcpy(state, "cl");
		draw(state, dt->cleanliness);
		dt->colour = dt->cleanliness/2;
	}
	free(state);
}


C set_main_action()								//< set main action if nothing special happens
{
	C act;
	// O("[set_main_action()]\n");
	
	act = dt->action;

	X((cnt->last_act < MAX_CNT_LA), {
		dt->action = 	(dt->satiety > STLIM && dt->cleanliness > CLLIM) 	? run 	: 
						(dt->satiety > STLIM && dt->cleanliness <= CLLIM)	? walk	: sit;}, 0);
	dt->action = ((dt->satiety <= STLIM) || (dt->cleanliness <= CLLIM)) ? sleep_1 : sleep_2;
	cnt->last_act = MAX_CNT_LA;
	
	if (act != dt->action) {
		O("\n%s%s%s to %s%s%s\n", CBLU, stat_name[act], CNRM, CRED,stat_name[dt->action], CNRM);
		p_dog_stat();
	}
}

//< C STAT[4] ++; C FILENAME[PATH_MAX] ++; C LINE[?] ++;
V event_check()									//< user's commands 
{
	/* GET FILE */

	S file_input = malloc(SZ(C) * 100), dog = malloc(SZ(C) * 4), str = malloc(SZ(C) * 40);						//< for ex
	I type;
	C r;
	// O("[event_check()]\n");


	strcpy(file_input, "123");
	strcpy(dog, "dog");
	strcpy(str, "\n\n\n\t\tbad boy\n\n\n\n");
	if (cnt->last_act == MAX_CNT_LA) {
		r = rand()%5;
		SW(r) {
			CS(1, {strcpy(file_input, "txt/FOOD.txt");})
			CS(2, {strcpy(file_input, "txt/bath.txt");})
			CS(3, {strcpy(file_input, "txt/big.txt");})
			CS(4, {strcpy(file_input, "txt/rude.txt");})
			CD:
				strcpy(file_input, "txt/mess.txt");

		}

		// strcpy(file_input, "txt/FOOD.txt");
		p_dog_stat();
	}

	if (1 && !access(file_input, F_OK)) {			//< GET_FILE instead of 1
		cnt->last_act = 0;
	
		O("file: %s\n", file_input);
		type = input_type(file_input);
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
				spit_file(str);
		}
	}

	free(file_input);

	
	/*GET CLICK EVENT*/
/*
	if (click) {
		if (dog_click) {
		cnt->last_act = 0;
		draw("dog", love);
		cnt_upd(cnt, love);	
		}
		else {
			if (kennel_click)
				draw("dog", return_);
		}
	
	}*/
	free(str);
	free(dog);
}

#include "../cfg.h"
#include "../params.h"
#include "../logic/draw.h"
#include "../file_edit/esfile.h"
#include "../___.h"
#include "../base/mains.h"
#include <unistd.h>


V cnt_upd(tm_cnt cnt_, I act)										//< cnt++ for ex. after action
{
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

V cnt_check()										//<	conditions of modifing dt in case of appropriate cnt
{
	if (cnt->satiety >= MAX_CNT_ST) {								//<	check for satiety
		cnt->satiety = 0;
		draw("st", --dt->satiety);
	}

	if (cnt->intellect >= MAX_CNT_IN) {								//<	check for intellect
		cnt->intellect = 0;
		dt->intellect = dt->intellect ? --dt->intellect : dt->intellect;
		draw("in", dt->intellect);
	}

	if (cnt->cleanliness >= MAX_CNT_CL) {							//< check for cleanliness 
		cnt->cleanliness = 0;
		dt->cleanliness = dt->cleanliness ? --dt->cleanliness : dt->cleanliness;
		draw("cl", dt->cleanliness);
		dt->colour = dt->cleanliness/2;
	}
}


C set_main_action()								//< set main action if nothing special happens
{
	X((cnt->last_act < MAX_CNT_LA), {
		dt->action = 	(dt->satiety > STLIM && dt->cleanliness > CLLIM) 	? run 	: 
						(dt->satiety > STLIM && dt->cleanliness <= CLLIM)	? walk	: sit;}, 0);
	dt->action = (dt->satiety <= STLIM || dt->cleanliness <= CLLIM) ? sleep_2 : sleep_1;
	cnt->last_act = MAX_CNT_LA;
}


V event_check()									//< user's commands 
{
	/* GET FILE */

	S file_input = "filename";						//< for ex

	if (1 && !access(file_input, F_OK)) {			//< GET_FILE instead of 1
		cnt->last_act = 0;
	
		SW(input_type(file_input)) {
			CS(1, { 
				draw("dog", eat);
				cnt_upd(cnt, eat);
				dt->satiety++;
				cnt->satiety = 0; })
			CS(2, { 
				dt->cleanliness++;
				cnt->cleanliness = 0;
				dt->colour = dt->cleanliness/2;})
			CS(3, {
				draw("dog", read_);
				cnt_upd(cnt, read_);
				dt->intellect++;
				cnt->intellect = 0;})
			CS(4, { 
				dt->action = sit;
				// eat_file();								//< 	test mode
				O("eat_file\n");})
			CD:
				draw("dog", poop);
				cnt_upd(cnt, poop);
				spit_file("\n\n\n\t\tbad boy\n\n\n\n");
		}
	}
	
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

}

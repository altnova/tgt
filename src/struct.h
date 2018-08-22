// #include "___.h"
#include <stdio.h>
#include <stdlib.h>
// #include "cfg.h"


ext V cnt_upd(counter cnt_tm, I num);									//< cnt++ for ex. after action

ext V cnt_check(counter cnt_tm, dat dt);								//<	conditions of modifing dt in case of appropriate  cnt

ext C death(dat dt);													//<	conditions of exit 	

// ext V event_check(counter cnt, dat dt);									//< user's commands 

ext C set_main_action(counter cnt, dat dt);								//< set main action if nothing special happens
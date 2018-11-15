// #include "base/cfg.h"

ext V cnt_upd(tm_cnt cnt_, I num);									//< cnt++ for ex. after action

ext V cnt_check();										//<	conditions of modifing dt in case of appropriate  cnt

ext C death();											//<	conditions of exit 	

ext V event_check();									//< user's commands 

ext C set_main_action();								//< set main action if nothing special happens

ext I ITER;

ext I MAIN_IT;

ext I test_cnt[];
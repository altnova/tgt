#include "cfg.h"
#include "___.h"

ext tm_cnt cnt;
ext dat dt;
ext coor crd;

V set_start()
{
	pDat dt_main = {5, 5, 5, 2, 9};
	pCounter cnt_main = {0, 0, 0, 0};


	dt = &dt_main;
	cnt = &cnt_main;

}
#include <stdio.h>
#include "../___.h"
#include "../png/canvas.h"


V depict(I am, S *filename, UH *x_, UH *y_)										//<!!! 	GTK+
{
	O("\tDEPICT [%s]\n", filename[0]);
	frame(am, filename, x_, y_);
}
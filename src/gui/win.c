//<	set gui
#include <stdio.h>

#include "../cfg/cfg.h"

#include "../png/canvas.h"


V depict(I am, S *filename, UH *x_, UH *y_)										//<!!! 	GTK+
{
	// O("\tDEPICT [%s] at %dx%d\n", filename[0], x_[0], y_[0]);
	frame(am, filename, x_, y_);									//< for tests!!!!
}

V set_win()
{
	/* make transparent (click/view) window fullscreen	*/

	/* draw png on it	*/
}

I height_()
{
	height = 300;
	R height;
}

I width_()
{
	width = 800;
	R width;
}
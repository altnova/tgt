//<	set gui
#include <stdio.h>

#include "../cfg/cfg.h"

#include "../png/canvas.h"

//<     *   *  *             * * *             *  *   *     >//
//<        depict(I am, S *filename, UH *x_, UH *y_)        >//
//<     *   *  *             * * *             *  *   *     >//
//<         send call to some c++ functions to set          >//
//<      each filename[i] image at x_[i] y_[i] in tmp.png   >//
//<     and show it in the window; am is amount of images   >//
//<     *   *  *             * * *             *  *   *     >//
V depict(I am, S *filename, UH *x_, UH *y_)									
{
	// O("\tDEPICT [%s] at %dx%d\n", filename[0], x_[0], y_[0]);
	frame(am, filename, x_, y_);									//< for tests!!!!
}

//<	may be unnecessary
V set_win()
{
	/* make transparent (click/view) window fullscreen	*/

	/* draw png on it	*/
}

//<     *   *  *             * * *             *  *   *     >//
//<                      height_()                          >//
//<     *   *  *             * * *             *  *   *     >//
//<    get screen height and keep it in global var height   >//
//<     *   *  *             * * *             *  *   *     >//
//<                 return screen height                    >//
//<     *   *  *             * * *             *  *   *     >//
I height_()
{
	height = 300;
	R height;
}

//<     *   *  *             * * *             *  *   *     >//
//<                      width_()                           >//
//<     *   *  *             * * *             *  *   *     >//
//<    get screen width and keep it in global var width     >//
//<     *   *  *             * * *             *  *   *     >//
//<                 return screen width                     >//
//<     *   *  *             * * *             *  *   *     >//
I width_()
{
	width = 800;
	R width;
}
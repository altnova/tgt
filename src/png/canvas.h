//<	compile .png for visualization

//<     *   *  *             * * *             *  *   *     >//
//<     add_to_canvas(I am, S* filename, UH* x_, UH* y_)    >//
//<     *   *  *             * * *             *  *   *     >//
//<     update CANVAS and canvas.png                        >//
//<     mount into canvas.png and CANVAS filename[i] at     >//
//<                 x_[i] and y_[i]                         >//
//<             am is number of filenames                   >//
//<     *   *  *             * * *             *  *   *     >//
ext void add_to_canvas(I am, S* filename, UH* x_, UH* y_);		

//<     *   *  *             * * *             *  *   *     >//
//<         frame(I am, S* filename, UH* x_, UH* y_)        >//
//<     *   *  *             * * *             *  *   *     >//
//<   create pic/tmp.png which is canvas.png with mounted   >//
//<            filename[i] pic at x_[i] y_[i]               >//
//<               am is amount of filename                  >//
//<     *   *  *             * * *             *  *   *     >//
ext void frame(I am, S* filename, UH* x_, UH* y_);	

//<     *   *  *             * * *             *  *   *     >//
//<                      set_canvas()                       >//
//<     *   *  *             * * *             *  *   *     >//
//<     set canvas as CANVAS with basic elements            >//
//<     pic/canvas.png created for insurance                >//
//<     *   *  *             * * *             *  *   *     >//	
ext void set_canvas();

//<     *   *  *             * * *             *  *   *     >//
//<                      end_canvas()                       >//
//<     *   *  *             * * *             *  *   *     >//
//<     free al allocated memory used to produce png img    >//
//<     *   *  *             * * *             *  *   *     >//
ext void end_canvas();
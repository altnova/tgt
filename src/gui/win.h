//<	set gui

//<     *   *  *             * * *             *  *   *     >//
//<        depict(I am, S *filename, UH *x_, UH *y_)        >//
//<     *   *  *             * * *             *  *   *     >//
//<         send call to some c++ functions to set          >//
//<      each filename[i] image at x_[i] y_[i] in tmp.png   >//
//<     and show it in the window; am is amount of images   >//
//<     *   *  *             * * *             *  *   *     >//
ext V depict(I am, S *filename, UH *x, UH *y);								

//<	may be unnecessary
ext V set_win();

//<     *   *  *             * * *             *  *   *     >//
//<                      height_()                          >//
//<     *   *  *             * * *             *  *   *     >//
//<    get screen height and keep it in global var height   >//
//<     *   *  *             * * *             *  *   *     >//
//<                 return screen height                    >//
//<     *   *  *             * * *             *  *   *     >//
ext I height_();

//<     *   *  *             * * *             *  *   *     >//
//<                      width_()                           >//
//<     *   *  *             * * *             *  *   *     >//
//<    get screen width and keep it in global var width     >//
//<     *   *  *             * * *             *  *   *     >//
//<                 return screen width                     >//
//<     *   *  *             * * *             *  *   *     >//
ext I width_();

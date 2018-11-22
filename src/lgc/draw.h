//<	depict board params or dog stat

//<     *   *  *             * * *             *  *   *     >//
//<                   draw(C key, I obj)                    >//
//<     *   *  *             * * *             *  *   *     >//
//<   function to choose which .png file change is needed   >//
//<             [tmp.png or canvas.png]                     >//
//< dependent on key which could be 'd' (change tmp.png)    >//
//<                                 's' (canvas.png sat)    >//
//<                                 'i' (canvas.png int)    >//
//<                                 'c' (canvas.png cle)    >//
//<     obj could be dog action enum number or              >//
//<             new value of dog param key                  >//
//<     *   *  *             * * *             *  *   *     >//
ext V draw(C key, int obj);
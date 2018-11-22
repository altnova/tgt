//<	basic file functions

//<     *   *  *             * * *             *  *   *     >//
//<                 input_type(S filename)                  >//
//<     *   *  *             * * *             *  *   *     >//
//<     opens filename and calculates filename's type       >//
//<     *   *  *             * * *             *  *   *     >//
//<     return:                                             >//
//<             0 -- file doesn't exist || size of file is 	>//
//<                     larger than 2 Mbytes || file        >//
//<                     doesn't constain any of key words   >//
//<             1 -- file contains food words               >//
//<             2 -- file contains cleaning words           >//
//<             3 -- file size is larger than 3 Kbytes      >//
//<                     and less than 2 Mbytes              >//
//<             4 -- file contains rude words               >//
//<     *   *  *             * * *             *  *   *     >//
ext C input_type(S filename);									
 
//<     *   *  *             * * *             *  *   *     >//
//<             subcheck_d(S path, S sub, I len)            >//
//<     *   *  *             * * *             *  *   *     >//
//<         specialized fdn() with the same arguments       >//
//<     but displays messages depending on the fdn() r val  >//
//<     *   *  *             * * *             *  *   *     >//
//<     return:                                             >//
//<             0 -- file or doesn't exist                  >//
//<             1 -- if directory                           >//
//<     *   *  *             * * *             *  *   *     >//
ext C subcheck_d(S path, S sub, I len);

//<     *   *  *             * * *             *  *   *     >//
//<                 is_tgt(S path)                          >//
//<     *   *  *             * * *             *  *   *     >//
//<         check for right subdirectories for tgt          >//
//<     *   *  *             * * *             *  *   *     >//
//<         if success return 1, else 0                     >//
//<     *   *  *             * * *             *  *   *     >//	
ext C is_tgt(S path);

//<     *   *  *             * * *             *  *   *     >//
//<                 is_home(S path)                         >//
//<     *   *  *             * * *             *  *   *     >//
//<         check for right subdirectories for home         >//
//<     *   *  *             * * *             *  *   *     >//
//<         if success return 1, else 0                     >//
//<     *   *  *             * * *             *  *   *     >//	
ext C is_home(S path);


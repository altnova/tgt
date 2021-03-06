//<	main functions for everything

//<     *   *  *             * * *             *  *   *     >//
//<                 case_cmp(C letter, C c)                 >//
//<     *   *  *             * * *             *  *   *     >//
//<         compares letter and c and ignores case          >//
//<     *   *  *             * * *             *  *   *     >//
//<     return 1 if letter == c [ignores case!] else : 0    >//
//<     *   *  *             * * *             *  *   *     >//
ext C case_cmp(C letter, C c);

//<     *   *  *             * * *             *  *   *     >//
//<                 FCLR(FILE *ptr, C r)                    >//
//<     *   *  *             * * *             *  *   *     >//
//<             close file pth and return   r               >//
//<     *   *  *             * * *             *  *   *     >//
//<                     return r                            >//
//<     *   *  *             * * *             *  *   *     >//
ext C FCLR(FILE *ptr, C r);

//<     *   *  *             * * *             *  *   *     >//
//<        arrcat(S buf, S line, I ptr, I buf_sz)           >//
//<     *   *  *             * * *             *  *   *     >//
//<         concatenates buf with line from	buf[ptr]        >//
//<             buf_sz is allocated buf size                >//
//<     *   *  *             * * *             *  *   *     >//
V arrcat(S buf, S line, I ptr, I buf_sz);

//<     *   *  *             * * *             *  *   *     >//
//<                 carrzero(S buf, I len)                  >//
//<     *   *  *             * * *             *  *   *     >//
//<     sets zero for each element less than buf[len]       >//
//<                     of char array                       >//
//<     *   *  *             * * *             *  *   *     >//
ext V carrzero(S buf, I len);

//<     *   *  *             * * *             *  *   *     >//
//<					iarrzero(I* buf, I len)					>//
//<     *   *  *             * * *             *  *   *     >//
//<			sets zero for each element less than buf[lem] 	>//
//<						of int array 						>//	
//<     *   *  *             * * *             *  *   *     >//
ext V iarrzero(I* buf, I len);

//<     *   *  *             * * *             *  *   *     >//
//<                 szfile(FILE *ptr)                       >//
//<     *   *  *             * * *             *  *   *     >//
//<                 size of ptr file                        >//
//<     *   *  *             * * *             *  *   *     >//
//<                 return size (UJ)                        >//
//<     *   *  *             * * *             *  *   *     >//
ext UJ szfile(FILE *ptr);

//<     *   *  *             * * *             *  *   *     >//
//< in_range(I obj_1_x, I obj_1_y, I obj_2_x, I obj_2_y)    >//
//<     *   *  *             * * *             *  *   *     >//
//<     checks for if obj_2 is in 2D RANGE of obj_1         >//
//<     *   *  *             * * *             *  *   *     >//
//<     return 1 if obj_2 is in 2D RANGE of obj_1, else 0   >//
//<     *   *  *             * * *             *  *   *     >//
ext C in_range(I obj_1_x, I obj_1_y, I obj_2_x, I obj_2_y);

//<     *   *  *             * * *             *  *   *     >//
//<                dec_digits(UJ num)                       >//
//<     *   *  *             * * *             *  *   *     >//
//<         calculate number of decimal digits of num       >//
//<     *   *  *             * * *             *  *   *     >//
//<             return amount of digits                     >//
//<     *   *  *             * * *             *  *   *     >//
ext I dec_digits(UJ num);

//<     *   *  *             * * *             *  *   *     >//
//<                 pow_(I basis, I exp_)                   >//
//<     *   *  *             * * *             *  *   *     >//
//<                 my integer pow                          >//
//<     *   *  *             * * *             *  *   *     >//
//<                 return basis^exp_                       >//
//<     *   *  *             * * *             *  *   *     >//
ext UJ pow_(I basis, I exp_);

//<     *   *  *             * * *             *  *   *     >//
//<                      itoa(I n)                          >//
//<     *   *  *             * * *             *  *   *     >//
//<     n to acsii like n == 128 --> NUM_INT == "128\0"     >//
//<     *   *  *             * * *             *  *   *     >//
//<                      return NUM_INT                     >//
//<     *   *  *             * * *             *  *   *     >//
ext S itoa(I num);

//<     *   *  *             * * *             *  *   *     >//
//<                 colour(S name, I col)                   >//
//<     *   *  *             * * *             *  *   *     >//
//<         for ex. name == "dir/file.txt" -->              >//
//<         -->	FILENAME == "dir/n/file.txt"                >//
//<                where n == '0' + col                     >//
//<     *   *  *             * * *             *  *   *     >//
//<                    return FILENAME                      >//
//<     *   *  *             * * *             *  *   *     >//
ext S colour(S name, I col);

//<     *   *  *             * * *             *  *   *     >//
//<               fopen_(S str1, S str2)                    >//
//<     *   *  *             * * *             *  *   *     >//
//<     standart fopen but str1 is concatenated with        >//
//<             TGT_HOME fopen mode is str2                 >//
//<     *   *  *             * * *             *  *   *     >//
//<     returns FILE pointer of concatenated TGT_HOME+str1  >//
//<     *   *  *             * * *             *  *   *     >//
ext FILE* fopen_(S str1, S str2);

//<     *   *  *             * * *             *  *   *     >//
//<                    p_dog_stat()                         >//
//<     *   *  *             * * *             *  *   *     >//
//<           print formatted dt && cnt structs             >//
//<     *   *  *             * * *             *  *   *     >//
ext V p_dog_stat();

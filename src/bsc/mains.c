//<	main functions for everything
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <limits.h>
#include <errno.h>

#include <pwd.h>
#include <sys/types.h>
#include <dirent.h>

#include "../cfg/cfg.h"

//<     *   *  *             * * *             *  *   *     >//
//<        arrcat(S buf, S line, I ptr, I buf_sz)           >//
//<     *   *  *             * * *             *  *   *     >//
//<         concatenates buf with line from	buf[ptr]        >//
//<             buf_sz is allocated buf size                >//
//<     *   *  *             * * *             *  *   *     >//
V arrcat(S buf, S line, I ptr, I buf_sz)			
{
	scpy(buf + (ptr * SZ(C)), line, buf_sz - (ptr * SZ(C)));
}

//<     *   *  *             * * *             *  *   *     >//
//<                 carrzero(S buf, I len)                  >//
//<     *   *  *             * * *             *  *   *     >//
//<     sets zero for each element less than buf[len]       >//
//<                     of char array                       >//
//<     *   *  *             * * *             *  *   *     >//
V carrzero(S buf, I len)				
{
	I i;
	for (i = 0; i < len; i++)
		buf[i] = 0;
}

//<     *   *  *             * * *             *  *   *     >//
//<					iarrzero(I* buf, I len)					>//
//<     *   *  *             * * *             *  *   *     >//
//<			sets zero for each element less than buf[lem] 	>//
//<						of int array 						>//	
//<     *   *  *             * * *             *  *   *     >//
V iarrzero(I* buf, I len)									
{
	I i;
	for (i = 0; i < len; i++)
		buf[i] = 0;
}

//<     *   *  *             * * *             *  *   *     >//
//<               fopen_(S str1, S str2)                    >//
//<     *   *  *             * * *             *  *   *     >//
//<     standart fopen but str1 is concatenated with        >//
//<             TGT_HOME fopen mode is str2                 >//
//<     *   *  *             * * *             *  *   *     >//
//<     returns FILE pointer of concatenated TGT_HOME+str1  >//
//<     *   *  *             * * *             *  *   *     >//
FILE* fopen_(S str1, S str2)								
{
	FILE *ptr;
	I len;
	C file[PATH_MAX + 1];
	S home = getenv("TGT_HOME");

	strcpy(file, home);
	len = strlen(home);
	file[len] = '/';
	file[++len] = 0;
	strcat(file, str1);
	// O("FILENAME: '%s'\n", file);
	ptr = fopen(file, str2);
	R ptr;
}

//<     *   *  *             * * *             *  *   *     >//
//<                 FCLR(FILE *ptr, C r)                    >//
//<     *   *  *             * * *             *  *   *     >//
//<             close file ptr and return   r               >//
//<     *   *  *             * * *             *  *   *     >//
//<                     return r                            >//
//<     *   *  *             * * *             *  *   *     >//
C FCLR(FILE *ptr, C r)											
{
	fclose(ptr);
	R r;
}

//<     *   *  *             * * *             *  *   *     >//
//<                 szfile(FILE *ptr)                       >//
//<     *   *  *             * * *             *  *   *     >//
//<                 size of ptr file                        >//
//<     *   *  *             * * *             *  *   *     >//
//<                 return size (UJ)                        >//
//<     *   *  *             * * *             *  *   *     >//
UJ szfile(FILE *ptr)	
{
	UJ cur, size;
	if (ptr == NULL)
		R 0;
	cur = ftell(ptr);
	fseek(ptr, 0, SEEK_END);

	size = ftell(ptr);
	fseek(ptr, cur, SEEK_SET);
	R size;
}

//<     *   *  *             * * *             *  *   *     >//
//<                 case_cmp(C letter, C c)                 >//
//<     *   *  *             * * *             *  *   *     >//
//<         compares letter and c and ignores case          >//
//<     *   *  *             * * *             *  *   *     >//
//<     return 1 if letter == c [ignores case!] else : 0    >//
//<     *   *  *             * * *             *  *   *     >//
C case_cmp(C c_1, C c_2)		
{
	R (c_1 == c_2 	|| (IN('A', c_1, 'Z') && c_2 == c_1 + ' ') 
					|| (IN('a', c_1, 'z') && c_2 == c_1 - ' ')) ? 1 : 0;
}

//<     *   *  *             * * *             *  *   *     >//
//< in_range(I obj_1_x, I obj_1_y, I obj_2_x, I obj_2_y)    >//
//<     *   *  *             * * *             *  *   *     >//
//<     checks for if obj_2 is in 2D RANGE of obj_1         >//
//<     *   *  *             * * *             *  *   *     >//
//<     return 1 if obj_2 is in 2D RANGE of obj_1, else 0   >//
//<     *   *  *             * * *             *  *   *     >//
C in_range(I obj_1_x, I obj_1_y, I obj_2_x, I obj_2_y)			
{
	R (	IN(obj_1_x - RANGE, obj_2_x, obj_1_x + RANGE) && 
		IN(obj_1_y - RANGE, obj_2_y, obj_1_y + RANGE)) ? 1 : 0;
}

//<     *   *  *             * * *             *  *   *     >//
//<                dec_digits(UJ num)                       >//
//<     *   *  *             * * *             *  *   *     >//
//<         calculate number of decimal digits of num       >//
//<     *   *  *             * * *             *  *   *     >//
//<             return amount of digits                     >//
//<     *   *  *             * * *             *  *   *     >//
I dec_digits(UJ num)									
{
	I i;
	X(num, {for (i = 0; num; num/= 10, i++);}, i);
	R1;
}

//<     *   *  *             * * *             *  *   *     >//
//<                 pow_(I basis, I exp_)                   >//
//<     *   *  *             * * *             *  *   *     >//
//<                 my integer pow                          >//
//<     *   *  *             * * *             *  *   *     >//
//<                 return basis^exp_                       >//
//<     *   *  *             * * *             *  *   *     >//
UJ pow_(I basis, I exp_) 											//<	my integer pow_
{
	I i;
	UJ result = 1;
	X(exp_, {for (i = 0; i < exp_; i++) 
					result *= basis;}, result);
	R1;
}

//<     *   *  *             * * *             *  *   *     >//
//<                     reverse(S s)                        >//
//<     *   *  *             * * *             *  *   *     >//
//<     reverses s like if s == "abc\0" --> s == "cba\0"    >//
//<     *   *  *             * * *             *  *   *     >//
V reverse(S s)														
{
	I i, j;
	C c;
	for (i = 0, j = scnt(s) - 1; i < j; i++, j--) {
		c = s[i];
		s[i] = s[j];
		s[j] = c;
	}
}

//<     *   *  *             * * *             *  *   *     >//
//<                      itoa(I n)                          >//
//<     *   *  *             * * *             *  *   *     >//
//<     n to acsii like n == 128 --> NUM_INT == "128\0"     >//
//<     *   *  *             * * *             *  *   *     >//
//<                      return NUM_INT                     >//
//<     *   *  *             * * *             *  *   *     >//
S itoa(I n)		
{
	I i;
	NUM_INT[0] = n % 10 + '0';
	for(i = 1;(n/=10) > 0;i++) 
		NUM_INT[i] = n % 10 + '0';
	
	NUM_INT[i] = '\0';
	reverse(NUM_INT);
}

//<     *   *  *             * * *             *  *   *     >//
//<                 colour(S name, I col)                   >//
//<     *   *  *             * * *             *  *   *     >//
//<         for ex. name == "dir/file.txt" -->              >//
//<         -->	FILENAME == "dir/n/file.txt"                >//
//<                where n == '0' + col                     >//
//<     *   *  *             * * *             *  *   *     >//
//<                    return FILENAME                      >//
//<     *   *  *             * * *             *  *   *     >//
S colour(S name, I col)	
{
	I len = scnt(name), i;
	I len_2 = len + 2;
	C new_name[PATH_MAX + 1];

	arrcat(new_name, name, 0, PATH_MAX+1);

	OMO({i = 0;}, 	(name[len - i] != '/' && i <= len), 
					{new_name[len_2 - i] = name[len - i];i++;});  	//<	must be /abc/s/some.png

	new_name[len_2 - i] = '0';										//< set 0 for a while
	//<	new_name[len_2 - i] = col%10 + '0';

	arrcat(FILENAME, new_name, 0, LINE_MAX_);

	R FILENAME;
}

//<     *   *  *             * * *             *  *   *     >//
//<                    p_dog_stat()                         >//
//<     *   *  *             * * *             *  *   *     >//
//<           print formatted dt && cnt structs             >//
//<     *   *  *             * * *             *  *   *     >//
V p_dog_stat()
{
	O("\n\tACT: %s\t\tSAT: %d\t", stat_name[dt->action], dt->satiety);
	O("INT: %d\tCLE: %d\tCOL: %d\n", dt->intellect, dt->cleanliness, dt->colour);

	O("\n\tTIMERS\n\tlast act: %d   [%d s] \t", cnt->last_act, cnt->last_act/1000);
	O("(max %d[%d sec]) \n", MAX_CNT_LA, MAX_CNT_LA/1000);
	O("\tintellect: %d   [%d s] \t", cnt->intellect, cnt->intellect/1000);
	O("(max %d[%d sec])\n", MAX_CNT_IN, MAX_CNT_IN/1000);

	O("\tcleanliness: %d   [%d s] \t", cnt->cleanliness, cnt->cleanliness/1000);
	O("(max %d[%d sec])\n", MAX_CNT_CL, MAX_CNT_CL/1000);
	O("\tsatiety: %d   [%d s] \t", cnt->satiety, cnt->satiety/1000);
	O("(max %d[%d sec])\n\n", MAX_CNT_ST, MAX_CNT_ST/1000);
}


/*
C last_c(S line, S needle, I len)									//< cmp line ending and needle							
{
	I n_len = strlen(needle);
	I i = n_len - 1, j;

	for (j = len - 1, i = n_len - 1; i >= 0; j--, i--) {
			if (line[j] != needle[i]) 
				R 0;
	}

	R 1;
}

C first_c(S line, S needle, I len)									//<	cmp line beggining and needle
{
	I n_len = strlen(needle), i;

	for (i = 0; needle[i] && i < n_len && i < len; i++) {
		if (line[i] != needle[i]) {
			R 0;
		}
	}
	if (i == len)
		R 0;

	R 1;
}

*/
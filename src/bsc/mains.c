#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <limits.h>
#include <errno.h>

#include <pwd.h>
#include <sys/types.h>
#include <dirent.h>

#include "../cfg/cfg.h"

V arrcat(S buf, S line, I ptr)										//<	strcat for global arrays
{
	I i, j = 0;

	for (i = ptr; line[j]; i++){
		buf[i] = line[j++];
	}
	buf[i] = 0;
}

I arrlen(S str)  													//<	global array len
{
	I i;
	for (i = 0; str[i]; i++);
	R i;
}

V carrzero(S buf, I len)											//<	char global array set all as zero
{
	I i;
	for (i = 0; i < len; i++)
		buf[i] = 0;
}

V iarrzero(I* buf, I len)											//<	int global array det all as zero
{
	I i;
	for (i = 0; i < len; i++)
		buf[i] = 0;
}

FILE* fopen_(S str1, S str2)										//<	fopen with concatenating env var path to directory
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

C FCLR(FILE *ptr, C r)												//< close file and return r
{
	fclose(ptr);
	R r;
}

UJ szfile(FILE *ptr)												//< sizeof file
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

C case_cmp(C letter, C c)											//<	case unsensetive char compare 	
{
	R (letter == c || (IN('A', letter, 'Z') && c == letter + ' ') || (IN('a', letter, 'z') && c == letter - ' ')) ? 1 : 0;
}

C in_range(I obj_1_x, I obj_1_y, I obj_2_x, I obj_2_y)				//< is obj_2 in range of obj_1?
{
	R (IN(obj_1_x - RANGE, obj_2_x, obj_1_x + RANGE) && IN(obj_1_y - RANGE, obj_2_y, obj_1_y + RANGE)) ? 1 : 0;
}

I dec_digits(UJ num)												//<	decimal digits of num
{
	I i;
	X(num, {for (i = 0; num; num/= 10, i++);}, i);
	R1;
}

UJ pow_(I basis, I exp_) 											//<	my intteger pow_
{
	I i;
	UJ result = 1;
	X(exp_, {for (i = 0; i < exp_; i++) result *= basis;}, result);
	R1;
}

V reverse(S s)														//< reverse string
{
	I i, j;
	C c;
	for (i = 0, j = arrlen(s) - 1; i < j; i++, j--) {
		c = s[i];
		s[i] = s[j];
		s[j] = c;
	}
}

S itoa(I n)															//< integer to ascii
{
	I i, max;
	NUM_INT[0] = n % 10 + '0';
	for(i = 1;(n/=10) > 0;i++) 
		NUM_INT[i] = n % 10 + '0';
	
	NUM_INT[i] = '\0';
	reverse(NUM_INT);
}

S colour(S name, I col)												//< 	dir/filename --> dir/n/filename, where n is colour num
{
	I len = arrlen(name), i;
	I len_2 = len + 2;
	C new_name[2000];

	arrcat(new_name, name, 0);

	OMO({i = 0;}, (name[len - i] != '/'), {new_name[len_2 - i] = name[len - i];i++;});  	//<	must be /abc/s/some.png

	new_name[len_2 - i] = '0';																//< set 0 for a while
	//<	new_name[len_2 - i] = col + '0';

	arrcat(FILENAME, new_name, 0);

	R FILENAME;
}

V p_dog_stat()
{
	O("\n\tACT: %s\t\tSAT: %d\tINT: %d\tCLE: %d\tCOL: %d\n", stat_name[dt->action], dt->satiety, dt->intellect, dt->cleanliness, dt->colour);
	O("\n\tTIMERS\n\tlast act: %d   [%d s] \t(max %d[%d sec]) \n\tintellect: %d   [%d s] \t(max %d[%d sec])\n", cnt->last_act, cnt->last_act/1000, MAX_CNT_LA, MAX_CNT_LA/1000, cnt->intellect, cnt->intellect/1000, MAX_CNT_IN, MAX_CNT_IN/1000);
	O("\tcleanliness: %d   [%d s] \t(max %d[%d sec])\n\tsatiety: %d   [%d s] \t(max %d[%d sec])\n\n", cnt->cleanliness, cnt->cleanliness/1000, MAX_CNT_CL, MAX_CNT_CL/1000, cnt->satiety, cnt->satiety/1000, MAX_CNT_ST, MAX_CNT_ST/1000);
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
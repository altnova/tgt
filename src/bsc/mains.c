//<	3 C FILENAME[PATH_MAX] --; C NEW_NAME[?] ++; C NUM[12] ++; I LEN[am] --; I STATE[am] --;

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <limits.h>
#include <errno.h>
#include "../cfg/cfg.h"


static C needle[4][PATH_MAX/2];
static S addr_needle[4] = {needle[0], needle[1], needle[2], needle[3]};
static S* addr_main[1] = {addr_needle};
// static S* addr_needle = &addr_needle;



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
	for (i = 0; str[i]; i++){
		// O("'%c' --> %d\n", str[i], i);
	}
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
/*
V free_array(S *arr, I am) 	
{
	for (I i = 0; i < am; i++)
		free(arr[i]);
	free(arr);
}
*/
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
	O("FILENAME: '%s'\n", file);
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

C file_cont(FILE *ptr, S* string, I am)								//<	~grep		
{
	C buf[2000];
	I i, j, a = 0, szbuf, b;
	C c;
	I length[100], state[100];

	if (am > 100) {
		O("too much strings for search; amount --> 100\n");
		am == 100;
	}

	for (i = 0; i < am; i++) {
		length[i] = arrlen(string[i]);
		a = MAX(a, length[i]);
	}
	a++;

	if (a > 2000) 
		printf("some of the strings are too long\n");

	szbuf = 2000;
	b = szbuf;

	iarrzero(state, 100);

	W (b == szbuf) {
		b = fread(buf, SZ(C), szbuf, ptr);
		for (i = 0; i < b; i++) {						//<	for each char from buf
			for (j = 0; j < am; j++) {						//<	for each needle
				c = case_cmp(buf[i], string[j][state[j]]);
				state[j] = (c)	? state[j] + 1 	:	0; 
				if (state[j] == length[j])
					R 1;
			}
		}
	}

	rewind(ptr);
	R 0;
}

C input_type(S filename)										//<	figures out input type: 1, 2, 3, 4 or 0
{
	FILE *ptr = fopen_(filename, "r");
	I i, size;

	if (!ptr) {
		R 0;
	}

	//<	0 --> input file is too large or nothing clear inside
	//<	1 --> input file food
	//<	2 --> input file clean
	//<	3 --> input file reading
	//<	4 --> input file rude


	size = szfile(ptr);

	X(size>3000, 	{fclose(ptr); O("3\n");},3);				
	X(size>2000000, {fclose(ptr); O("0\n");},0);

	arrcat(needle[0], "asshole", 0);
	arrcat(needle[1], "bitch", 0);
	arrcat(needle[2], "pidor", 0);

	// O("%u: 	addr of n[0]\n%u: 	addr of n[1]\n%u: 	addr of n[2]\n", &needle[0], &needle[1], &needle[2]);


	if (file_cont(ptr, addr_main[0], 3)) 
		R FCLR(ptr, 4);

	arrcat(needle[0], "bone", 0);
	arrcat(needle[1], "food", 0);

	if (file_cont(ptr, addr_main[0], 2)) 
		R FCLR(ptr, 1);

	arrcat(needle[0], "bath", 0);
	arrcat(needle[1], "water", 0);
	arrcat(needle[2], "shower", 0);

	if (file_cont(ptr, addr_main[0], 3)) 
		R FCLR(ptr, 2);

	R FCLR(ptr, 0);
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

//< C NUM[12] ++
S itoa(I n)															//< integer to ascii
{
	I i, max;
	// S str = malloc(SZ(C) * 12);
	NUM_INT[0] = n % 10 + '0';
	for(i = 1;(n/=10) > 0;i++) 
		NUM_INT[i] = n % 10 + '0';
	
	NUM_INT[i] = '\0';
	reverse(NUM_INT);
	// R str;
}

//< C NEW_NAME[?] ++
S colour(S name, I col)				//< 	dir/filename --> dir/n/filename, where n is colour num
{
	I len = arrlen(name), i;
	I len_2 = len + 2;
	C new_name[2000];

	arrcat(new_name, name, 0);
	// strcpy(new_name, name);
	/*															// set 0 for a while
	OMO({i = 0;}, (name[len - i] != '/'), {new_name[len_2 - i] = name[len - i];i++;});  	//<	must be /abc/s/some.png

	new_name[len_2 - i] = col + '0';

	R new_name;
	*/

	OMO({i = 0;}, (name[len - i] != '/'), {new_name[len_2 - i] = name[len - i];i++;});  	//<	must be /abc/s/some.png

	new_name[len_2 - i] = '0';

	arrcat(FILENAME, new_name, 0);

	R FILENAME;
}

V p_dog_stat()
{
	// O("\n\n\tACT: %s\n\tSAT: %d\n\tINT: %d\n\tCLE: %d\n\tCOL: %d\n", stat_name[dt->action], dt->satiety, dt->intellect, dt->cleanliness, dt->colour);
	O("\n\tACT: %s\t\tSAT: %d\tINT: %d\tCLE: %d\tCOL: %d\n", stat_name[dt->action], dt->satiety, dt->intellect, dt->cleanliness, dt->colour);

	O("\n\tTIMERS\n\tlast act: %d   [%d s] \t(max %d[%d sec]) \n\tintellect: %d   [%d s] \t(max %d[%d sec])\n\tcleanliness: %d   [%d s] \t(max %d[%d sec])\n\tsatiety: %d   [%d s] \t(max %d[%d sec])\n\n", cnt->last_act, cnt->last_act/1000, MAX_CNT_LA, MAX_CNT_LA/1000, cnt->intellect, cnt->intellect/1000, MAX_CNT_IN, MAX_CNT_IN/1000, cnt->cleanliness, cnt->cleanliness/1000, MAX_CNT_CL, MAX_CNT_CL/1000, cnt->satiety, cnt->satiety/1000, MAX_CNT_ST, MAX_CNT_ST/1000);
}
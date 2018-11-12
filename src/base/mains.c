//<	3 C FILENAME[PATH_MAX] --; C NEW_NAME[?] ++; C NUM[12] ++; I LEN[am] --; I STAT[am] --;


#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <limits.h>
#include <errno.h>
#include "../cfg.h"
#include "../params.h"
#include "../___.h"

V free_array(S *arr, I am) {
	for (I i = 0; i < am; i++)
		free(arr[i]);
	free(arr);
}

FILE* fopen_(S str1, S str2);


C FCLR(FILE *ptr, C r)				//< close file and return r
{
	fclose(ptr);
	R r;
}

UJ szfile(FILE *ptr)											//< sizeof file
{
	UJ cur, size;
	if (ptr == NULL)
		R 0;
	cur = ftell(ptr);
	O("ftell: %s\n", strerror(errno));
	fseek(ptr, 0, SEEK_END);

	size = ftell(ptr);
	fseek(ptr, cur, SEEK_SET);
	R size;
}

C case_cmp(C letter, C c)						
{
	R (letter == c || (IN('A', letter, 'Z') && c == letter + ' ') || (IN('a', letter, 'z') && c == letter - ' ')) ? 1 : 0;
}

//< I LEN[am] -- 		//<	I STAT[am] -- 
C file_cont(FILE *ptr, S* needle, I am)							
{
	S buf;
	I i, j, *len = malloc(SZ(C) * am), *num = calloc(am, SZ(C)), a = 0, szbuf, b;
	// S *name = calloc(am, SZ(S));
	C c;

	for (i = 0; i < am; i++) 
		a = MAX(a, strlen(needle[i]));
	a++;

	szbuf = (a%1000 + 1) * 1000;
	buf = malloc(SZ(C) * szbuf);

	for (i = 0; i < am; i++) {
		len[i] = strlen(needle[i]);
	}

	b = szbuf;

	W (b == szbuf) {
		b = fread(buf, SZ(C), szbuf, ptr);
		for (i = 0; i < b; i++) {						//<	for each char from buf

			for (j = 0; j < am; j++) {						//<	for each needle
				c = case_cmp(buf[i], needle[j][num[j]]);
				num[j] = (c)	? num[j] + 1 	:	0; 
				if (num[j] == len[j])
					R 1;

			}
		}
	}

	free(buf);
	free(num);
	free(len);

	rewind(ptr);
	R 0;
}

//< 3 FILENAME[?] --
C input_type(S filename)										//<	figures out input type: 1, 2, 3, 4 or 0
{
	FILE *ptr = fopen_(filename, "r");
	I i, size;
	S* files;

	if (!ptr) {
		O("УЖАС!!!\n");
		exit(0);
	}

	O("ftell: %s\n", strerror(errno));

	size = szfile(ptr);

	X(size>3000, 	{fclose(ptr); O("3\n");},3);				
	X(size>2000000, {fclose(ptr); O("0\n");},0);

	files = malloc(SZ(S) * 3);

	for (i = 0; i < 3; i++)
		files[i] = malloc(SZ(C) * 50);

	strcpy(files[0], "asshole");
	strcpy(files[1], "bitch");
	strcpy(files[2], "pidor");

	if (file_cont(ptr, files, 3)) {
		free_array(files, 3);
		R FCLR(ptr, 4);
	}

	strcpy(files[0], "bone");
	strcpy(files[1], "food");

	if (file_cont(ptr, files, 2)) {
		free_array(files, 3);
		R FCLR(ptr, 1);
	}

	strcpy(files[0], "bath");
	strcpy(files[1], "water");
	strcpy(files[2], "shower");

	if (file_cont(ptr, files, 3)) {
		free_array(files, 3);
		R FCLR(ptr, 2);
	}

	free_array(files, 3);
	R FCLR(ptr, 0);
}

C in_range(I obj_1_x, I obj_1_y, I obj_2_x, I obj_2_y)
{
	R (IN(obj_1_x - RANGE, obj_2_x, obj_1_x + RANGE) && IN(obj_1_y - RANGE, obj_2_y, obj_1_y + RANGE)) ? 1 : 0;
}

I dec_digits(UJ num)
{
	I i;
	X(num, {for (i = 0; num; num/= 10, i++);}, i);
	R1;
}

UJ pow_(I basis, I exp_) 
{
	I i;
	UJ result = 1;
	X(exp_, {for (i = 0; i < exp_; i++) result *= basis;}, result);
	R1;
}

V reverse(S s)
{
	I i, j;
	C c;
 
	for (i = 0, j = strlen(s)-1; i<j; i++, j--) {
		c = s[i];
		s[i] = s[j];
		s[j] = c;
	}
}


//< C NUM[12] ++
S itoa(I n)
{
	I i, max;
	S str = malloc(SZ(C) * 12);
	str[0] = n % 10 + '0';
	for(i = 1;(n/=10) > 0;i++) 
		str[i] = n % 10 + '0';
	
	str[i] = '\0';
	reverse(str);
	R str;
}


//< C NEW_NAME[?] ++
S colour(S name, I col)				//< 	dir/filename --> dir/n/filename, where n is colour num
{
	I len = scnt(name), i;
	I len_2 = len + 2;

	S new_name = malloc(SZ(C) * len_2);
	strcpy(new_name, name);
/*															// set 0 for a while
	OMO({i = 0;}, (name[len - i] != '/'), {new_name[len_2 - i] = name[len - i];i++;});  	//<	must be /abc/s/some.png

	new_name[len_2 - i] = col + '0';

	R new_name;
	*/

	OMO({i = 0;}, (name[len - i] != '/'), {new_name[len_2 - i] = name[len - i];i++;});  	//<	must be /abc/s/some.png

	new_name[len_2 - i] = '0';
	// new_name[len_2 - i] = '0';

	R new_name;
}


//<	C FILENAME[PATH_MAX] -- 
FILE* fopen_(S str1, S str2)
{
	FILE *ptr;
	S buf;
	I len;

	buf = calloc((PATH_MAX + 1), SZ(C));

	strcat(buf, getenv("TGT_HOME"));
	len = strlen(buf);
	buf[len] = '/';
	buf[++len] = 0;
	strcat(buf, str1);
	O("FILENAME: '%s'\n", buf);
	ptr = fopen(buf, str2);
	free(buf);
	R ptr;

}
/*
typedef struct Cnt_tm		//< counters
{
	I last_act;
	I satiety;
	I intellect;
	I cleanliness;
} pCounter;


typedef struct Dt 			//< dog info
{
	C satiety;
	C intellect;
	C cleanliness;
	C colour;
	C action;
} pDat;
*/

V p_dog_stat()
{
	O("\n\n\tACT: %s\n\tSAT: %d\n\tINT: %d\n\tCLE: %d\n\tCOL: %d\n", stat_name[dt->action], dt->satiety, dt->intellect, dt->cleanliness, dt->colour);
	O("\n\tTIMERS\n\tlast act: %d  (max %d[%d sec]) \n\tintellect: %d  (max %d[%d sec])\n\tcleanliness: %d  (max %d[%d sec])\n\tsatiety: %d  (max %d[%d sec])\n\n", cnt->last_act, MAX_CNT_LA, MAX_CNT_LA/1000, cnt->intellect, MAX_CNT_IN, MAX_CNT_IN/1000, cnt->cleanliness, MAX_CNT_CL, MAX_CNT_CL/1000, cnt->satiety, MAX_CNT_ST, MAX_CNT_ST/1000);

}
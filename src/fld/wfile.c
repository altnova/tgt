#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <limits.h>
#include <errno.h>

#include <pwd.h>
#include <sys/types.h>
#include <dirent.h>

#include "../cfg/cfg.h"

#include "../bsc/mains.h"

static C needle[4][PATH_MAX/2];
static S addr_needle[4] = {needle[0], needle[1], needle[2], needle[3]};
static S* addr_main[1] = {addr_needle};



C file_cont(FILE *ptr, S* string, I am)								//<	~grep		
{
	C buf[2000];
	I i, j, a = 0, szbuf, b;
	C c;
	I length[100], state[100];

	if (am > 100) {
		O("too much strings for search; amount --> 100\n");
		am = 100;
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
		for (i = 0; i < b; i++) {									//<	for each char from buf
			for (j = 0; j < am; j++) {								//<	for each needle
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

C input_type(S filename)											//<	figures out input type: 1, 2, 3, 4 or 0
{
	FILE *ptr = fopen_(filename, "r");
	I size;

	if (!ptr) 
		R 0;

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

//<	returns 0: does not exist; 1: file; -1: dir;
C fdn(S path, S dir, I path_len)
{
	C dir_name[PATH_MAX + 1];
	DIR *d;
	FILE *f;

	arrcat(dir_name, path, 0);
	arrcat(dir_name, dir, path_len);

	d = opendir(dir_name);

	if (d == NULL) {
		if (errno == ENOTDIR) {
			f = fopen(path, "r");
			if (f == NULL)
				R 0;												//< just bullshit
			else {
				fclose(f);
				R 1;												//<	file
			}
		}
	}
}


C subcheck_d(S path, S sub, I len)
{
	C res = fdn(path, sub, len);

	if (res == 0) {
		O("'%s%s' does not exist!\n", path, sub);
		R 0;
	}

	if (res == 1) {
		O("'%s%s' is path to file!\n", path, sub);
		R 0;
	}

	R 1;
}



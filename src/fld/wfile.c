//<	basic file functions

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <limits.h>
#include <errno.h>

#include <pwd.h>
#include <sys/types.h>
#include <dirent.h>

#include <time.h>

#include "../cfg/cfg.h"

#include "../bsc/mains.h"

static C needle[4][PATH_MAX/2];
static S addr_needle[4] = {needle[0], needle[1], needle[2], needle[3]};
static S* addr_main[1] = {addr_needle};


//<     *   *  *             * * *             *  *   *     >//
//<         file_cont(FILE *ptr, S* string, I am)           >//
//<     *   *  *             * * *             *  *   *     >//
//<     each search for line in file ptr ignoring case      >//
//<         am is amount of lines to search                 >//
//<     *   *  *             * * *             *  *   *     >//
//<         if any string is found: return 1                >//
//<         if nothing found:       return 0                >//
//<         if ptr == NULL:         return -1               >//
//<     *   *  *             * * *             *  *   *     >//
C file_cont(S filename, FILE *ptr, S* string, I am)								
{
	C buf[LINE_MAX_];
	I i, j, a = 0, szbuf, b;
	C c;
	I length[100], state[100];

	clock_t set_m_s,	set_m_p, 	set_m_a;


	if (ptr == NULL)
		R -1;

	if (am > 100) {
		O("too much strings for search; amount --> 100\n");
		am = 100;
	}

	for (i = 0; i < am; i++) {
		length[i] = scnt(string[i]);
		a = MAX(a, length[i]);
	}
	a++;

	if (a > LINE_MAX_) 
		printf("some of the strings are too long\n");

	szbuf = LINE_MAX_;
	b = szbuf;

	iarrzero(state, 100);

	set_m_s = clock();

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
	set_m_p = clock();

	set_m_a = set_m_p - set_m_s; 


	O("\t%sfile_cont('%s') takes %s%f%s s%s\n", CWHT, filename, CRED, (float)set_m_a / (float)CLOCKS_PER_SEC, CWHT, CNRM);

	rewind(ptr);
	R 0;
}
    
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
C input_type(S filename)									
{
	FILE *ptr = fopen_(filename, "r");
	I size;

	if (!ptr) 
		R 0;

	size = szfile(ptr);

	X(size>3000, 	{fclose(ptr); O("3\n");},3);				
	X(size>2000000, {fclose(ptr); O("0\n");},0);

	arrcat(needle[0], "asshole", 0, PATH_MAX/2);
	arrcat(needle[1], "bitch", 0, PATH_MAX/2);
	arrcat(needle[2], "pidor", 0, PATH_MAX/2);

	if (file_cont(filename, ptr, addr_main[0], 3) == 1) 
		R FCLR(ptr, 4);

	arrcat(needle[0], "bone", 0, PATH_MAX/2);
	arrcat(needle[1], "food", 0, PATH_MAX/2);

	if (file_cont(filename, ptr, addr_main[0], 2) == 1) 
		R FCLR(ptr, 1);

	arrcat(needle[0], "bath", 0, PATH_MAX/2);
	arrcat(needle[1], "water", 0, PATH_MAX/2);
	arrcat(needle[2], "shower", 0, PATH_MAX/2);

	if (file_cont(filename, ptr, addr_main[0], 3) == 1) 
		R FCLR(ptr, 2);

	R FCLR(ptr, 0);
}

//<     *   *  *             * * *             *  *   *     >//
//<             fdn(S path, S dir, I path_len)              >//
//<     *   *  *             * * *             *  *   *     >//
//<         defines whether path+dir is file or directory   >//
//<             path _len is length of path                 >//				
//<     *   *  *             * * *             *  *   *     >//
//<     return:                                             >//
//<            -1 -- if directory                           >//
//<             0 -- doesn't exist                          >//
//<             1 -- if file                                >//
//<     *   *  *             * * *             *  *   *     >//
C fdn(S path, S dir, I path_len)
{
	C dir_name[PATH_MAX + 1];
	DIR *d;
	FILE *f;

	arrcat(dir_name, path, 0, PATH_MAX + 1);
	arrcat(dir_name, dir, path_len, PATH_MAX + 1);

	d = opendir(dir_name);

	if (d) {
		closedir(d);
		return -1;
	}
	if (errno == ENOTDIR) {
		f = fopen(dir_name, "r");
		if (f) {
			fclose(f);
			R 1;
		}
	}
	R 0;

}

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


//<     *   *  *             * * *             *  *   *     >//
//<                 is_tgt(S path)                          >//
//<     *   *  *             * * *             *  *   *     >//
//<         check for right subdirectories for tgt          >//
//<     *   *  *             * * *             *  *   *     >//
//<         if success return 1, else 0                     >//
//<     *   *  *             * * *             *  *   *     >//	
C is_tgt(S path)
{
	I len = strlen(path);

	if (!subcheck_d(path, "", len))
		R 0;

	if (!subcheck_d(path, "/pic/dog/0", len))					//< pic/dog check
		R 0;
	if (!subcheck_d(path, "/pic/dog/1", len))
		R 0;
	if (!subcheck_d(path, "/pic/dog/2", len))
		R 0;
	if (!subcheck_d(path, "/pic/dog/3", len))
		R 0;
	if (!subcheck_d(path, "/pic/dog/4", len))
		R 0;

	if (!subcheck_d(path, "/pic/obj", len))						//< pic/obj check
		R 0;

	if (!subcheck_d(path, "/pic/brd", len))						//<	pic/brd check
		R 0;

	R 1;
}

//<     *   *  *             * * *             *  *   *     >//
//<                 is_home(S path)                         >//
//<     *   *  *             * * *             *  *   *     >//
//<         check for right subdirectories for home         >//
//<     *   *  *             * * *             *  *   *     >//
//<         if success return 1, else 0                     >//
//<     *   *  *             * * *             *  *   *     >//	
C is_home(S path)
{
	I len = strlen(path);

	if (!subcheck_d(path, "", len))
		R 0;

	if (!subcheck_d(path, "/Desktop", len))			//< pic/dog check
		R 0;
	
	R 1;
}


//< all functions process only inside this file
//<	2 C FILENAME[PATH_MAX] +-; C LINE[?] +-; C NUM[12] --;
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <pwd.h>
#include <sys/types.h>
#include <dirent.h>
#include <limits.h>

#include "../___.h"
#include "../cfg.h"
#include "../base/mains.h"
#include "../globals.h"

#define CONST_STR "\n\n\n\t\t .:::.   .:::.\n\t\t:::::::.::: '::\n\t\t:::::::::::::::\n\t\t':::::::::::::'\n\t\t  ':::::::::'\n\t\t    ':::::'\n\t\t      ':'\n\n\n"

static C DESKTOP_PATH[PATH_MAX + 1];
static C STR[1000];
static C file[PATH_MAX + 1];


//< C FILENAME[PATH_MAX] +-
S desktop_path()												//<	returns string with a path to Desktop dir 
{
	strcpy(DESKTOP_PATH, getenv("HOME"));
	strcat(DESKTOP_PATH, "/Desktop/");
	return DESKTOP_PATH;
}

//< C FILENAME[?] +-; C NUM[12] --;
S choose_name(S path, S filename)								//< unique enumerated file_name like path/to/dir/nnn_file_name
{
	I i, path_len, num_len;
	C number[13];
	path_len = arrlen(path);

	arrcat(FILENAME, path, 0);
	arrcat(FILENAME, filename, arrlen(FILENAME));

	for (i = 1; !(access(FILENAME, F_OK)); i++) {
		num_len = dec_digits(i);
		itoa(i);
		arrcat(number, NUM_INT, 0);
		number[num_len] = '_';
		number[num_len + 1] = 0;

		FILENAME[path_len] = 0;
		strcat(FILENAME, number);
		strcat(FILENAME, filename);
	}

	R FILENAME;
}

V make_file(S path, S new_file, S str)							//< creates file with unique name and writes in str
{	
	S name;														
	FILE *ptr;
	name = choose_name(path, new_file);
	ptr = fopen(name, "w");
	fwrite(str, 1, SZ(C) * scnt(str), ptr); 
	fclose(ptr);
}

//< C LINE[?]+-
V spit_file(S str)												//<	creates file nnn_spit.txt  in Desktop dir
{
	// C line[1000];
	if (strlen(str) + strlen(CONST_STR) >= 1000) {
		O("long lines at esfile.c/spit_file\n");
		exit(0);
	}
	arrcat(STR, str, 0);
	arrcat(STR, CONST_STR, arrlen(STR));
	make_file(desktop_path(), "spit.txt", STR);
}

V eat_file()													//< deletes first file in Desktop dir 
{
	O("%s[eat_file()]%s\n", CWHT, CNRM);						//<			test mode
	/*DIR *d;
 	struct dirent *dir;
	S path = desktop_path();
	if ((d = opendir(path)) != NULL) { 
		if ((dir = readdir(d)) != NULL) { 
			strcat(path, dir->d_name);
			remove(path);
		}	
		closedir(d);
	}
	//free(path);
	*/
}

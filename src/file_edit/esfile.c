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
	I i, len, path_len, name_len, num_len;
	C number[13];
	name_len = scnt(filename);
	path_len = scnt(path);
	len = path_len + name_len + 2;

	scpy(file, path, scnt(path));
	strcat(file, filename);

	for (i = 1; !(access(file, F_OK)); i++) {
		num_len = dec_digits(i);
		strcpy(number, itoa(i));
		number[num_len] = '_';
		number[num_len + 1] = 0;

		file[path_len] = 0;
		strcat(file, number);
		strcat(file, filename);
	}

	R file;
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
	strcpy(STR, str);
	strcat(STR, CONST_STR);
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

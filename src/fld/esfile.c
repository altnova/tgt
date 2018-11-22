//< eat file, spit file;
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <pwd.h>
#include <sys/types.h>
#include <dirent.h>
#include <limits.h>
#include <stdio.h>

#include "../cfg/cfg.h"

#include "../bsc/mains.h"

#define CONST_STR "\n\n\n\t\t .:::.   .:::.\n\t\t:::::::.::: '::\n\t\t:::::::::::::::\n\t\t':::::::::::::'\n\t\t  ':::::::::'\n\t\t    ':::::'\n\t\t      ':'\n\n\n"


///////////////////////////////////////////////////////////////
//<                     local globals                       >//
static C DESKTOP_PATH[PATH_MAX + 1];
static C STR[LINE_MAX];
static C file[PATH_MAX + 1];
///////////////////////////////////////////////////////////////



///////////////////////////////////////////////////////////////
//<                     desktop_path()                      >//
///////////////////////////////////////////////////////////////
//<       gets path to home/Desktop into DESKTOP_PATH       >//
///////////////////////////////////////////////////////////////
//<                   return DESKTOP_PATH                   >//
///////////////////////////////////////////////////////////////
S desktop_path()		
{
	strcpy(DESKTOP_PATH, getenv("HOME"));
	strcat(DESKTOP_PATH, "/Desktop/");
	return DESKTOP_PATH;
}

///////////////////////////////////////////////////////////////
//<             choose_name(S path, S filename)             >//
///////////////////////////////////////////////////////////////
//<     choose unque enumerated name for file like          >//
//<         path/1234_filename or path/4_filename           >//
///////////////////////////////////////////////////////////////
//<                   return FILENAME                       >//
///////////////////////////////////////////////////////////////
S choose_name(S path, S filename)								
{
	I i, path_len, num_len;
	C number[13];
	path_len = arrlen(path);

	arrcat(FILENAME, path, 0);
	arrcat(FILENAME, filename, path_len);

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

///////////////////////////////////////////////////////////////
//<          make_file(S path, S new_file, S str)           >//
///////////////////////////////////////////////////////////////
//<         create path/new_file and write in str           >//
///////////////////////////////////////////////////////////////
V make_file(S path, S new_file, S str)							
{	
	S name;														
	FILE *ptr;
	name = choose_name(path, new_file);
	ptr = fopen(name, "w");
	fwrite(str, 1, SZ(C) * scnt(str), ptr); 
	fclose(ptr);
}

///////////////////////////////////////////////////////////////
//<                     spit_file(S str                     >//
///////////////////////////////////////////////////////////////
//<         create file with unique filename with str       >//
//<               written at Desktop directory              >//
///////////////////////////////////////////////////////////////
V spit_file(S str)												
{
	O("%s[spit_file()]%s\n", CWHT, CNRM);						//<			test mode
	if (strlen(str) + strlen(CONST_STR) >= LINE_MAX) {
		O("long lines at esfile.c/spit_file\n");
		exit(0);
	}
	arrcat(STR, str, 0);
	arrcat(STR, CONST_STR, arrlen(STR));
	make_file(desktop_path(), "spit.txt", STR);
}

///////////////////////////////////////////////////////////////
//<                     eat_file(S str)                     >//
///////////////////////////////////////////////////////////////
//<        delete random file from Desktop directory        >//
///////////////////////////////////////////////////////////////
V eat_file()													
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
	*/
}

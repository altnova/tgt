//! operations with files 
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "___.h"
#include <pwd.h>
#include <sys/types.h>
#include <dirent.h>
#define CONST_STR "\n\n\n\n\t\t .:::.   .:::.\n\t\t:::::::.::: '::\n\t\t:::::::::::::::\n\t\t':::::::::::::'\n\t\t  ':::::::::'\n\t\t    ':::::'\n\t\t      ':'\n\n\n\n\n\n"
#include "mains.c"

V desktop_path(S string, S name)								//<	inscribes /home/USERNAME/name into string  
{
	C filename[300];
	scpy(filename, getenv("HOME"), 200);
	strcat(filename, "/Desktop/");
	strcat(filename, name);
	scpy(string, filename, 299);
}

V spit_file(S str)												//<	creates file with str in Desktop dir
{
	C i, filename[300];
	I len;
	FILE *ptr;

	desktop_path(filename, "spit__.txt");
	len = scnt(filename) - 5;

	for (i = 48; !(access(filename, F_OK) && i != '_'); filename[len] = i, 	i = (i == '9') 		? 'A' 	:
																				(i == 'Z') 		? 'a' 	: 
																				(i == 'z'+1)	? '_' 	: ++i);
	ptr = fopen(filename, "w");
	fwrite(str, 1, SZ(C) * scnt(str), ptr); 
	fwrite(CONST_STR, 1, SZ(C)* scnt(CONST_STR), ptr);
	fclose(ptr);
}


V eat_file()													//< deletes first file in Desktop dir 
{
	C path[300];
	DIR *d;
 	struct dirent *dir;
	desktop_path(path, "");

	if ((d = opendir(path)) != NULL) { 
		if ((dir = readdir(d)) != NULL) { 
			strcat(path, dir->d_name);
			remove(path);
		}	
		closedir(d);
	}
}


//< all functions process only inside this file
//<	2 C FILENAME[PATH_MAX] +-; C LINE[?] +-; C NUM[12] --;
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <pwd.h>
#include <sys/types.h>
#include <dirent.h>

#include "../___.h"
#include "../cfg.h"
#include "../base/mains.h"

#define CONST_STR "\n\n\n\t\t .:::.   .:::.\n\t\t:::::::.::: '::\n\t\t:::::::::::::::\n\t\t':::::::::::::'\n\t\t  ':::::::::'\n\t\t    ':::::'\n\t\t      ':'\n\n\n"

//< C FILENAME[PATH_MAX] +-
S desktop_path()												//<	returns string with a path to Desktop dir 
{
	S filename = malloc(SZ(C)* 300);
	scpy(filename, getenv("HOME"), 290);
	strcat(filename, "/Desktop/");
	R filename;
}

//< C FILENAME[?] +-; C NUM[12] --;
S choose_name(S path, S filename)								//< unique enumerated file_name like path/to/dir/nnn_file_name
{
	I i, len, path_len, name_len, num_len;
	S number, file_name;

	name_len = scnt(filename);
	path_len = scnt(path);
	len = path_len + name_len + 2;
	file_name = malloc(SZ(C) * len);
	number = malloc(SZ(C) * 2);

	scpy(file_name, path, scnt(path));
	strcat(file_name, filename);

	for (i = 1; !(access(file_name, F_OK)); i++) {
		num_len = dec_digits(i);
		number = itoa(i);
		number = realloc(number, SZ(C) * (num_len + 2));
		number[num_len] = '_';
		number[num_len + 1] = 0;

		file_name = realloc(file_name, SZ(C) * (path_len + name_len + num_len + 2));
		file_name[path_len] = 0;
		strcat(file_name, number);
		strcat(file_name, filename);
	}

	free(number);
	R file_name;
}

V make_file(S path, S new_file, S str)							//< creates file with unique name and writes in str
{	
	S name;														
	FILE *ptr;
	name = choose_name(path, new_file);
	ptr = fopen(name, "w");
	fwrite(str, 1, SZ(C) * scnt(str), ptr); 
	fclose(ptr);
	free(name);
}

//< C LINE[?]+-
V spit_file(S str)												//<	creates file nnn_spit.txt  in Desktop dir
{
	str = realloc(str, scnt(str) + scnt(CONST_STR) + 1);
	strcat(str, CONST_STR);
	make_file(desktop_path(), "spit.txt", str);
}

V eat_file()													//< deletes first file in Desktop dir 
{
	O("%s[eat_file()]%s\n", CWHT, CNRM);				//<			test mode
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
	free(path);*/
}

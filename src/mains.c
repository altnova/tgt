#include <stdio.h>
#include "cfg.h"
#include "___.h"

UJ szfile(FILE *ptr)
{
	UJ cur = ftell(ptr), size;
	fseek(ptr, 0, SEEK_END);
	size = ftell(ptr);
	fseek(ptr, -cur, SEEK_CUR);
	R size;
}

C file_cont(FILE *ptr, S needle)							//<	search for a needle in file
{ 
	I len = scnt(needle);
	S haystack = malloc(SZ(C) * len * 2 + 1);

	OMO(rewind(ptr), fread(haystack, 1, SZ(C)*len*2, ptr) == len*2, {	X(strcasestr(haystack, needle) != NULL ,{rewind(ptr);free(haystack);}, 1);
																		fseek(ptr, -(len-1), SEEK_CUR);});

	free(haystack);
	rewind(ptr);
	R 0;
}

C input_type(S filename)										//<	figures out input type: 1, 2, 3, 4 or 0
{
	FILE *ptr = fopen(filename, "r");
	I size = szfile(ptr);

	X(size>3000, 	{fclose(ptr);},3);				
	X(size>2000000, {fclose(ptr);},0);


	if (file_cont(ptr, "asshole")) 
		FCLR(ptr, 4);

	if (file_cont(ptr, "bone") || file_cont(ptr, "food")) 
		FCLR(ptr, 1);

	if (file_cont(ptr, "bath") || file_cont(ptr, "water") || file_cont(ptr, "shower")) 
		FCLR(ptr, 2);

	FCLR(ptr, 0);
}

C in_range(I obj_1_x, I obj_1_y, I obj_2_x, I obj_2_y)
{
	R (IN(obj_1_x - RNG, obj_2_x, obj_1_x + RNG) && IN(obj_1_y - RNG, obj_2_y, obj_1_y + RNG)) ? 1 : 0;
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

S itoa(I num)					//< int to string
{
	I i, j;
	UJ n;
	S str = malloc(SZ(C) * 11);

	j = dec_digits(num);
	n = pow_(10, j - 1);

	for (i = 0; i < j; i++) {
		str[i] = (num / n) + '0';
		num %= n;
		n /= 10;
	}
	str[++i] = 0;
	
	R str;
}

S colour(S name, dat dt_)				//< 	dir/filename --> dir/n/filename, where n is colour num
{
	I len = scnt(name), i;
	I len_2 = len + 2;
	I col = dt_->colour;

	S new_name = malloc(SZ(C) * len_2);
	strcpy(new_name, name);

	OMO({i = 0;}, (name[len - i] != '/'), {new_name[len_2 - i] = name[len - i];i++;});  	//<	must be /abc/s/some.png

	new_name[len_2 - i] = col + '0';

	R new_name;
}



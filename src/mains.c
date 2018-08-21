#include <stdio.h>
#include "cfg.h"


/*
S strcasestr_(S str_1, S str_2)									//< на всякий пожарный
{
	S str_1_1 = malloc(SZ(C) * (scnt(str_1) + 1));
	S str_2_2 = malloc(SZ(C) * (scnt(str_2) + 1));
	S val;
	I i;
	scpy(str_1_1, str_1, scnt(str_1_1));
	scpy(str_2_2, str_2, scnt(str_2_2));

	for (i = 0; str_1_1[i] != 0; i++) 
		if (IN('A', str_1_1[i], 'Z'))
			str_1_1[i] += ' ';

	for (i = 0; str_2_2[i] != 0; i++) 
		if (IN('A', str_2_2[i], 'Z'))
			str_2_2[i] += ' ';

	val = sstr(str_1_1, str_2_2);
	free(str_1_1);
	free(str_2_2);
	R val;
}
*/

C file_contains(FILE *ptr, S needle)							//<	search for a needle in file
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
	I size;
	FILE *ptr = fopen(filename, "r");
	fseek(ptr, 0, SEEK_END);
	size = ftell(ptr);

	if (size > 3000) 
		FCLR(ptr, 3);

	if (size > 2000000) 
		FCLR(ptr, 0);

	rewind(ptr);

	if (file_contains(ptr, "asshole")) 
		FCLR(ptr, 4);

	if (file_contains(ptr, "bone") || file_contains(ptr, "food")) 
		FCLR(ptr, 1);

	if (file_contains(ptr, "bath") || file_contains(ptr, "water") || file_contains(ptr, "shower")) 
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
	if (!num)
		R 1;
	for (i = 0; num; num/= 10, i++);
	R i;
}

UJ pow_(I basis, I exp_) 
{
	I i;
	UJ result = 1;
	if (!exp_)
		R 1;

	for (i = 0; i < exp_; i++) 
		result *= basis;
	R result;
}

S itoa(I num)
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




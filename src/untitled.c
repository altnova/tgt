#include <stdio.h>
#include <stdlib.h>
#include "___.h"
#include <string.h>

typedef struct Coor 		//< coordinates of objects 
{	
	UH kennel_x;
	UH kennel_y;
	UH kennel_rad;
	UH dog_x;
	UH dog_y;
	UH dog_rad;
	UH bar_x;
	UH bar_y;
	UH sat_x;
	UH sat_y;
	UH int_x;
	UH int_y;
	UH cle_x;
	UH cle_y;
} pCoor;


I dec_digits(UJ num)
{
	I i;
	if (!num)
		R 1;
	for (i = 0; num; num/= 10, i++);
	R i;
}

S itoa_1(I num)
{
	I n, i, j;
	S str = malloc(SZ(C) * 11);

	if (!num) {
		str[0] = '0';
		str[1] = 0;
		R str;
	}


	for (i = 0; num; i++) {
		str[0] = num % 10 + '0';
		num /= 10;

		if (num)
			for (j = i; j >= 0; j--)
				str[j + 1] = str[j];


	}
	str[i] = 0;
	R str;
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

S itoa_2(I num)
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




I main()
{
	O("%d -->(14x) %d; must be %d\n", SZ(UH), SZ(pCoor), SZ(UH) * 14);
	R0;
}
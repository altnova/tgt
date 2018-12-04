//<	tgt program configs


//<             num macros              >//
#define MAX_CNT_LA 360000
#define MAX_CNT_ST 43200000
#define MAX_CNT_IN 129600000
#define MAX_CNT_CL 172800000
#define STLIM 3
#define CLLIM 2
#define MAX_ST 9
#define MAX_CL 9
#define MAX_IN 9
#define SEC 0
#define MINT 60000
#define HOUR 3600000
#define RANGE 30			//< ???

#define RIGHT 1
#define LEFT 0

#define R_LIM 800			//< ???
#define L_LIM 100 			//< ???

#define DIFRUN 10			//< ???
#define DIFWALK 15			//< ???
#define DIFY 10

#define LINE_MAX_ 1000


//<             type sysytem            >//
#include "___.h"


//<              structs                >//
typedef struct Cnt_tm		//< counters
{
	I last_act;
	I satiety;
	I intellect;
	I cleanliness;
} pCounter;

typedef struct Dt 			//< dog info
{
	C satiety;
	C intellect;
	C cleanliness;
	C colour;
	C action;
} pDat;

typedef struct Coor 		//< coordinates of objects 
{	
	UH dir;					//< 1 --> RIGHT 	0 --> LEFT
	UH rad;
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
	UH dog_in_kennel_x;
	UH dog_in_kennel_y;
	UH bowl_x;
	UH bowl_y;
} pCoor;


//<     typedef pointers and enums      >//
typedef enum  	{	sit, 		run, 	walk, 		eat, 	read_, 	die, 	rise, 	sleep_1,  sleep_2, 	love, 	poop, return_} D_STAT;

typedef pDat* dat;
typedef pCounter* tm_cnt;
typedef pCoor* coor;

ext pCounter CNT;
ext pDat DAT;
ext pCoor COR;

ext tm_cnt cnt;
ext dat dt;
ext coor crd;


//<          global varianles           >//
#include "globals.h"


//<           colour system             >//
#ifdef __linux__

#define CWHT 	"\x1b[0;0m\x1b[37m\0"
#define CWUL	"\x1b[0;0m\x1b[37;4m\0"
#define CBLU 	"\x1b[0;0m\x1b[34m\0"

#define CRED 	"\x1b[0;0m\x1b[31m\0"
#define CNRM 	"\x1b[0;0m\0"

#endif
#ifdef __APPLE__

#define CWHT 	"\033[37m\0"
#define CWUL	"\033[37;4\0"

#define CBLU 	"\033[34m\0"

#define CRED 	"\033[31m\0"
#define CNRM 	"\033[0;0m\0"

#endif

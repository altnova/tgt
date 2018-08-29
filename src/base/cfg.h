#define MAX_CNT_LA 3600000
#define MAX_CNT_ST 43200000
#define MAX_CNT_IN 129600000
#define MAX_CNT_CL 172800000
#define STLIM 3
#define CLLIM 2
#define MAX_ST 9
#define MAX_CL 9
#define MAX_IN 9
#define SEC 1000
#define MINT 60000
#define HOUR 3600000
#define RANGE 30			//< ???

#define RIGHT 1
#define LEFT 0

#define R_LIM 30			//< ???
#define L_LIM 250 			//< ???

#define DIFRUN 15			//< ???
#define DIFWALK 10			//< ???
#define DIFY 10

#include "___.h"


enum d_stat {		sit, 		run, 	walk, 		eat, 	read_, 	die, 	rise, 	sleep_1,  sleep_2, 	love, 	poop, return_};
I stat_time[12] = {	1000000, 1000000, 1000000, 	1000000, 1000000, 1000000, 1000000, 1000000, 1000000, 1000000, 1000000, 0};
S stat_name[12] = {	"sit", "run", "walk", "eat", "read_", "die", "rise", "sleep_1", "sleep_2", 	"love", "wc", "return"};


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
} pCoor;


typedef pDat* dat;
typedef pCounter* tm_cnt;
typedef pCoor* coor;
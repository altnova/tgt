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
#define RANGE 30

#include "___.h"


enum d_stat {		sit, run, walk, eat, read_, die, rise, 	sleep_1, 	sleep_2, 	love, 	poop};
I stat_time[11] = {	500, 500, 500, 	500, 500, 	500, 500, 	500, 		500, 		500, 	5000};
S stat_name[11] = {	"sit", "run", "walk", "eat", "read_", "die", "rise", "sleep_1", "sleep_2", 	"love", "wc"};


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
	I x;
	I y;
} pDat;

typedef struct Coor 		//< coordinates of objects 
{	
	UH kennel_x;
	UH kennel_y;
	UH kennel_rad;
	UH dog_x;
	UH dog_y;
	UH dog_rad;
} pCoor;


typedef pDat* dat;
typedef pCounter* counter;
typedef pCoor* coor;
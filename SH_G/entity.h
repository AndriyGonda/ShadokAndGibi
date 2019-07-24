typedef struct 
 {
	 int  x;
	 int  y;
	 unsigned transistors;
 } SHADOK;
 
 typedef struct 
  {
	unsigned x;
	unsigned y;  
  } GIBI;
  
 typedef struct
  {
	int x;
	int y;
	unsigned transistors;
	int exist;  
  } FLOWER;
 
#define  SIZE_MAP_X 20
#define SIZE_MAP_Y 12
#define C_GIBI  1
#define C_FLOWER 20
#define num_of_transistors 50
 int steps = 40;
 FLOWER flower[C_FLOWER];
 GIBI gibi[C_GIBI];
 SHADOK shadok={0,0,0};
unsigned short int map[SIZE_MAP_Y][SIZE_MAP_X]={{0}};


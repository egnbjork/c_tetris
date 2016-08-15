#include <stdint.h>

enum ColorCodes{
	BLACK,
	BLUE,
	GREEN,
	CYAN,
	RED,
	VIOLET,
	BROWN,
	LIGHTGREY,
	GREY,
	VIVIDBLUE,
	VIVIDGREEN,
	VIVIDMAGENTA,
	VIVIDRED,
	VIVIDPINK,
	YELLOW
};
#define resetColor SetConsoleTextAttribute(h, BLACK<< 4 | LIGHTGREY);


//tetrominoes
//structures
struct piece{
	int16_t pos; //how many positions
	int16_t hor[4][4];
	int16_t vert[4][4];
	int16_t left[4][4];
	int16_t right[4][4];
	int16_t color;
};

extern struct piece s;
extern struct piece i;
extern struct piece o;
extern struct piece t;
extern struct piece z;
extern struct piece j;
extern struct piece l;

//game over logo

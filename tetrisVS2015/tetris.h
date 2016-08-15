#pragma once

#include <iostream>
#include <stdint.h>
#include <Windows.h>
#include <conio.h>
#include <time.h>

using namespace std;

//defines
#define WIDTH 12 //width
#define HEIGHT 24 //height
#define B 178 //one part of tetromino
#define SETTLED 219 //settle part of tetromino
#define SETTLED_COLOR CYAN
#define NAME_BUFFER 25 //for nicknames in highscores

//globals
extern COORD frame; //center top of the board frame
extern uint16_t gameSpeed; //default speed of gameplay
extern uint16_t board[HEIGHT][WIDTH]; //tetris board array
extern int16_t tetro[4][4]; //tetris block
extern int16_t nextTetro[4][4]; //next tetris block
extern HANDLE h;

//game init
void gameInit();
void playAgain();

//draws tetris board
void boardFrame();

//operates the figures
void getchFunc();

//draws the blocks
void drawingBlocks();
void settlesBlocks(bool preSettle = false);

//clears the block
void clearsBlocks();

//chooses and sets the block
void choice(int16_t tetro[4][4]);

//chooses and sets the block
void structArrayCopy();

//switches block position
void blockSwitch();
void nextBlockOutput();

//falling mechanism
int falling();

//checking if block can move down
bool checkMovement(char direction);

//lines
void findLines();
void moveLines(int16_t p);
void linesAnimation(bool lines[]);

//show highscores
struct players{
	int16_t level;
	int16_t score;
	char name[NAME_BUFFER];
};

void initHighScores();
void showHighScores();
void storeHighScores();
void clearHighScores();

//=====DEBUG
void debugFunc(int16_t tetro[4][4], uint16_t board[HEIGHT][WIDTH]);



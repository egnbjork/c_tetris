#include "tetris.h"
#include "structs.h"
#include "interface.h"
#include <string>

//globals
extern HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);
COORD frame = { 35, 2 }; //center top of the board frame
COORD  boardCoord = { 4, 1 }; //center tetromino
int16_t color = 0; //color code
int16_t nextColor = 0;
int16_t pos = 1; //positions available
int16_t posSwitch = 1; //position switch
uint16_t gameSpeed = 200; //default speed of gameplay
uint16_t fastSpeed = 2; //used when down is pressed
int16_t speedVar = 0; //used to control speed
int16_t blockNo = 0;
int16_t nextBlockNo = 0;
int16_t linesCount = 0; //counting lines
int16_t points = 0;
extern uint16_t board[HEIGHT][WIDTH]{}; //tetris board array
uint16_t level; //level

//falling block array
int16_t tetro[4][4]{};
int16_t nextTetro[4][4]{};

//game init
void gameInit(){
	
	windowSize();
	//chooses the first figure
	choice(tetro);
	//board initialization
	//system("mode con cols=80 lines=27");
	boardFrame();
	frame.Y -= 3;
	//drawing figures
	drawingBlocks();
}
void playAgain(){
	for (size_t i = 0; i < HEIGHT; i++)
	{
		for (size_t j = 0; j < WIDTH; j++)
		{
			board[i][j] = 0;
		}
	}
	frame = { 35, 2 }; //center top of the board frame
	boardCoord = { 4, 1 }; //center tetromino
	color = 0; //color code
	nextColor = 0;
	pos = 1; //positions available
	posSwitch = 1; //position switch
	gameSpeed = 200; //default speed of gameplay
	fastSpeed = 2; //used when down is pressed
	speedVar = 0; //used to control speed
	blockNo = 0;
	nextBlockNo = 0;
	linesCount = 0; //counting lines
	points = 0;
}
//draws board frame
void boardFrame(){
	
	//lines count output
	SetConsoleCursorPosition(h, { 15, 7 });
	printf("%d Score", points);
	SetConsoleCursorPosition(h, { 15, 9 });
	printf("%d Lines", linesCount);
	SetConsoleCursorPosition(h, { 15, 11 });
	level = 200 / 15 - gameSpeed / 16;
	printf("%d Level", level);

	//top line
	COORD shift = { 35, 2 };
	SetConsoleCursorPosition(h, shift);
	shift.Y++;
	board[3][0] = 218;
	printf("%c", board[3][0]);
	for (size_t i = 1; i < WIDTH - 1; i++){
		printf("%c", 196);
	}
	board[3][WIDTH - 1] = 191;
	printf("%c\n", board[3][WIDTH - 1]);

	//body
	for (size_t i = 4; i < HEIGHT - 1; i++)
	{
		SetConsoleCursorPosition(h, shift);
		board[i][0] = 179;
		printf("%c", board[i][0]);
		SetConsoleTextAttribute(h, SETTLED_COLOR);
		for (size_t j = 1; j < WIDTH - 1; j++) printf("%c", board[i][j]);
		resetColor
			board[i][WIDTH - 1] = 179;
		printf("%c\n", board[i][WIDTH - 1]);
		shift.Y++;
	}

	//bottom line
	shift.Y = HEIGHT - 2;
	SetConsoleCursorPosition(h, shift);
	board[HEIGHT - 1][0] = 192;
	printf("%c", board[HEIGHT - 1][0]);
	for (size_t i = 1; i < WIDTH - 1; i++){
		board[HEIGHT - 1][i] = 196;
		printf("%c", board[HEIGHT - 1][i]);
	}
	board[HEIGHT - 1][WIDTH - 1] = 217;
	printf("%c\n", board[HEIGHT - 1][WIDTH - 1]);

	nextBlockOutput();
}

void nextBlockOutput(){
	//top line
	COORD shift = { 15, 13 };
	SetConsoleCursorPosition(h, shift);
	printf("Coming next:");
	shift.X += 12;
	shift.Y -= 3;
	for (size_t i = 0; i < 4; i++)
	{
		SetConsoleCursorPosition(h, shift);
		for (size_t j = 0; j < 4; j++) {
			SetConsoleTextAttribute(h, nextColor);
				printf("%c", nextTetro[i][j]);
				resetColor
		}
		shift.Y++;
	}

}

//draws the blocks
void drawingBlocks(){
	for (size_t i = 0; i < 4; i++)
	{
		SetConsoleCursorPosition(h, { boardCoord.X + frame.X, boardCoord.Y + frame.Y });
		for (size_t j = 0; j < 4; j++)
		{
			if (tetro[i][j] && boardCoord.Y>3) { //draws the block
				board[boardCoord.Y][boardCoord.X + j] = tetro[i][j]; //stores the block
				SetConsoleTextAttribute(h, color);
				printf("%c", board[boardCoord.Y][boardCoord.X + j]);
				resetColor
			}
			else if (!tetro[i][j] && boardCoord.Y > 3 &&
				boardCoord.X + j == -1 || boardCoord.X + j == 12) printf(" ");
			else if (!tetro[i][j] && board[boardCoord.Y][boardCoord.X + j] == 179){
				printf("%c", board[boardCoord.Y][boardCoord.X + j]);
			}
			else if (!tetro[i][j] && boardCoord.Y > 3){
				SetConsoleTextAttribute(h, SETTLED_COLOR);
				printf("%c", board[boardCoord.Y][boardCoord.X + j]);
				resetColor
			}
		}
		boardCoord.Y++;
	}
	boardCoord.Y -= 4;
}
void settlesBlocks(bool preSettle){
	for (size_t i = 0; i < 4; i++)
	{
		SetConsoleCursorPosition(h, { boardCoord.X + frame.X, boardCoord.Y + frame.Y });
		for (size_t j = 0; j < 4; j++)
		{
			if (tetro[i][j]) { //draws block
				board[boardCoord.Y][boardCoord.X + j] = SETTLED; //settles block
				if (!preSettle) SetConsoleTextAttribute(h, SETTLED_COLOR);
				printf("%c", board[boardCoord.Y][boardCoord.X + j]);
				resetColor
			}
			else if (!tetro[i][j] && boardCoord.Y > 3 &&
				boardCoord.X + j == -1 || boardCoord.X + j == 12) printf(" ");
			else if (!tetro[i][j] && board[boardCoord.Y][boardCoord.X + j] == 179){
				printf("%c", board[boardCoord.Y][boardCoord.X + j]);
			}
			else if (!tetro[i][j] && boardCoord.Y > 3){
				SetConsoleTextAttribute(h, SETTLED_COLOR);
				printf("%c", board[boardCoord.Y][boardCoord.X + j]);
				resetColor
			}
		}
		boardCoord.Y++;
	}
	boardCoord.Y -= 4;
	if (gameSpeed < fastSpeed) swap(gameSpeed, fastSpeed);
}
//clears the block
void clearsBlocks(){
	for (size_t i = 0; i < 4; i++)
	{
		SetConsoleCursorPosition(h, { boardCoord.X + frame.X, boardCoord.Y + frame.Y });
		for (size_t j = 0; j < 4; j++)
		{
			if (boardCoord.Y + frame.Y==2 && boardCoord.X + frame.X+j == 35) printf("%c", 218);
			else if (boardCoord.Y + frame.Y == 2 && boardCoord.X + frame.X + j == 46) printf("%c", 191);
			else if (boardCoord.Y + frame.Y == 2) { //clears the block from the frame
				printf("%c", 196);
			}
			else if (board[boardCoord.Y][boardCoord.X + j] == 178){
				board[boardCoord.Y][boardCoord.X + j] = 0; //clears the board from the block
				printf("%c", board[boardCoord.Y][boardCoord.X + j]);
			}
			else if (boardCoord.X + j == -1 || boardCoord.X + j == 12) printf(" ");
			else if (board[boardCoord.Y][boardCoord.X + j] == 179){
				resetColor
				printf("%c", board[boardCoord.Y][boardCoord.X + j]);
			}
			else {
				SetConsoleTextAttribute(h, SETTLED_COLOR);
				printf("%c", board[boardCoord.Y][boardCoord.X + j]);
				resetColor
			}
		}
		boardCoord.Y++;
	}
	boardCoord.Y -= 4;
}

//falling mechanism
int falling(){
	getchFunc();
		if (!(speedVar % gameSpeed) && checkMovement('d')) { //block falling
			clearsBlocks();
			boardCoord.Y++;
			}
		else if (!(speedVar % gameSpeed)){ //block settling
			clearsBlocks();
			settlesBlocks(true);
			Sleep(250);
			settlesBlocks();
			choice(tetro);
			findLines();
			boardCoord.Y = 1;
			boardCoord.X = 4;
		}
		else if (!checkMovement('d') && boardCoord.Y < 3){
			gameOver();
			system("pause");
			system("cls");
			storeHighScores();
			return 1;
		}
	drawingBlocks();
	speedVar++;
	return 0;
}

//chooses and sets the block
void choice(int16_t tetro[4][4]){
	//chooses the block mechanism
	if (!blockNo) nextBlockNo = rand() % 7 + 1;
	
	blockNo = nextBlockNo;
	posSwitch = 1;
	nextBlockNo = rand() % 7 + 1;
	structArrayCopy();
}

//switches block position
void blockSwitch(){
	int16_t lastPos = posSwitch;
	if (posSwitch >= pos) posSwitch = 1;
	else posSwitch++;
	structArrayCopy();
	clearsBlocks();
	
	//checking if can fit
	if (!checkMovement('s')) {
		posSwitch = lastPos;
		structArrayCopy();
	}

	
}

//operates figures
void getchFunc(){
	if (_kbhit()){
		//controls
		uint16_t key = _getch();
		if (224 == key){
			key = _getch();
			switch (key){
			case 72:
				blockSwitch();
				break;
			case 75:	//left movement
				if (checkMovement('l')){
					clearsBlocks();
					boardCoord.X--;
					drawingBlocks();
				}
				break;
			case 77:{	//right movement
						if (checkMovement('r')){
							clearsBlocks();
							boardCoord.X++;
							drawingBlocks();
						}
			}
				break;
			case 80:	//speeds up
				swap(gameSpeed,fastSpeed);
				break;
			}
		}
	}
}

//struct to array copy
void structArrayCopy(){
	piece temp, nextTemp,switchTemp;
	for (size_t p = 0; p < 2; p++)
	{
		switch ((p)?blockNo:nextBlockNo){
		case 1:
			switchTemp = i;
			break;
		case 2:
			switchTemp = o;
			break;
		case 3:
			switchTemp = t;
			break;
		case 4:
			switchTemp = s;
			break;
		case 5:
			switchTemp = z;
			break;
		case 6:
			switchTemp = j;
			break;
		case 7:
			switchTemp = l;
			break;
		}
		(p) ? temp = switchTemp : nextTemp = switchTemp;
	}
	
	color = temp.color;
	pos = temp.pos;
	nextColor = nextTemp.color;

	for (size_t i = 0; i < 4; i++)
	{
		for (size_t j = 0; j < 4; j++)
		{
			switch (posSwitch){
			case 1:
				tetro[i][j] = temp.hor[i][j];
				break;
			case 2:
				tetro[i][j] = temp.vert[i][j];
				break;
			case 3:
				tetro[i][j] = temp.left[i][j];
				break;
			case 4:
				tetro[i][j] = temp.right[i][j];
				break;
			}
			nextTetro[i][j] = nextTemp.hor[i][j];
		}
	}
}

//checking if block can move down
bool checkMovement(char direction){
	if (direction == 'd'){ //down direction
		for (size_t i = 0; i < 4; i++){
			for (size_t j = 0; j < 4; j++){
				if (tetro[i][j] != 0 &&
					board[boardCoord.Y + i + 1][boardCoord.X + j] != 0 &&
					board[boardCoord.Y + i + 1][boardCoord.X + j] != 178) {
					return false;
				}
			}
		}
	}
	else if (direction == 'l'){ //left direction
		for (size_t i = 0; i < 4; i++){
			for (size_t j = 0; j < 4; j++){
				if (tetro[i][j] != 0 &&
					board[boardCoord.Y + i][boardCoord.X + j - 1] != 0 &&
					board[boardCoord.Y + i][boardCoord.X + j - 1] != 178) {
					return false;
				}
			}
		}
	}
	else if (direction == 'r'){ //right direction
		for (size_t i = 0; i < 4; i++){
			for (size_t j = 0; j < 4; j++){
				if (tetro[i][j] != 0 &&
					board[boardCoord.Y + i][boardCoord.X + 1 + j] != 0 &&
					board[boardCoord.Y + i][boardCoord.X + 1 + j] != 178) {
					return false;
				}
			}
		}
	}
	else if (direction == 's'){ //switch position
		for (size_t i = 0; i < 4; i++){
			for (size_t j = 0; j < 4; j++){
				if (tetro[i][j] != 0 && boardCoord.Y>3 &&
					board[boardCoord.Y + i][boardCoord.X + j] != 0 &&
					board[boardCoord.Y + i][boardCoord.X + j] != 178) {
					return false;
				}
			}
		}
	}
	return true;
}

//lines
void findLines(){
	bool lines[HEIGHT-1]{};
	for (size_t i = HEIGHT - 2; i > 4; i--)
	{
		if (board[i][1]){
			for (size_t j = 1; j < WIDTH; j++)
			{
				if (board[i][j] == 0) break;
				if (j == WIDTH - 1){
					lines[i] = true;
				}
			}
		}
	}

	linesAnimation(lines);

	int16_t pointsPerLine = 0;
	for (size_t i = 4; i <HEIGHT-1; i++)
	{
		if (lines[i]) {
			moveLines(i);
			lines[i] = false;
			pointsPerLine++;
		}
	}
	linesCount += pointsPerLine;
	points += pointsPerLine*pointsPerLine * 15;
	gameSpeed -= pointsPerLine*5;
	boardFrame();
}
void moveLines(int16_t p){
	for (size_t i = p; i > 4; i--)
	{
		for (size_t j = 1; j < WIDTH - 1; j++)
		{
			board[i][j] = 0;
			swap(board[i][j], board[i - 1][j]);
		}
	}
}
void linesAnimation(bool lines[]){
	bool goSleep = false;
	for (short i = 0; i < 3; i++)
	{
		for (short row = HEIGHT - 2; row > 4; row--)
		{
			if (lines[row]){ //erasing lines
				SetConsoleCursorPosition(h, { frame.X + 1, frame.Y + row });
				for (size_t i = 1; i < WIDTH - 1; i++) {
					printf(" ");
					goSleep = true;
				}
			}
			if (row == 5 && goSleep) Sleep(200);
		}

		for (short row = HEIGHT - 2; row > 4; row--)
		{
			if (lines[row]){ //drawing lines
				SetConsoleCursorPosition(h, { frame.X + 1, frame.Y + row });
				SetConsoleTextAttribute(h, SETTLED_COLOR);
				for (size_t i = 1; i < WIDTH - 1; i++){
					printf("%c", SETTLED);
				}
				resetColor
			}
			if (row == 5 && goSleep) Sleep(200);
		}
	}
}

//highscores

struct player{
	int16_t level;
	int16_t score;
	int16_t rating;
	char name[NAME_BUFFER];
};
player scores[10]{};

void initHighScores(){
	int16_t playerNumber = 0;
	FILE *highscores = nullptr;
	if (fopen_s(&highscores, "highscores.txt", "r")){
		return;
	}
	char buff[60];
	char parser[7];
	//clears structs
	for (size_t i = 0; i < 10; i++)
	{
		scores[i].score = 0;
	}
	while (fgets(buff, 60, highscores)){
		for (size_t i = 0; i < 6; i++)
		{
			parser[i] = buff[i];
		}
		parser[6] = '\0'; 
		
		char *start = strchr(buff, '\"');
		char *end = strchr(buff, '\n');
		int16_t size = end - start + 1;
		
		if (!strcmp("name: ", parser)){
			strcpy_s(scores[playerNumber].name, size, buff+7);
			scores[playerNumber].name[size-3] = '\0';
			//printf("name is %s\n", scores[playerNumber].name);
		}
		else if (!strcmp("level:", parser)){
			char *temp = new char[size+1];
			strcpy_s(temp, size, buff + 8);
			scores[playerNumber].level = stoi(temp, nullptr);
			//printf("level is %d\n", scores[playerNumber].level);
			delete[] temp;
		}
		else if (!strcmp("score:", parser)){
			char *temp = new char[size+1];
			strcpy_s(temp, size, buff + 8);
			scores[playerNumber].score = stoi(temp, nullptr);
			//printf("score is %d\n", scores[playerNumber].score);
			scores[playerNumber].rating = ++playerNumber;
			delete[] temp;
		}
	}
	fclose(highscores);

	for (size_t i = 0; i < 10; i++)
	{
		for (size_t i = 1; i < 10; i++)
		{
			if (scores[i - 1].score < scores[i].score)
				swap(scores[i - 1], scores[i]);
		}
	}
}

void showHighScores(){
	initHighScores();
	puts("");
	SetConsoleCursorPosition(h, { 17, 15 });
	initHighScores();
	printf("\tname\t\t\tscores\tlevel\n");
	int16_t rating = 1;
	for (short i = 0; i < 10; i++)
	{
		SetConsoleCursorPosition(h, { 17, 17+i });
		if (scores[i].score == 0) break;
		printf("%d\t%s",
			rating++,
			scores[i].name);

		if (strlen(scores[i].name) < 7) printf("\t\t\t");
		else if (strlen(scores[i].name) < 16) printf("\t\t");
		else printf("\t");

		printf("%d\t%d\n",
			scores[i].score,
			scores[i].level);
	}
	puts("");
	_getch();
}

void storeHighScores(){
	initHighScores();
	//checks if the score is for the table
	if (points < scores[9].score) return;
	
	const int16_t NAME_BUFF = 30 ;
	system("cls");
	SetConsoleCursorPosition(h, { 25, 10 });
	printf("your nickname?: ");
	cin.getline(scores[9].name, NAME_BUFF);
	scores[9].level = level;
	scores[9].score = points;
	char levelChar[5]{}, pointsChar[5]{};
	
	FILE *f = NULL;
	fopen_s(&f, "highscores.txt", "w");
	
	if (!f)
	{
		return;
	}

	for (size_t i = 0; i < 10; i++)
	{
		_itoa_s(scores[i].level, levelChar, 10);
		_itoa_s(scores[i].score, pointsChar, 10);
		char *text[] = { "\n\nname: \"", scores[i].name, "\"\nlevel: \"", 
			levelChar, "\"\nscore: \"", pointsChar, "\"" };
		
		int count = sizeof(text) / sizeof(char*);
		for (int j = 0; j < count; j++)
		{
			if (fputs(text[j], f) < 0)
			{
				fclose(f);
				return;
			}
		}
	}
	
	fclose(f);
	
}

void clearHighScores(){
	SetConsoleCursorPosition(h, { 18, 22 });
	printf("press enter to delete reset all highscores");
	SetConsoleCursorPosition(h, { 18, 23 });
	printf("\tor any other button to cancel");
	
	SetConsoleCursorPosition(h, { 18, 25 });
	if (_getch() == 13) printf("sure?");
	else {
		system("cls");
		return;
	}

	if (_getch() == 13) {
		FILE *f = NULL;
		fopen_s(&f, "highscores.txt", "w");
		fclose(f);
		printf("\t...no more highscores");
	}
	else {
		system("cls");
		return;
	}
	SetConsoleCursorPosition(h, { 0, 43 });
	system("pause");
	system("cls");
}
void name(){}
//=====DEBUG
void debugFunc(int16_t tetro[4][4], uint16_t board[HEIGHT][WIDTH]){
	SetConsoleCursorPosition(h, { 0, 30 });
	for (size_t i = 0; i < HEIGHT; i++)
	{
		for (size_t j = 0; j < WIDTH; j++)
		{
			printf("%3d ", board[i][j]);
		}
		puts("");
	}
	//system("pause");
}
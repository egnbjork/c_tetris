#include "tetris.h"
#include "structs.h"


void logo(){
	Sleep(40);
	
	system("mode con cols=80 lines=44");
	

	FILE *gameOverLogo = nullptr;
	if (fopen_s(&gameOverLogo, "logo.txt", "r")){
		perror("Error while opening file: ");
		return;
	}

	SetConsoleCursorPosition(h, { 0, 3 });
	char buff[100];

	while (fgets(buff, 100, gameOverLogo)){
		for (size_t i = 0; i < 100; i++)
		{
			if (!i || buff[i] == -52) printf("\b");
			else 
				printf("%c", buff[i]);
		}
	}
	SetConsoleCursorPosition(h, { 21, 33 });
	for (size_t i = 0; i < 25; i++)
	{
		printf(" ");
	}
	SetConsoleCursorPosition(h, { 35, 34 });
	//printf("Yevgen Berberyan");
	SetConsoleCursorPosition(h, { 0, 43 });
	fclose(gameOverLogo);
}


void gameOver(){
	Sleep(50);
	char windowSize[30];
	strcpy_s(windowSize, "mode con cols=80 lines=44");
	for (size_t i = 27; i < 35; i+=5)
	{
		windowSize[23] = i / 10 + 49;
		windowSize[24] = i % 10 + 49;
		system(windowSize);
	}

	FILE *gameOverLogo = nullptr;
	if (fopen_s(&gameOverLogo, "game_over.txt", "r")){
		perror("Error while opening file: ");
		return;
	}

	SetConsoleCursorPosition(h, { 0, 0 });
	char buff[100];

	while (fgets(buff, 100, gameOverLogo)){
		for (size_t i = 0; i < 100; i++)
		{
			switch (buff[i]){
			case'#':
			case'+':
			case'@':
				SetConsoleTextAttribute(h, YELLOW << 4 | BLACK);
				break;
			case -52:
				printf("\b"); break;
			default:
			case 32:
				SetConsoleTextAttribute(h, YELLOW << 4 | BLACK);
				break;
			}
			if (!i) printf("\b");
			else printf("%c", buff[i]);
			resetColor
		}
		Sleep(20);
	}

	fclose(gameOverLogo);
}

void cleanMenu(int16_t startWidth, int16_t width, int16_t startHeight,
	int16_t height){

	SetConsoleCursorPosition(h, { startWidth + 20, startHeight + 2 });
	printf("New game");
	SetConsoleCursorPosition(h, { startWidth + 20, startHeight + 4 });
	printf("Hightscores");
	SetConsoleCursorPosition(h, { startWidth + 20, startHeight + 6 });
	printf("Options");
	SetConsoleCursorPosition(h, { startWidth + 20, startHeight + 8 });
	printf("Exit");

}


int16_t menu(int16_t startWidth, int16_t width, int16_t startHeight,
	int16_t height){

	//hide cursor
	CONSOLE_CURSOR_INFO cci;
	cci.bVisible = false;
	cci.dwSize = 100;
	SetConsoleCursorInfo(h, &cci);
	cleanMenu(startWidth, width, startHeight, height);

	int16_t selection = 0;

	while (1){
		uint16_t key = _getch();

		if (224 == key){
			key = _getch();
			switch (key){
			case 72: //up arrow
				(selection < 1) ? selection = 4 : selection--;
				break;
			case 80:	//down arrow
				(selection > 5) ? selection = 1 : selection++;
				break;
			}
		}

		switch (selection){
		case 1:
			cleanMenu(startWidth, width, startHeight, height);
			SetConsoleCursorPosition(h, { startWidth + 20, startHeight + 2 });
			SetConsoleTextAttribute(h, RED << 4 | GREY);
			printf("New game");
			SetConsoleTextAttribute(h, GREY << 4 | BLACK);
			break;
		case 2:
			cleanMenu(startWidth, width, startHeight, height);
			SetConsoleCursorPosition(h, { startWidth + 20, startHeight + 4 });
			SetConsoleTextAttribute(h, RED << 4 | GREY);
			printf("Hightscores");
			SetConsoleTextAttribute(h, GREY << 4 | BLACK);
			break;
		case 3:
			cleanMenu(startWidth, width, startHeight, height);
			SetConsoleCursorPosition(h, { startWidth + 20, startHeight + 6 });
			SetConsoleTextAttribute(h, RED << 4 | GREY);
			printf("Options");
			SetConsoleTextAttribute(h, GREY << 4 | BLACK);
			break;
		case 4:
			cleanMenu(startWidth, width, startHeight, height);
			SetConsoleCursorPosition(h, { startWidth + 20, startHeight + 8 });
			SetConsoleTextAttribute(h, RED << 4 | GREY);
			printf("Exit");
			SetConsoleTextAttribute(h, GREY << 4 | BLACK);
			break;
		}
		if (13 == key &&selection) return selection;
	}
}

void windowSize(){
	char windowSize[30];
	system("cls");
	strcpy_s(windowSize, "mode con cols=80 lines=44");
	for (size_t i = 32; i > 15; i-=5)
	{
		windowSize[23] = i / 10 + 49;
		windowSize[24] = i % 10 + 49;
		system(windowSize);
	}
}

int16_t intro(){
	char windowSize[30];
	strcpy_s(windowSize, "mode con cols=80 lines=44");
	system(windowSize);

	SetConsoleCursorPosition(h, { 0, 43 });
	//printf("Tetris by Yevgen Berberyan");

	int16_t height = 80, width = 43, startHeight = 0, startWidth = 0;
	bool shrinking = true;
	SetConsoleTextAttribute(h, VIVIDRED);
	int16_t choice = 0;

	while (1){
		for (short i = startHeight; i < height; i++)
		{
			for (short j = startWidth; j < width; j++)
			{
				if (j == startWidth){
					SetConsoleCursorPosition(h, { i, startWidth });
					printf("%c", 219);
				}
				else if (j == width - 1){
					SetConsoleCursorPosition(h, { i, width - 1 });
					printf("%c", 219);
				}
				if (i == startHeight){
					SetConsoleCursorPosition(h, { startHeight, j });
					printf("%c", 219);
				}
				else if (i == height - 1){
					SetConsoleCursorPosition(h, { height - 1, j });
					printf("%c", 219);
				}
			}
		}

		if (shrinking && startWidth < width){
			startHeight++;
			startWidth++;
			height--;
			width--;
		}
		else if (27 == width && !choice) {
			choice = menu(startWidth, width, startHeight, height);
			shrinking = true;
			SetConsoleTextAttribute(h, VIVIDRED);
		}
		else if (!shrinking){
			startHeight--;
			startWidth--;
			height++;
			width++;
		}
		else {
			shrinking = false;
			SetConsoleTextAttribute(h, GREY << 4 | BLACK);
		}
		if (width == 44 && choice) {
			SetConsoleTextAttribute(h, BLACK << 4 | LIGHTGREY);

			return choice;
		}
		Sleep(100);
	}
}

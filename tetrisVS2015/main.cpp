#include "tetris.h"
#include "interface.h";

int main(){
	//for (size_t i = 0; i < 255; printf("%d is %c\n", i, i++)); _getch();
	srand(time(0));
	bool game = true;
	logo();
	system("pause");

	while (1){
		int16_t introSwitch = intro();
		switch (introSwitch){
		case 1:
			playAgain();
			gameInit();

			while (game){
				for (size_t i = 0; i < HEIGHT; i++)
				{
					//debugFunc(tetro, board); //DEBUG########################################
					//system("pause");

					//falls
					if (falling()) {
						game = false;
						break;
					}
				}
			}
			break;
		
		case 2:
			initHighScores();
			showHighScores();
			system("cls");
			break;
		case 3:
			clearHighScores();
			break;
		case 4:
			exit(0);
		}
		game = true;
	}

	system("pause");
	
	return 0;
}

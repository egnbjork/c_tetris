#include <iostream>
#include <stdint.h>
#include <string.h>
#include <Windows.h>


void logo();
void gameOver();
int16_t intro();
int16_t menu(int16_t startWidth, int16_t width, int16_t startHeight,
	int16_t height);
void cleanMenu(int16_t startWidth, int16_t width, int16_t startHeight,
	int16_t height);
void windowSize();
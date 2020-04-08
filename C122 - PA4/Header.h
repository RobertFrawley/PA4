#pragma once

#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <time.h>
#include <fstream>
using namespace std;

//class of the Gameworld and all functions that are in relation to the private members for this class
class GameWorld
{
private:
	char Board[5][5] = { { '\0' } };
	int xcoord, ycoord, p_check = 0, w_check = 0, g_check = 0, xcoord_OG, ycoord_OG;
public:
	GameWorld();

	void Map_Reset();

	void Player_Reset();

	void Initialize();

	void DisplayEntireWorld();

	void FindPos();

	void DisplayVisibleWorld();

	void MoveUp();

	void MoveLeft();

	void MoveRight();

	void MoveDown();

	void DeathText();

	bool HaveIWon();

	bool AmIAlive();
};

void Display_Menu();

char input();

void Intro();
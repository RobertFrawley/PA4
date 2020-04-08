#include "Header.h"

/*******************************************************************************************
* Programmer: Robert Frawley *
* Class: CptS 122, Spring, 2020; Lab Section 5 *
* Programming Assignment: PA4 *
* Date: March 4, 2020 *
* Description: This program allows the player to move along elements in a 2D array to find the gold marked 'G', avoiding the pits ('P') and the Wumpus ('W')
* along the way. *
* Note: The code does not check for ability of the player to get to the gold. *
*******************************************************************************************/
int main(void)
{
	srand(time(0));
	//char map[5][5] = { { '\0' } };

	GameWorld map;
	map.Initialize();
	char choice = '\0';
	int points = 0;
	char name[20];

	cout << "Please enter the name of the Adventurer:\n";
	cin >> name;

	Intro();

	do
	{
		choice = '\0';
		
		system("cls");
		//map.DisplayEntireWorld();
		//map.DisplayVisibleWorld();
		Display_Menu();
		choice = input();
		if (choice == 'i' || choice == 'I')
		{
			map.MoveUp();
		}
		else if (choice == 'j' || choice == 'J')
		{
			map.MoveLeft();
		}
		else if (choice == 'k' || choice == 'K')
		{
			map.MoveDown();
		}
		else if (choice == 'l' || choice == 'L')
		{
			map.MoveRight();
		}
		else if (choice == 'r' || choice == 'R')
		{
			map.Map_Reset();
			points = 0;
		}
		else if (choice == 'n' || choice == 'N')
		{
			system("cls");
			map.Map_Reset();
			points = 0;
			cout << "Please enter the name of the Adventurer:\n";
			cin >> name;
			Intro();
		}
		else if (choice == 'v' || choice == 'V')
		{
			map.DisplayVisibleWorld();
			points = points - 2;
			system("pause");
		}
		else if (choice == 'c' || choice == 'C')
		{
			map.DisplayEntireWorld();
			points = points - 5;
			system("pause");
		}

		
		if (choice == 'i' || choice == 'I' || choice == 'j' || choice == 'J' || choice == 'k' || choice == 'K' || choice == 'l' || choice == 'L')
		{
			if (map.AmIAlive() == 1)
			{
				points = points + 5;
			}
			else
			{
				system("cls");
				cout << "Game Over!\n";
				map.DeathText();

				cout << "\n\nPlay Again? (Y/N)\n";
				do
				{
					cin >> choice;
				} while (choice != 'y' && choice != 'Y' && choice != 'n' && choice != 'N');
				if (choice == 'n' || choice == 'N')
					return 0;
				else
				{
					map.Map_Reset();
					points = 0;
				}
			}

			if (map.HaveIWon() == 1)
			{
				points = points + 5;
				system("cls");
				cout << "You Have Won!\n\n";

				ofstream myfile;
				myfile.open("GameScores.txt", ios::app);
				myfile << name << " has earned " << points << " points and has retrieved the Treasure!\n";
				myfile.close();

				cout << "Play Again? (Y/N)\n";
				do
				{
					cin >> choice;
				} while (choice != 'y' && choice != 'Y' && choice != 'n' && choice != 'N');
				if (choice == 'n' || choice == 'N')
					return 0;
				else
				{
					map.Map_Reset();
					points = 0;
				}
			}
		}

	} while (choice != 'q' && choice != 'Q');

	return 0;
}
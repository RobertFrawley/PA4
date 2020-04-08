#include "Header.h"

//initializes the board and sets all values to null
GameWorld::GameWorld()
{
	for (int i = 0; i < 5; i++)
	{
		for (int j = 0; j < 5; j++)
		{
			Board[i][j] = '\0';
		}
	}

	g_check = 0, p_check = 0, w_check = 0;
}

//populates the board with pits, the Wumpus, the Gold, and the Player randomly. MAY CAUSE NO ACCESSIBLE MEANS TO REACH THE GOLD!
void GameWorld::Initialize()
{
	int x_coord, y_coord, pit_amt, player_sym, wumbus_sym, gold_sym;

	pit_amt = (rand() % (10 - 5 + 1)) + 5;

	//adds the Pits to the map
	for (int i = 0; i < pit_amt; i++)
	{
		do {
			x_coord = (rand() % (4 + 1));
			y_coord = (rand() % (4 + 1));
		} while (Board[x_coord][y_coord] != '\0');

		Board[x_coord][y_coord] = 'P';
	}

	//adds the Player Symbol to the map
	do {

		x_coord = (rand() % (4 + 1));
		y_coord = (rand() % (4 + 1));

	} while (Board[x_coord][y_coord] != '\0');

	Board[x_coord][y_coord] = 'U';

	xcoord_OG = x_coord;
	ycoord_OG = y_coord;

	//adds the Wumbus Symbol to the map
	do {
		x_coord = (rand() % (4 + 1));
		y_coord = (rand() % (4 + 1));
	} while (Board[x_coord][y_coord] != '\0');

	Board[x_coord][y_coord] = 'W';

	//adds the Gold Symbol to the map
	do {
		x_coord = (rand() % (4 + 1));
		y_coord = (rand() % (4 + 1));
	} while (Board[x_coord][y_coord] != '\0');

	Board[x_coord][y_coord] = 'G';

}

//resets the Board back into null elements, and calls the Initialize function again to recreate the random board. also resets the 3 checks in case.
void GameWorld::Map_Reset()
{
	for (int i = 0; i < 5; i++)
	{
		for (int j = 0; j < 5; j++)
		{
			Board[i][j] = '\0';
		}
	}
	Initialize();
	g_check = 0, p_check = 0, w_check = 0;
}

//resets the player to the spawn position when the board was created. Not being used in the code
void GameWorld::Player_Reset()
{
	FindPos();
	Board[ycoord][xcoord] = 'X';
	Board[ycoord_OG][xcoord_OG] = 'U';
	p_check = 0, w_check = 0, g_check = 0;
}

//displays the entire world
void GameWorld::DisplayEntireWorld()
{
	system("cls");
	
	for (int i = 0; i < 5; i++)
	{
		for (int j = 0; j < 5; j++)
		{
			if (Board[i][j] == '\0')
			{
				cout << Board[i][j] << "X  ";
			}
			else
			{
				cout << " " << Board[i][j] << "  ";
			}
		}
		cout << "\n";
	}
}

//This function searches the grid one by one until it finds the 'U', and inputs the coordinates into private members 'xcoord' and 'ycoord'
void GameWorld::FindPos()
{
	int xcenter, ycenter;

	for (int i = 0; i < 5; i++)
	{
		for (int j = 0; j < 5; j++)
		{
			if (Board[i][j] == 'U')
			{
				ycoord = i;
				xcoord = j;
			}
		}
	}
}

//searches for the U character, takes those coordinates into int values, and then performs a smaller for by for loop to display everything within a 3x3 square
//centered on the 'U'. For elements that are deemed out of bounds, special characters are used to show walls.
void GameWorld::DisplayVisibleWorld()
{

	FindPos();

	for (int i = 0; i <= 2; i++)
	{
		for (int j = 0; j <= 2; j++)
		{
			if (ycoord + (i - 1) > 4 || ycoord + (i - 1) < 0)
			{
				cout << " _  ";
			}
			else if (xcoord + (j - 1) < 0 || xcoord + (j - 1) > 4)
			{
				cout << "|   ";
			}
			else if (Board[ycoord + (i - 1)][xcoord + (j - 1)] == '\0')
			{
				cout << Board[ycoord + (i - 1)][xcoord + (j - 1)] << "X  ";
			}
			else
			{
				cout << " " << Board[ycoord + (i - 1)][xcoord + (j - 1)] << "  ";
			}
		}
		cout << "\n";
	}

	//system("pause");
}

//these four functions are self explanatory, each checks for an 'out-of-bounds' and afterwards sets the future space to 'U' and the current space to 'X'
//these four also check if a Wumpus or a Pit is in the direction of movement, and changes the 3 checks values correspondly
void GameWorld::MoveUp()
{
	FindPos();

	if (ycoord - 1 < 0)
	{
		system("cls");
		cout << "There is a wall in the way!\n";
		system("pause");
	}
	else if(Board[ycoord - 1][xcoord] == 'P')
	{
		p_check = 1;
	}
	else if (Board[ycoord - 1][xcoord] == 'W')
	{
		w_check = 1;
	}
	else if (Board[ycoord - 1][xcoord] == 'G')
	{
		g_check = 1;
	}
	else
	{
		Board[ycoord][xcoord] = 'X';
		Board[ycoord - 1][xcoord] = 'U';
	}
}

void GameWorld::MoveLeft()
{
	FindPos();

	if (xcoord - 1 < 0)
	{
		system("cls");
		cout << "There is a wall in the way!\n";
		system("pause");
	}
	else if (Board[ycoord][xcoord - 1] == 'P')
	{
		p_check = 1;
	}
	else if (Board[ycoord][xcoord - 1] == 'W')
	{
		w_check = 1;
	}
	else if (Board[ycoord][xcoord - 1] == 'G')
	{
		g_check = 1;
	}
	else
	{
		Board[ycoord][xcoord] = 'X';
		Board[ycoord][xcoord - 1] = 'U';
	}
}

void GameWorld::MoveRight()
{
	FindPos();
	
	if (xcoord + 1 > 4)
	{
		system("cls");
		cout << "There is a wall in the way!\n";
		system("pause");
	}
	else if (Board[ycoord][xcoord + 1] == 'P')
	{
		p_check = 1;
	}
	else if (Board[ycoord][xcoord + 1] == 'W')
	{
		w_check = 1;
	}
	else if (Board[ycoord][xcoord + 1] == 'G')
	{
		g_check = 1;
	}
	else
	{
		Board[ycoord][xcoord] = 'X';
		Board[ycoord][xcoord + 1] = 'U';
	}
}

void GameWorld::MoveDown()
{
	FindPos();

	if (ycoord + 1 > 4)
	{
		system("cls");
		cout << "There is a wall in the way!\n";
		system("pause");
	}
	else if (Board[ycoord + 1][xcoord] == 'P')
	{
		p_check = 1;
	}
	else if (Board[ycoord + 1][xcoord] == 'W')
	{
		w_check = 1;
	}
	else if (Board[ycoord + 1][xcoord] == 'G')
	{
		g_check = 1;
	}
	else
	{
		Board[ycoord][xcoord] = 'X';
		Board[ycoord + 1][xcoord] = 'U';
	}
}

//fancy text based on how you died
void GameWorld::DeathText()
{
	if (w_check == 1)
		cout << "You were caught by the Wumpus!";
	else if (p_check == 1)
		cout << "You fell into a pit and got stuck!";
}

//checks if the direction of movement causes the 'g_check' to increase
bool GameWorld::HaveIWon()
{
	if (g_check != 1)
	{
		return false;
	}
	else
	{
		return true;
	}
}

//checks if the direction of movement causes the 'w_check' or the 'p_check' to increase
bool GameWorld::AmIAlive()
{
	if (p_check == 1 || w_check == 1)
	{
		return false;
	}
	else
		return true;
}

//displays the menu of input options
void Display_Menu()
{
	cout << "\n\nThe 'i', 'l', 'j', and 'k' keys will movie the player up, down, left, and right, respectively\
		\nThe 'v' key can be used to display the visible landscape\nThe 'c' key can be used to display the entire landscape\
		\nThe 'r' key is to reset the game for the current player\n The 'n' key is to reset the game and choose a new player\
		\nThe 'q' key is to quit and exit the game";
}

//takes the input, validates the input, and returns
char input()
{
	char choice = '\0';

	do
	{
		choice = '\0';
		cout << "\n\n\nPlease decide on an action\n";
		cin >> choice;
		if (choice != 'i' && choice != 'I' && choice != 'j' && choice != 'J' && choice != 'k' && choice != 'K' && choice != 'l' && choice != 'L' &&\
			choice != 'r' && choice != 'R' && choice != 'n' && choice != 'N' && choice != 'v' && choice != 'V' && choice != 'c' && choice != 'C' &&\
			choice != 'q' && choice != 'Q')
		{
			cout << "\n\nInvalid Choice\n\n";
		}
	} while (choice != 'i' && choice != 'I' && choice != 'j' && choice != 'J' && choice != 'k' && choice != 'K' && choice != 'l' && choice != 'L' && \
		choice != 'r' && choice != 'R' && choice != 'n' && choice != 'N' && choice != 'v' && choice != 'V' && choice != 'c' && choice != 'C' && \
		choice != 'q' && choice != 'Q');
	
	return choice;
}

void Intro()
{
	cout << "You are an Adventurer who heard rumors of a stash of gold when drinking in a tavern. Excited, you pack up your gear and travel to the\
	location. Staring into the dark entrance of the cave, you take your first steps, when you stumble and roll down an unexpected steep decline.\
	Once you finally stop at the bottom and get your bearings, you see the piles of skeletons and rotting adventurer gear. You here the roar of a creature\
	in the distance, a Wumpus you think, and you continue your next few steps in trepidation and fear.\n";
	system("pause");
}



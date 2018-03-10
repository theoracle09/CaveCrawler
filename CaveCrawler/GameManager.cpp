#include "stdafx.h"
#include "GameManager.h"
#include <iostream> // In, out
#include <conio.h> // _getch

/****************
Initialize needed game objects
*****************/
GameManager::GameManager()
{
	// Just testing GIT bullshit
}

/****************
Houses the main game loop
Creates the level and player instances
*****************/
void GameManager::play()
{
	char playerMove;
		
	level_.load("levels/level1.txt", player_, enemies_, chests_);

	// MAIN Game loop
	while (!player_.getStatus())
	{
		level_.print(player_);

		if (checkGameStatus())
		{
			std::cout << "You win!\n";
			exit(0);
		}

		std::cout << "W/A/S/D to move. Open Inventory: I\n";
		std::cout << "Enter a command: ";

		// Pause the program and wait for player input
		playerMove = _getch();

		level_.movePlayer(playerMove, player_, chests_);
		level_.moveEnemy(enemies_);
	}

	// Player has died
	level_.print(player_);
	std::cout << "You died! Game Over!\n";
}

/****************
Checks whether or not the player has reached the X marker
*****************/
bool GameManager::checkGameStatus()
{
	// Check and see if the player has reached the X
	return level_.getPlayerReachedEnd();
}



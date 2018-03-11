#include "stdafx.h"
#include "Battle.h"
#include "Level.h"
#include "Enemy.h"
#include "Chest.h"
#include <string>
#include <fstream>
#include <iostream>
#include <random>


Level::Level()
{

}

/****************
Takes in a text file, and parses it into a vector
Also gets object locations, such as player, enemy, and chests
*****************/
void Level::load(std::string fileName, Player& player, std::vector<Enemy>& enemies, std::list<Chest>& chests)
{
	std::ifstream inputFile;
	std::string fileRow;

	inputFile.open(fileName);

	if (!inputFile)
	{
		std::cout << "Unable to open file...\n";
		exit(1);
	}

	while (getline(inputFile, fileRow))
	{
		levelData_.push_back(fileRow);
	}

	inputFile.close();

	char tile;

	// Get player position. Loop through rows
	for (unsigned int i = 0; i < levelData_.size(); i++)
	{
		// Loop through chars in row
		for (unsigned int j = 0; j < levelData_[i].size(); j++)
		{
			tile = levelData_[i][j];

			switch (tile)
			{
				case '@':
				{
					player.setPosition(j, i);
					break;
				}
				case 'E':
				{
					// TODO Get enemy name from a file of random names
					std::string enemyName = "Enemy" + std::to_string(j) + std::to_string(i);
					enemies.push_back( (Enemy((j), (i), enemyName, 100)) );
					break;
				}
				case 'C':
				{
					std::string chestName = "Chest" + std::to_string(j) + std::to_string(i);
					chests.push_back( (Chest(chestName, player)) );
				}
			}
		}
	}
}

/****************
Displays the GUI above the level, and prints the level from the levelData vector
*****************/
void Level::print(Player& player)
{
	// TODO Find a more elegant solution to clearing the screen. Yes, I know, this method shouldn't
	// be used. I know I know I know. 
	// "clears" the console
	//std::cout << std::string(100, '\n');
	system("CLS");

	// Print the HUD
	// Print top border
	const int ROW_LENGTH = levelData_[0].size();
	const int NUM_ROWS = 5;

	for (unsigned int i = 0; i < ROW_LENGTH; i++)
	{
		std::cout << "*";

		// Reached the end of the row, so cout a newline
		if (i == (ROW_LENGTH - 1))
		{
			std::cout << std::endl;
		}
	}

	// Print the middle section 
	for (unsigned int i = 0; i < NUM_ROWS; i++)
	{
		// Display the player's health in the middle of the HUD
		if (i == 2)
		{
			int playerHealth = player.getHealth();
			int digits = 0;

			std::cout << "|" << "     Health: " << playerHealth;
			
			// Calculate number of digits in player health, and check if 
			// the playerHealth is 0
			if (playerHealth > 0)
			{
				while (playerHealth)
				{
					playerHealth /= 10;
					digits++;
				}
			}
			else
			{
				// Player has died, so to display properly, set digits to 1
				digits = 1;
			}

			// Depending on the number of digits in player health, display the correct
			// number of spaces and the end char "|"
			switch (digits)
			{
				case 3:
				{

					for (int i = 0; i < (ROW_LENGTH - 18); i++)
					{
						std::cout << " ";
					}
					std::cout << "|" << std::endl;
					break;
				}
				case 2:
				{

					for (int i = 0; i < (ROW_LENGTH - 17); i++)
					{
						std::cout << " ";
					}
					std::cout << "|" << std::endl;
					break;
				}
				case 1:
				{

					for (int i = 0; i < (ROW_LENGTH - 16); i++)
					{
						std::cout << " ";
					}
					std::cout << "|" << std::endl;
					break;
				}
			}

		}
		else
		{
			// Display '|                     |' for the other lines
			std::cout << "|";
			for (int j = 0; j < (ROW_LENGTH - 2); j++)
			{
				std::cout << " ";
			}
			std::cout << "|" << std::endl;
		}
	}

	// Print the bottom line '*******************'
	for (int i = 0; i < ROW_LENGTH; i++)
	{
		std::cout << "*";

		// Reached the end of the row, so cout a newline
		if (i == (ROW_LENGTH - 1))
		{
			std::cout << std::endl;
		}
	}

	// Print the map
	for (unsigned int i = 0; i < levelData_.size(); i++)
	{
		std::cout << levelData_[i] << std::endl;
	}
}

/****************
Takes in a movement from the player (w,s,a,d) and 
passes the movement to a processor function
*****************/
void Level::movePlayer(char input, Player& player, std::list<Chest>& chests)
{
	int playerX, playerY;

	player.getPosition(playerX, playerY);

	switch (input)
	{
		case 'w':
		case 'W':
			processPlayerMove(player, playerX, playerY - 1, chests);
			break;
		case 's':
		case 'S':
			processPlayerMove(player, playerX, playerY + 1, chests);
			break;
		case 'a':
		case 'A':
			processPlayerMove(player, playerX - 1, playerY, chests);
			break;
		case 'd':
		case 'D':
			processPlayerMove(player, playerX + 1, playerY, chests);
			break;
		case 'i':
		case 'I':
			player.showInv();
			break;
		default:
			std::cout << "Please make sure to only type \"w/a/s/d/i\"\n";
			system("PAUSE");
	}
}

/****************
Receives the movement command and checks the target tile to see
if it's a viable spot to move into
*****************/
void Level::processPlayerMove(Player& player, int targetX, int targetY, std::list<Chest>& chests)
{
	int playerX, playerY;

	player.getPosition(playerX, playerY);

	// Store the char which occupies the space the player wants to go
	char newTile = getTile(targetX, targetY);

	// Check what's in that position
	switch (newTile)
	{
		case '#':
		{
			std::cout << "You ran into a wall!" << std::endl;
			system("PAUSE");
			break;
		}
		case '.':
		{
			player.setPosition(targetX, targetY);
			setTile(playerX, playerY, '.');
			setTile(targetX, targetY, '@');
			break;
		}
		case 'X':
		{
			hasPlayerReachedEnd_ = true;
			break;
		}
		case 'E':
		{
			player.takeDamage(15);
			break;
		}
		case 'C':
		{
			// Create a comparison name based on the coordinate of where the player wants to go
			std::string chestName = "Chest" + std::to_string(targetX) + std::to_string(targetY);

			// Loop through the entire Chest list, which is located in GameManager.h
			for (std::list<Chest>::iterator lit = chests.begin(); lit != chests.end(); lit++)
			{
				if ((lit->getName()) == chestName)
				{
					lit->print(player);
				}
			}
			break;
		}
	}
}

/****************
Creates a random number which corresponds to the enemy's movement command
*****************/
void Level::moveEnemy(std::vector<Enemy>& enemies)
{
	std::random_device rd; // Obtain random number from hardware
	std::mt19937 eng(rd()); // Seed the generator
	std::uniform_int_distribution<> distr(1, 4); // Define the range
	int randomNumber;
	int enemyX, enemyY;
	char input;

	// Loop through entire enemy vector
	for (unsigned int i = 0; i < enemies.size(); i++)
	{
		// Get enemy current position
		enemies[i].getPosition(enemyX, enemyY);

		// Obtain random number
		randomNumber = distr(eng); 

		// Assign enemy movement based on random number
		switch (randomNumber)
		{
			case 1:
				input = 'w';
				break;
			case 2:
				input = 's';
				break;
			case 3:
				input = 'a';
				break;
			case 4:
				input = 'd';
				break;
		}

		// Move enemy based on 'input key'
		switch (input)
		{
			case 'w':
				processEnemyMove(enemies[i], enemyX, enemyY - 1);
				break;
			case 's':
				processEnemyMove(enemies[i], enemyX, enemyY + 1);
				break;
			case 'a':
				processEnemyMove(enemies[i], enemyX - 1, enemyY);
				break;
			case 'd':
				processEnemyMove(enemies[i], enemyX + 1, enemyY);
				break;
		}

	}

}

/****************
Recieves the enemy's movement command and swaps the characters in the level data vector,
as well as updating the enemy's own location variables
*****************/
void Level::processEnemyMove(Enemy& enemy, int targetX, int targetY)
{
	int enemyX, enemyY;

	// Get enemy's current position
	enemy.getPosition(enemyX, enemyY);

	// Store the char which occupies the space the enemy wants to go
	char newTile = getTile(targetX, targetY);

	// Check what's in that position
	switch (newTile)
	{
		case '.':
			enemy.setPosition(targetX, targetY);
			setTile(enemyX, enemyY, '.');
			setTile(targetX, targetY, 'E');
			break;
	}
}

/****************
Looks at the levelData vector, and returns the character at the specified location
*****************/
char Level::getTile(int x, int y)
{
	return levelData_[y][x];
}

/****************
Recieves a location and a character, and updates the levelData vector to the new character
*****************/
void Level::setTile(int x, int y, char tile)
{
	levelData_[y][x] = tile;
}




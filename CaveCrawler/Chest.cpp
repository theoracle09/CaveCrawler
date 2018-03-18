#include "stdafx.h"
#include "Chest.h"
#include "Weapon.h"
#include "Armor.h"
#include <conio.h>	// _getch()
#include <fstream> // File IO
#include <iomanip>	// setw
#include <iostream> // cout
#include <random>
#include <sstream> // istringstream
#include <vector>
#include <random>

Chest::Chest(std::string name, Player& player)
{
	name_ = name;

	loadFile(player, "Storage/Weapons.txt", "weapons");
	loadFile(player, "Storage/Armor.txt", "armor");
}

void Chest::print(Player& player)
{

	bool isDone = false;
	const int FIELD_LENGTH = 16;	// Number of characters in each table cell
	char input;
	std::vector<int> itemIds;
	bool isVectorEmpty = true;	// Store whether the vector is empty, so as not to add to it again
	int attack = 0;

	while (!isDone)
	{
		system("CLS");
		
		int counter = 1;

		std::cout << "|-------------------------------------------------------------------------------------------|\n";
		std::cout << "|   No.   |               Name               |    Value   |   Weight   |   Attack/Defense   |\n";
		std::cout << "|-------------------------------------------------------------------------------------------|\n";
		for (std::list<BaseItem*>::iterator lit = inventory_.begin(); lit != inventory_.end(); lit++)
		{
			attack = (*lit)->getAttack();

			if (attack == 0)
			{
				attack = (*lit)->getDefense();
			}

			std::cout << "|" << std::setw(7) << counter << "  |  " 
				<< std::setw(30) << (*lit)->getName() << "  |  "
				<< std::setw(FIELD_LENGTH/2) << (*lit)->getValue() << "  |  "
				<< std::setw(FIELD_LENGTH/2) << (*lit)->getWeight() << "  |  "
				<< std::setw(FIELD_LENGTH) << attack	<< "  |\n";

			// First check if itemIds vector is empty
			if (isVectorEmpty)
			{
				// Insert item IDs into seperate vector
				itemIds.push_back((*lit)->getId());
			}

			counter++;
		}
		isVectorEmpty = false;

		std::cout << "|-------------------------------------------------------------------------------------------|\n";


		std::cout << "\n\nPress the number of the item you'd like to take.\n";
		std::cout << "(Q)-exit\n";
		std::cout << "Selection: ";
		input = _getch();

		switch (input)
		{
		case 'Q':
		case 'q':
			isDone = true;
			break;
		default:
			int intInput = input - '0';
			input--; // Minus 1 on input to match indexes
			if (intInput > itemIds.size())
			{
				std::cout << "Invalid input. Try again.\n";
				system("PAUSE");
				break;
			}
			else
			{
				// Check if number typed matches what's displayed
				for (int i = 0; i < itemIds.size(); i++)
				{
					// input - '0' converts from char to int
					if ((input - '0') == i)
					{
						std::cout << "\nAre you sure you want this item? (Y)es or (N)o\n";
						char input2;
						input2 = _getch();

						switch (input2)
						{
						case 'y':
						case 'Y':
							// Insert item into player's inventory
							// Loop through chest contents until we get to player's choice
							for (std::list<BaseItem*>::iterator lit = inventory_.begin(); lit != inventory_.end(); /**/)
							{
								// Found the item the player wants to add
								if ((*lit)->getId() == itemIds[i])
								{
									// Add item to player's inventory
									player.addItem((*lit)->getAttack(), (*lit)->getName(), (*lit)->getDesc(), (*lit)->getId(),
										(*lit)->getValue(), (*lit)->getWeight());

									// Delete item from chest. erase() returns next position in iterator
									delete *lit;
									lit = inventory_.erase(lit);

									// Delete ID from itemIds vector
									itemIds.erase(itemIds.begin() + i);
									break; // Terminate for loop
								}
								else
								{
									lit++;
								}
							}
							break;
						case 'n':
						case 'N':
							continue;
							break;

						default:
							std::cout << "Invalid input. Try again\n";
							system("PAUSE");
							break;
						}
					}
				}

				break;
			}
		}

	}
}

void Chest::loadFile(Player& player, std::string fileName, std::string itemType)
{
	std::ifstream inputFile;
	std::string fileRow;

	std::random_device rd; // Obtain random number from hardware
	std::mt19937 eng(rd()); // Seed the generator
	std::uniform_int_distribution<> distr(1, 2); // Define the range

	int numberItemsInChest = 0;	// Keep track of how many items in the chest
	const int MAX_ITEMS_CHEST = 5;	// Default: 5

									// Opens the file which houses all the weapons in the game
	inputFile.open(fileName);

	if (!inputFile)
	{
		std::cout << "Unable to open " << fileName << ". Exiting now.\n";
		exit(1);
	}

	while (getline(inputFile, fileRow))
	{
		// Check each row and make sure it doesn't include any comments (/)
		// or empty spaces, which is the NULL
		if (fileRow[0] != '/' && fileRow[0] != NULL)
		{
			std::vector<std::string> temp;
			std::istringstream ss(fileRow);
			std::string token;

			// Break the line of strings up based on the delimiter
			while (getline(ss, token, ','))
			{
				temp.push_back(token);
			}

			if (numberItemsInChest != MAX_ITEMS_CHEST)
			{
				// Get a random number to decide if the item gets added to the chest or not
				// 50-50 chance right now per item
				int randomNumber = distr(eng);
				if (randomNumber == 1)
				{
					if (itemType == "armor")
					{
						Armor* armor = new Armor(std::stoi(temp[0]), temp[1], temp[2], std::stoi(temp[3]), std::stoi(temp[4]), std::stoi(temp[5]));
						inventory_.push_back(armor);

						numberItemsInChest++;
					}
					else if (itemType == "weapons")
					{
						Weapon* weapon = new Weapon(std::stoi(temp[0]), temp[1], temp[2], std::stoi(temp[3]), std::stoi(temp[4]), std::stoi(temp[5]));
						inventory_.push_back(weapon);

						numberItemsInChest++;
					}
				}
			}
			else
			{
				// Chest has 5 items, so break out of while loop
				break;
			}
		}
	}

	inputFile.close();
}



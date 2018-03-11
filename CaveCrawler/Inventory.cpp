#include "stdafx.h"
#include "Inventory.h"
#include "Weapon.h"
#include "Armor.h"
#include <iostream>
#include <iomanip> // setw()
#include <conio.h> // _getch()
#include <vector>


Inventory::Inventory()
{
	
}

/****************
Reads from std::list and prints the user's inventory
*****************/
void Inventory::print()
{
	bool isDone = false;	// bool to control the user input loop
	char input;
	const int FIELD_LENGTH = 16;	// Number of characters in each table cell
	std::vector<int> itemIds;	// Store the item IDs which will aid in viewDetail() function

	while (!isDone)
	{
		int counter = 1;	// Variable to count the number of items in the inventory_ list
		system("CLS");
		std::cout << "Inventory:\n\n\n";

		if (inventory_.empty())
		{
			std::cout << "Nothing to show here.\n\n\n";
		}
		else
		{
			std::cout << "|-----------------------------------------------------------------------------------|\n";
			std::cout << "|   No.   |               Name               |  Equipped  |    Value   |   Weight   |\n";
			std::cout << "|-----------------------------------------------------------------------------------|\n";
			for (std::list<BaseItem*>::iterator lit = inventory_.begin(); lit != inventory_.end(); lit++)
			{
				std::cout << "|" << std::setw(7) << counter << "  |  " << std::setw(30) << (*lit)->getName() << "  |  "
					<< std::setw(8) << (*lit)->getIsEquipped() << "  |  "
					<< std::setw(FIELD_LENGTH/2) << (*lit)->getValue() << "  |  "
					<< std::setw(FIELD_LENGTH/2) << (*lit)->getWeight() << "  |\n";

				//Insert ID into vector
				itemIds.push_back((*lit)->getId());

				counter++;
			}
			std::cout << "|-----------------------------------------------------------------------------------|\n";


			std::cout << "\n\nPress the number of the item you'd like to view more details for.\n";
		}

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
				bool isWrongInput = true;

				// Minus one on input since vector index starts at 0
				input--;

				// Compare input to indexes to make sure number is actually in inv
				for (unsigned int i = 0; i < itemIds.size(); i++)
				{
					// input - '0' converts from char to int
					if ((input - '0') == i)
					{
						viewDetail(itemIds[i]);
						// Once we come back from viewDetail, we need to not print the 'input not
						// recognized' bit below. Hence the bool.
						isWrongInput = false;
					}
				}

				// Either user hit a weird key (l, u, f, whatever)
				// or, no index exists for the item they want
				if (isWrongInput)
				{
					std::cout << "Input not recognized. Try again.\n";
					system("PAUSE");
				}
		}

	}
}

/****************
Display a particular item the user wants to view
Includes additional data for the user to see
*****************/
void Inventory::viewDetail(int id)
{
	bool isDone = false;

	while (!isDone)
	{
		system("CLS");

		// Loop through list and find item player wants details on
		for (std::list<BaseItem*>::iterator lit = inventory_.begin(); lit != inventory_.end(); lit++)
		{
			// Match IDs and print all required info to screen
			if ((*lit)->getId() == id)
			{
				std::cout << "|-----------------------------------------------------------|\n";
				std::cout << "|                Detailed Item View                         |\n";
				std::cout << "|-----------------------------------------------------------|\n";
				std::cout << "|     Name:  " << std::setw(47) << std::left << (*lit)->getName() << "|\n";
				std::cout << "|     Desc:  " << std::setw(47) << std::left << (*lit)->getDesc() << "|\n";

				// Find if item is weapon or armor or neither
				if ((*lit)->getAttack() == 0)
				{
					std::cout << "|  Defense:  " << std::setw(47) << std::left << (*lit)->getDefense() << "|\n";
				}
				else if ((*lit)->getAttack() != 0)
				{
					std::cout << "|   Attack:  " << std::setw(47) << std::left << (*lit)->getAttack() << "|\n";
				}

				std::cout << "|    Value:  " << std::setw(47) << std::left << (*lit)->getValue() << "|\n";
				std::cout << "|   Weight:  " << std::setw(47) << std::left << (*lit)->getWeight() << "|\n";
				std::cout << "|-----------------------------------------------------------|\n\n";
				
				// Check if item is already equipped or not
				if (equippedWeapon_ == nullptr)
				{
					std::cout << "Press (E) to equip item.\n";
				}
				else if (equippedWeapon_->getName() == (*lit)->getName())
				{
					std::cout << (*lit)->getName() << " is equipped.\n";
				}

				std::cout << "Press (Q) to return to inventory.\n";

				char input;
				input = _getch();

				switch (input)
				{
					case 'Q':
					case 'q':
					{
						isDone = true;
						break;
					}

					case 'E':
					case 'e':
					{
						// Equip item
						equipItem(*lit);
						break;
					}

					default:
					{
						std::cout << "Input not recognized. Try again.\n";
						system("PAUSE");
					}
				}

				// No need to continue looping through for loop
				break;
			}
		}
	}
}

/****************
Adds a weapon to the inventory std::list
*****************/
void Inventory::addWeapon(int attack, std::string name, std::string desc, int id, int value, int weight)
{
	Weapon* weapon = new Weapon(attack, name, desc, id, value, weight);
	inventory_.push_back(weapon);
}

/****************
Adds an armor piece to the inventory std::list
*****************/
void Inventory::addArmor(int defense, std::string name, std::string desc, int id, int value, int weight)
{
	Armor* armor = new Armor(defense, name, desc, id, value, weight);
	inventory_.push_back(armor);
}

/****************
Once the user no longer wants the item in their inventory,
delete the item from the list, and delete the item from the heap
*****************/
void Inventory::deleteItem()
{
	// Remove item from list, and BE SURE TO delete the object from the heap
}

/****************
Equips an item from the user's inventory. Makes the equipped item
easier to work with in a battle class.
*****************/
void Inventory::equipItem(BaseItem* item)
{
	item->setIsEquipped(true);
	equippedWeapon_ = item;
}

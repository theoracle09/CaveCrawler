#pragma once
#include "BaseItem.h"
#include "Player.h"
#include <list>
#include <string>

class Chest
{
public:
	Chest(std::string name, Player& player);
	void print(Player& player);

	// Getters and Setters
	std::string getName() { return name_; };

private:
	void loadFile(Player& player, std::string fileName, std::string itemType);

	std::string name_;
	std::list<BaseItem*> inventory_;
};


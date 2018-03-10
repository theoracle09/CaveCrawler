#pragma once
#include "BaseItem.h"

class Weapon : public BaseItem
{
public:
	using BaseItem::BaseItem;
	Weapon(int attack, std::string name, std::string desc, int id, int value, int weight);

	// Getters and Setters
	int getAttack() override { return attack_; };

private:
	int attack_;
};


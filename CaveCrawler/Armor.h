#pragma once
#include "BaseItem.h"

class Armor : public BaseItem
{
public:
	using BaseItem::BaseItem;
	Armor(int defense, std::string name, std::string desc, int id, int value, int weight);

	// Getters and Setters 
	int getDefense() override { return defense_; };

private:
	int defense_;
};


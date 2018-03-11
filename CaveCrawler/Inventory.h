#pragma once
#include "BaseItem.h"
#include <list>
class Inventory
{
public:
	Inventory();
	void print();
	void viewDetail(int id);
	void addWeapon(int attack, std::string name, std::string desc, int id, int value, int weight);
	void addArmor(int defense, std::string name, std::string desc, int id, int value, int weight);
	void deleteItem();
	void equipItem(BaseItem* item);
	void unequipItem(BaseItem* equippedWeapon);

	// Getters and Setters

private:
	std::list<BaseItem*> inventory_;
	BaseItem* equippedWeapon_ = nullptr;
};


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

private:
	std::list<BaseItem*> inventory_;
};


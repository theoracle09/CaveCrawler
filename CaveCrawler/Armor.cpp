#include "stdafx.h"
#include "Armor.h"


Armor::Armor(int defense, std::string name, std::string desc, int id, int value, int weight)
	: BaseItem(name, desc, id, value, weight)
{
	defense_ = defense;
}



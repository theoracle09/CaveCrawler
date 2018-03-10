#include "stdafx.h"
#include "Weapon.h"


Weapon::Weapon(int attack, std::string name, std::string desc, int id, int value, int weight)
	: BaseItem(name, desc, id, value, weight)
{
	attack_ = attack;
}


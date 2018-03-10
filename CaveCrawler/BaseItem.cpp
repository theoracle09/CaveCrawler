#include "stdafx.h"
#include "BaseItem.h"


BaseItem::BaseItem()
{
}

BaseItem::BaseItem(std::string name, std::string desc, int id, int value, int weight)
{
	name_ = name;
	desc_ = desc;
	id_ = id;
	value_ = value;
	weight_ = weight;
}




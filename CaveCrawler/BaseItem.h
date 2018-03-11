#pragma once
#include <string>

class BaseItem
{
public:
	BaseItem();
	BaseItem(std::string name, std::string desc, int id, int value, int weight);


	// Getters and Setters
	std::string getName() { return name_; };
	std::string getDesc() { return desc_; };
	int getId() { return id_; };
	int getValue() { return value_; };
	int getWeight() { return weight_; };

	virtual int getAttack() { return 0; };
	virtual int getDefense() { return 0; };

	char getIsEquipped();
	void setIsEquipped(bool isEquipped);

private:
	std::string name_;
	std::string desc_;
	int id_;
	int value_;
	int weight_;
	bool isEquipped_ = false;
};


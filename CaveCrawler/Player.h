#pragma once
#include "BaseItem.h"
#include "Inventory.h"
#include <string>

class Player
{

public:
	Player();
	void takeDamage(int damageAmount);
	void showInv();
	void addItem(int attack, std::string name, std::string desc, int id, int value, int weight);

	// Getters and Setters
	void getPosition(int& x, int& y);
	void setPosition(int x, int y);
	int getAttack() { return inventory_.getAttack(); };
	int getHealth() { return health_;  };
	bool getStatus() { return isDead_; };
	

private:
	Inventory inventory_;
	int x_;
	int y_;
	int health_;
	bool isDead_;

};


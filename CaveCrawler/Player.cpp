#include "stdafx.h"
#include "Player.h"
#include "Weapon.h"
#include <iostream>
#include <conio.h> // _getch()



/***************************
Class constructor. Initialize private variables to default states.
****************************/
Player::Player()
{
	x_ = 0;
	y_ = 0;
	health_ = 100;
	isDead_ = false;
}

void Player::takeDamage(int damageAmount)
{
	health_ -= damageAmount;

	if (health_ <= 0) 
	{ 
		health_ = 0;
		isDead_ = true;
	}
}

void Player::showInv()
{
	inventory_.print();
}

void Player::addItem(int attack, std::string name, std::string desc, int id, int value, int weight)
{
	inventory_.addWeapon(attack, name, desc, id, value, weight);
}

void Player::getPosition(int& x, int& y)
{
	x = x_;
	y = y_;
}

void Player::setPosition(int x, int y)
{
	x_ = x;
	y_ = y;
}





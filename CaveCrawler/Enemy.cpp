#include "stdafx.h"
#include "Enemy.h"


Enemy::Enemy(int x, int y, std::string name, int health)
{
	x_ = x;
	y_ = y;
	name_ = name;
	health_ = health;
	isDead_ = false;
}

void Enemy::takeDamage(int damageAmount)
{
	health_ -= damageAmount;

	if (health_ <= 0)
	{
		health_ = 0;
		isDead_ = true;
	}
}

void Enemy::setPosition(int x, int y)
{
	x_ = x;
	y_ = y;
}

void Enemy::getPosition(int& x, int& y)
{
	x = x_;
	y = y_;
}


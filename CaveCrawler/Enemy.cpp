#include "stdafx.h"
#include "Enemy.h"


Enemy::Enemy(int x, int y, std::string name, int health)
{
	x_ = x;
	y_ = y;
	name_ = name;
	health_ = health;
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


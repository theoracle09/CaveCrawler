#pragma once
#include <string>

class Enemy
{
public:
	Enemy(int x, int y, std::string name, int health);
	~Enemy();
	void takeDamage(int damageAmount);

	// Getters and Setters

	std::string getName() { return name_; }
	void setPosition(int x, int y);
	void getPosition(int& x, int& y);
	bool getStatus() { return isDead_; };

private:
	int x_;
	int y_;
	std::string name_;
	int health_;
	bool isDead_;

};


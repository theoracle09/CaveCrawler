#pragma once
#include <string>

class Enemy
{
public:
	Enemy(int x, int y, std::string name, int health);

	// Getters and Setters

	std::string getName() { return name_; }
	void setPosition(int x, int y);
	void getPosition(int& x, int& y);

private:
	int x_;
	int y_;
	std::string name_;
	int health_;

};


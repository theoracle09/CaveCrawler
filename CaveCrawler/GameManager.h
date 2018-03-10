#pragma once
#include "BaseItem.h"
#include "Chest.h"
#include "Enemy.h"
#include "Level.h"
#include "Player.h"
#include <vector>
#include <list>



class GameManager
{
public:
	GameManager();

	void play();
	bool checkGameStatus();

	// Getters and Setters

private:
	std::vector<Enemy> enemies_;
	std::list<Chest> chests_;
	Player player_;
	Level level_;
};



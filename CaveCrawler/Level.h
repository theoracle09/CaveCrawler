#pragma once
#include "Player.h"
#include "Enemy.h"
#include "Chest.h"
#include <string>
#include <vector>
#include <list>

class Level
{

public:
	Level();
	void load(std::string file_name, Player& player, std::vector<Enemy>& enemies, std::list<Chest>& chests);
	void print(Player& player);
	void movePlayer(char input, Player& player, std::list<Chest>& chests);
	void processPlayerMove(Player& player, int targetX, int targetY, std::list<Chest>& chests);
	void moveEnemy(std::vector<Enemy>& enemies);
	void processEnemyMove(Enemy& enemy, int targetX, int targetY);

	// Getters and Setters
	char getTile(int targetX, int targetY);
	void setTile(int x, int y, char tile);
	bool getPlayerReachedEnd() { return hasPlayerReachedEnd_; }


private:
	std::vector<std::string> levelData_;
	bool hasPlayerReachedEnd_ = false;

};


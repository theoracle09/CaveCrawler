#pragma once
#include "Player.h"
#include "Enemy.h"
#include "Level.h"
#include <string>


class Battle
{
public:
	Battle();
	void MainBattle(std::string whoAttackedFirst, Player& player, Enemy& enemy, Level* level);


private:
	void playerTurn(Player& player, Enemy& enemy);
	void enemyTurn(Player& player, Enemy& enemy);
	bool isDone_ = false;
};


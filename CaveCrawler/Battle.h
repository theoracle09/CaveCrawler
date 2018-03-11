#pragma once
#include "Player.h"
#include "Enemy.h"
#include <string>


class Battle
{
public:
	Battle();
	void MainBattle(std::string whoAttackedFirst, Player& player, Enemy& enemy);


private:
	void playerTurn(Player& player, Enemy& enemy);
	void enemyTurn(Player& player, Enemy& enemy);
	bool isDone_ = false;
};


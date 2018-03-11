#include "stdafx.h"
#include "Battle.h"
#include "Player.h"
#include "Enemy.h"
#include <random>
#include <iostream>


Battle::Battle()
{
}

void Battle::MainBattle(std::string whoAttackedFirst, Player& player, Enemy& enemy)
{
	bool isFirstTurn = true;

	// Main battle loop
	while (!isDone_)
	{
		if (whoAttackedFirst == "enemy" && isFirstTurn)
		{
			enemyTurn(player, enemy);
			isFirstTurn = false;
		}

		playerTurn(player, enemy);
		enemyTurn(player, enemy);
	}
}

void Battle::playerTurn(Player& player, Enemy& enemy)
{
	int attackDamage = 0;
	int weaponAttackStatMax = player.getAttack();
	int weaponAttackStatMin = (weaponAttackStatMax * 85) / 100;	// Min is 85% of Max

	std::random_device rd; // Obtain random number from hardware
	std::mt19937 eng(rd()); // Seed the generator
	std::uniform_int_distribution<> distr(weaponAttackStatMin, weaponAttackStatMax); // Define the range

	attackDamage = distr(eng); 

	enemy.takeDamage(attackDamage);

	std::cout << "You hit the enemy for " << attackDamage << " damage!\n";
	system("PAUSE");

	// Check if enemy is dead
	if (enemy.getStatus())
	{
		std::cout << enemy.getName() << " is dead!\n";
		isDone_ = true;
		system("PAUSE");
	}
}

void Battle::enemyTurn(Player& player, Enemy& enemy)
{

}

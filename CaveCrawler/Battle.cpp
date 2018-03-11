#include "stdafx.h"
#include "Battle.h"
#include "Player.h"
#include "Enemy.h"
#include <random>
#include <iostream>


Battle::Battle()
{
}

/****************
Main battle method. 
*****************/
void Battle::MainBattle(std::string whoAttackedFirst, Player& player, Enemy& enemy, Level* level)
{
	bool isFirstTurn = true;

	// Main battle loop
	while (!isDone_)
	{
		level->print(player);

		if (whoAttackedFirst == "enemy" && isFirstTurn)
		{
			enemyTurn(player, enemy);
			isFirstTurn = false;
		}

		if (!isDone_) playerTurn(player, enemy);

		if (!isDone_) enemyTurn(player, enemy);
	}
}

void Battle::playerTurn(Player& player, Enemy& enemy)
{
	int attackDamage = 0;
	int weaponAttackStatMax = player.getAttack();
	int enemyHealth = enemy.getHealth();	// Retrieve enemy health

	// Check if player has a weapon equipped
	if (weaponAttackStatMax == 0)
	{
		isDone_ = true;
		std::cout << "\nYou don't have anything equipped!\n";
		std::cout << "Go into your inventory and equip a weapon!\n";
		system("PAUSE");
		return;
	}

	int weaponAttackStatMin = (weaponAttackStatMax * 85) / 100;	// Min is 85% of Max

	std::random_device rd; // Obtain random number from hardware
	std::mt19937 eng(rd()); // Seed the generator
	std::uniform_int_distribution<> distr(weaponAttackStatMin, weaponAttackStatMax); // Define the range

	attackDamage = distr(eng); 

	// If the enemy's health is lower than the attack damage, set the attack to be
	// equal to the amount of health remaining. This is so we don't attack an enemy with 5hp 
	// remaining for a hit of 35 or something outrageous.
	if (enemyHealth < attackDamage)
	{
		attackDamage = enemyHealth;
	}
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
	int attackDamage = 0;
	int weaponAttackStatMax = 15;
	int weaponAttackStatMin = (weaponAttackStatMax * 85) / 100;	// Min is 85% of Max
	int playerHealth = player.getHealth();

	std::random_device rd; // Obtain random number from hardware
	std::mt19937 eng(rd()); // Seed the generator
	std::uniform_int_distribution<> distr(weaponAttackStatMin, weaponAttackStatMax); // Define the range

	attackDamage = distr(eng);

	// If the player's health is lower than the attack damage, set the attack to be
	// equal to the amount of health remaining. This is so we don't attack the player with 5hp 
	// remaining for a hit of 35 or something outrageous.
	if (playerHealth < attackDamage)
	{
		attackDamage = playerHealth;
	}
	player.takeDamage(attackDamage);

	std::cout << enemy.getName()<< " hit you for " << attackDamage << " damage!\n";
	system("PAUSE");

	// Check if player has died
	if (player.getStatus())
	{
		isDone_ = true;
	}
}

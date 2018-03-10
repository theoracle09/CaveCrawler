#include "stdafx.h"
#include "GameManager.h"
#include "Menu.h"


/**********************
Main function: Primary file for program to run. Main gameplay
is handled by the GameManager class.
***********************/
int main()
{
	Menu menu;
	GameManager gameManager;

	// TODO when player dies, come back to main menu. Right now it just exits.
	// Main Menu is commented out for testing purposes
	/*do
	{
		menu.main();
	} while (!menu.getReadyStatus());*/

	gameManager.play();

    return 0;
}


#include "stdafx.h"
#include "Menu.h"
#include <iostream>


Menu::Menu()
{
}

void Menu::main()
{
	system("CLS");

	std::cout << "**************************************" << std::endl
		<< "*    ----    Cave Crawler    ----    *" << std::endl
		<< "**************************************" << std::endl
		<< "*                                    *" << std::endl
		<< "*  1. Play Game                      *" << std::endl
		<< "*  2. About                          *" << std::endl
		<< "*  3. Quit Game                      *" << std::endl
		<< "*                                    *" << std::endl
		<< "**************************************" << std::endl;

	char input;
	std::cin >> input;

	switch (input)
	{
		case '1':
			isPlayGame_ = true;
			break;
		case '2':
			about();
			break;
		case '3':
			exit(0);
			break;
		default:
			std::cout << "Wrong input. Please try again" << std::endl;
	}

}

void Menu::about()
{
	system("CLS");

	std::cout << "**************************************" << std::endl
		<< "*    ----    Cave Crawler    ----    *" << std::endl
		<< "**************************************" << std::endl
		<< "*                                    *" << std::endl
		<< "*       Created by theoracle09       *" << std::endl
		<< "*                                    *" << std::endl
		<< "*    Press any key to continue...    *" << std::endl
		<< "*                                    *" << std::endl
		<< "**************************************" << std::endl;

	char input;
	std::cin >> input;
	main();
}

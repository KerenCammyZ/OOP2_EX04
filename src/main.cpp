#include <iostream>
#include "Controller.h"
#include <SFML\Graphics.hpp>
int main()
{
	try {
		Controller game;
		game.run();
	}
	catch (const std::exception& e)
	{
		std::cerr << "Error: " << e.what() << std::endl;
		std::cout << "Press Enter to exit..." << std::endl;
		std::cin.get();
		return EXIT_FAILURE;
	}
	return EXIT_SUCCESS;
}

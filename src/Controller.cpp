#include "Controller.h"

void Controller::run()
{
	// Initialize the controller
	loadLevel("level1.txt");
	// Main loop
	while (true)
	{
		// Update the controller state
		update();
		// Handle user input
		//handleInput();
		// Render the current state
		render();
	}
}

void Controller::loadLevel(const std::string& fileName)
{
	// Load the level from the file
	std::ifstream file(fileName);
	if (!file.is_open())
	{
		throw std::runtime_error("Failed to open level file: " + fileName);
	}
	// Read the level data from the file
	std::string line;
	

	
	// Initialize the game state

	
	// Initialize the view
	
	
	// Initialize the input handler

	file.close();
}

void Controller::update()
{
}

void Controller::render()
{
	m_window.draw();
}

void Controller::handleEvents()
{

}

void Controller::handleInput()
{
	// Handle user input
}
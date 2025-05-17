#include "Controller.h"
#include "GameObject.h"


Controller::Controller() : m_window(sf::VideoMode(1000, 1100), "Xonix"), m_running(false){}

void Controller::run()
{
	// Initialize the controller
	//loadLevel("level1.txt");
	// Main loop
	while (m_window.isOpen())
	{
		// check all the window's events that were triggered since the last iteration of the loop
		sf::Event event;
		while (m_window.pollEvent(event))
		{
			// "close requested" event: we close the window
			if (event.type == sf::Event::Closed)
				m_window.close();
		}

		// clear window with black color
		m_window.clear(sf::Color::Black);

		// update the game state
		//update();

		// draw everything
		//draw();
		/*GameObject a;
		a.draw(m_window);*/
		m_board.draw(m_window);

		// end the current frame
		m_window.display();
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

	file.close();
}

void Controller::update()
{
}

void Controller::draw()
{
}

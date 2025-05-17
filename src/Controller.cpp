#include "Controller.h"
#include "GameObject.h"

int rows = 50;
int cols = 80;
int tileSize = 10; // NOTE: exists independently in class GameObject.h, must have same size.

Controller::Controller()  
: m_window(sf::VideoMode(800, 600), "Xonix"), m_running(false), m_board(rows, cols, tileSize)
{  

}

void Controller::run()
{
	while (m_window.isOpen())
	{
		// handle input
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
		// update();
		Player player;
		Enemy redEnemy1;
		Enemy redEnemy2;
		player.setPosition(sf::Vector2f(cols/2*tileSize, 0));
		redEnemy1.setPosition(sf::Vector2f(5 * tileSize, (rows-4)*tileSize));
		redEnemy2.setPosition(sf::Vector2f(2 * tileSize, 3 * tileSize));

		// draw everything
		// draw();
		m_board.draw(m_window);
		player.draw(m_window);
		redEnemy1.draw(m_window);
		redEnemy2.draw(m_window);

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

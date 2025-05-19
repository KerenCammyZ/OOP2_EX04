#include "Controller.h"
#include "GameObject.h"
#include "GlobalSizes.h"

int rows = 50;
int cols = 80;

Controller::Controller() 
	: m_window(sf::VideoMode(800, 600), "Xonix"), m_running(false), m_board{rows,cols}
{
	// Load the level manager
	LevelManager levelManager("levels.txt");
	if (!levelManager.initialize())
	{
		throw std::runtime_error("Failed to initialize level manager");
	}

	sf::Vector2u windowSize = levelManager.getWindowSize();

	// Update the window size based on the data read from the file
    m_window.create(sf::VideoMode(windowSize.x, windowSize.y), "Xonix");

	m_player.setPosition(sf::Vector2f(100, 100));
	std::cout << "Window size: " << m_window.getSize().x << "x" << m_window.getSize().y << std::endl;
}


void Controller::run()
{
	while (m_window.isOpen())
	{
		// handle input
		sf::Event event;
		while (m_window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				m_window.close();
		}

		m_deltaTime = m_clock.restart();

		// clear window with black color
		m_window.clear(sf::Color::Black);

		// update the game state
		//update();
		handleKeyPressed(event.key.code, m_deltaTime);
		// draw everything
		// draw();
		m_board.draw(m_window);
		m_player.draw(m_window);
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

void Controller::handleKeyPressed(sf::Keyboard::Key keyCode, sf::Time deltaTime)
{
	m_player.setDirection(keyCode);
	m_player.move(deltaTime);
}

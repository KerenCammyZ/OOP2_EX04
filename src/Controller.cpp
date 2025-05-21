#include <SFML\Graphics.hpp>
#include <iostream>
#include <string>
#include "Controller.h"
#include "GameObject.h"
#include "GlobalSizes.h"

int rows = 50;
int cols = 80;

Controller::Controller()
	: m_window(sf::VideoMode(800, 600), "Xonix"),
	m_running(false),
	m_board{rows,cols},
	m_levelManager("levels.txt")

{
	if (!m_levelManager.initialize()) {
		throw std::runtime_error("Failed to initialize level manager");
	}
	sf::Vector2u windowSize = m_levelManager.getWindowSize();

	// Update the window size based on the data read from the file
    m_window.create(sf::VideoMode(windowSize.x, windowSize.y), "Xonix");
	std::cout << "Window size: " << m_window.getSize().x << "x" << m_window.getSize().y << std::endl;
}


void Controller::run()
{
	waitForSpace(); // Wait for space key to be pressed before starting the game  
	LevelData levelData; // initialize struct from class LevelManager with fields: requiredPercentage, enemyCount
	m_player.setPosition(sf::Vector2f(100, 100));
	m_player.setOldPosition(m_player.getStartPosition());
	bool isLoadNextLevel = true;
	while (m_window.isOpen())
	{
		// handle input  
		sf::Event event;
		while (m_window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				m_window.close();
		}
		if (isLoadNextLevel)
		{
			// Load next level
			if (m_levelManager.loadNextLevel(levelData)) // write to levelData
			{
				m_lives = m_levelManager.getInitialLives();
				m_requiredPercentage = levelData.requiredPercentage;
				
				m_board.initializeBoard(levelData.enemyCount);
				m_board.draw(m_window);

				m_player.setPosition(sf::Vector2f(100, 100));
				isLoadNextLevel = false;
			}
		}
		m_deltaTime = m_clock.restart();

		// clear window with black color  
		m_window.clear(sf::Color::Black);
		// update the game state  
		//update(); 
		handleKeyPressed(event.key.code, m_deltaTime);
		handleCollisions();

		// draw everything  
		// draw();  
		m_board.draw(m_window);
		m_player.draw(m_window);
		// end the current frame  
		m_window.display();
	}
}

void Controller::checkBoundries(GameObject& obj) const
{
	if (obj.getLocation().x >= m_board.getCols() * tileSize  ||
		obj.getLocation().y >= m_board.getRows() * tileSize - tileSize ||
		obj.getLocation().x <= 0 ||
		obj.getLocation().y <= 0)
	{
		obj.setLocation(obj.getOldLocation());
	}
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

// wait for user to press spacebar before starting the game
void Controller::waitForSpace()
{
	while (m_window.isOpen() && !m_running)
	{
		sf::Event event;
		while (m_window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				m_window.close();
			if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Space)
				m_running = true;
		}
		m_window.clear(sf::Color::Black);
		
		// draw a "Press Space to Start" message here
		sf::Font font;
		if (!font.loadFromFile("arial.ttf")) {
			throw std::runtime_error("Failed to load font file: arial.ttf");
		}
		sf::Text text("Press Space to Start", font, 30);
		text.setFillColor(sf::Color::White);
		text.setPosition(m_window.getSize().x / 2 - text.getGlobalBounds().width / 2,
			m_window.getSize().y / 2 - text.getGlobalBounds().height / 2);
		m_window.draw(text);
		m_window.display();
	}
}

void Controller::handleCollisions()
{
	checkBoundries(m_player);
	bool collided = false;
	
	//checkPlayerGameBounds(m_player);


	if (collided)
	{
		// lose life, respawn, etc...
	}
}


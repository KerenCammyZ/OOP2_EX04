#include <SFML\Graphics.hpp>
#include <iostream>
#include <string>
#include <algorithm>  // std::min, std::max
#include "Controller.h"
#include "GameObject.h"
#include "GlobalSizes.h"


Controller::Controller()
	:
	m_window(sf::VideoMode(800, 600), "Xonix"),
	m_running(false),
	m_levelManager("levels.txt"),
	m_board() // Initialize with default constructor
{
	if (!m_levelManager.initialize()) {
		throw std::runtime_error("Failed to initialize level manager");
	}
	sf::Vector2u windowSize = m_levelManager.getWindowSize();

	// Update the window size based on the data read from the file
    m_window.create(sf::VideoMode(windowSize.x, windowSize.y), "Xonix");
	std::cout << "Window size: " << m_window.getSize().x << "x" << m_window.getSize().y << std::endl;

	int rows = m_window.getSize().y / tileSize - 4;
	int cols = m_window.getSize().x / tileSize;
	m_board = Board(rows, cols); // leave 4 tileSize space on bottom for stats
}


void Controller::run()
{
	LevelData levelData;
	m_player.setStartPosition(sf::Vector2f(100, 100));
	m_player.setOldPosition(m_player.getStartPosition());
	waitForSpace(); // Wait for space key to be pressed before starting the game  
	loadNextLevel(levelData); // Load the first level

	while (m_window.isOpen())
	{
		m_deltaTime = m_clock.restart();
		
		// handle input  
		// handleEvents()
		sf::Event event;
		while (m_window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				m_window.close();
		}
		// handle player movement
		handleKeyPressed(event.key.code, m_deltaTime);
		// --

		// update the game state  
		// update();
		m_board.update(m_deltaTime);
		handleCollisions();
		updatePlayerOutlineColor();

		if (m_player.getLives() <= 0)
		{
			loadNextLevel(levelData);
		}
		// --

		// draw everything  
		// draw();  		
		m_window.clear(sf::Color::Black); // clear window with black color  
		
		handleStats();
		m_board.draw(m_window);
		m_player.getTrail().draw(m_window);
		m_player.draw(m_window);

		m_window.display();// end the current frame  
		// --
	}
}

void Controller::loadNextLevel(LevelData& levelData)
{
	m_levelManager.loadNextLevel(levelData);
	m_player.setLives(m_levelManager.getInitialLives());
	m_requiredPercentage = levelData.requiredPercentage;

	m_board.initializeBoard(levelData.enemyCount);
	m_board.draw(m_window);

	m_player.setPosition(m_player.getStartPosition());
}

void Controller::checkBoundries(GameObject& obj) const
{
	if (obj.getPosition().x >= m_board.getCols() * tileSize - tileSize  ||
		obj.getPosition().y >= m_board.getRows() * tileSize - tileSize ||
		obj.getPosition().x <= 0 ||
		obj.getPosition().y < 0)
	{
		obj.setPosition(obj.getOldLocation());
	}
}


void Controller::handleEvents()
{
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
	
	if (keyCode == sf::Keyboard::R)
		m_board.reset();
}

// draw game stats on the screen
void Controller::handleStats()
{
	// handle stats here
	// draw lives, score, etc...
	sf::Font font;
	if (!font.loadFromFile("arial.ttf")) {
		throw std::runtime_error("Failed to load font file: arial.ttf");
	}
	int remainingLives = m_player.getLives();
	sf::Text lives("Lives: " + std::to_string(remainingLives), font, 30);
	lives.setFillColor(sf::Color::White);
	lives.setPosition(10, m_window.getSize().y - 35);
	m_window.draw(lives);
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

	for (auto& enemy : m_board.getEnemies()) 
	{
		// ememy-boundries collision
		checkBoundries(*enemy);

		// check for collisions between player and enemy
		for (const auto& trailTile : m_player.getTrail().getTiles())
		{		
			// trail-enemy collision
			if (enemy->checkCollision(*trailTile))
			{
				m_player.handleCollision(*enemy);
				break;
			}
			// player-enemy collision
			if (m_player.checkCollision(*enemy))
			{
				m_player.handleCollision(*enemy);
				break;
			}
		}
	}
	bool collided = false;
	//checkPlayerGameBounds(m_player);

	if (collided)
	{
		// lose life, respawn, etc...
	}

	// check for collisions between enemies and tiles
	handleEnemyTileCollisions();
}


// Check for collisions between enemies and tiles  
void Controller::handleEnemyTileCollisions()  
{
	for (auto& enemyPtr : m_board.getEnemies())
	{
		auto& enemy = *enemyPtr;

		sf::FloatRect bounds = enemy.getGlobalBounds();
		int rows = m_board.getRows();
		int cols = m_board.getCols();

		bool collisionHandled = false;
		{
			// Convert pixel coordinates to tile indices
			int left = std::max(0, static_cast<int>(bounds.left / tileSize));
			int right = std::min(cols - 1, static_cast<int>((bounds.left + bounds.width) / tileSize));
			int top = std::max(0, static_cast<int>(bounds.top / tileSize));
			int bottom = std::min(rows - 1, static_cast<int>((bounds.top + bounds.height) / tileSize));

			// Iterate over the tiles in the bounding box of the enemy
			for (int row = top; row <= bottom && !collisionHandled; ++row) {
				for (int col = left; col <= right && !collisionHandled; ++col) {
					auto it = m_board.find({ row, col });
					if (it != m_board.end()) {
						Tile* tilePtr = it->second.get();
						// Check if the tile is a FullTile before handling collision  
						if (dynamic_cast<FullTile*>(tilePtr) && enemy.getGlobalBounds().intersects(tilePtr->getGlobalBounds())) {

							enemy.handleCollision(*tilePtr);
							collisionHandled = true;
						}
					}
				}
			}
		}
	}
}

// Check if the player is on a filled tile and update outline color accordingly
void Controller::updatePlayerOutlineColor()
{
	
	Tile* tile = m_board.getTileAt(m_player.getPosition());
	if (tile) {
		std::cout << "player on tile type: " << static_cast<int>(tile->getType()) << std::endl;
		if (tile && tile->getType() == TileType::Full) {
			m_player.setOutlineColor(sf::Color::Black);
		}
		else {
			m_player.setOutlineColor(sf::Color::White);
		}
	} else { std::cout << "player on tile type: nullptr" << std::endl; }
}
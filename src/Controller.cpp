#include <SFML\Graphics.hpp>
#include <iostream>
#include <string>
#include <algorithm>
#include "Controller.h"
#include "GameObject.h"
#include "GlobalSizes.h"
#include <set>
#include <queue>

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

	if (!m_font.loadFromFile("arial.ttf")) {
		throw std::runtime_error("Failed to load font file: arial.ttf");
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
	m_currentLevelData = levelData; // Store the current level data

	while (m_window.isOpen())
	{
		m_deltaTime = m_clock.restart();

		if (m_deltaTime.asSeconds() > 0.1f) // Limit deltaTime to avoid too fast updates
			m_deltaTime = sf::seconds(0.016f);
		
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
		
		// Handle events like collisions, stats, etc.
		handleEvents(); 

		// update the game state  
		update();
		/*m_board.update(m_deltaTime);
		handleCollisions();
		updatePlayerState();
		handleStats();*/

		if (m_player.getLives() <= 0)
		{
			loadNextLevel(levelData);
		}

		// draw everything  		
		m_window.clear(sf::Color::Black); // clear window with black color  
		try {
			draw();
		}
		catch (const std::exception& e) {
			std::cerr << "Error during drawing: " << e.what() << std::endl;
			resetGame(); // Reset the game if an error occurs
			continue; // Skip the rest of the loop to avoid further issues
		}
		/*handleStats();
		m_board.draw(m_window);
		m_player.getTrail().draw(m_window);
		m_player.draw(m_window);*/

		m_window.display();// end the current frame  
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
	handleStats();
	handleCollisions();
}

void Controller::update()
{
	handleStats();
	m_board.update(m_deltaTime);
	updatePlayerState();
}

void Controller::draw()
{
	handleStats();
	m_board.draw(m_window);
	m_player.getTrail().draw(m_window);
	m_player.draw(m_window);
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
	int remainingLives = m_player.getLives();
	sf::Text lives("Lives: " + std::to_string(remainingLives), m_font, 30);
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
		sf::Text text("Press Space to Start", m_font, 30);
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

		bool trailHit = false;

		// check for collisions between player and enemy
		for (const auto& trailTile : m_player.getTrail().getTiles())
		{		
			// trail-enemy collision
			if (enemy->checkCollision(*trailTile))
			{
				m_player.handleCollision(*enemy);
				trailHit = true;
				break;
			}		
		}
		// player-enemy collision
		if (!trailHit && m_player.checkCollision(*enemy))
		{
			m_player.handleCollision(*enemy);
			break;
		}
	}
	bool collided = false;
	//checkPlayerGameBounds(m_player);

	if (collided)
	{
		// lose life, respawn, etc...
	}

	handleFullTileEnemyCollisions();
}


// Check for collisions between enemies and tiles  
void Controller::handleFullTileEnemyCollisions()  
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

// Check if the player is on a filled tile and update state accordingly
void Controller::updatePlayerState()
{
	Tile* tile = m_board.getTileAt(m_player.getPosition());
	if (tile->getType() == TileType::Full) {
		m_player.setOutlineColor(sf::Color::Black);
	}
	else {
		m_player.setOutlineColor(sf::Color::White);
	}

	if (m_player.checkTrailCompleted(tile->getType())) {
		std::cout << "Trail completed!" << std::endl;
		claimTerritory();
	}

	// Add a new tile to the player's trail 
	if (tile && tile->getType() == TileType::Empty) {
		auto trailTile = std::make_shared<Tile>(
			m_player.getPosition().x,
			m_player.getPosition().y,
			sf::Color::Magenta
		);
		trailTile->setPosition(m_player.getPosition());
		m_player.getTrail().addTile(trailTile);
	}
}


std::vector<std::vector<std::pair<int, int>>> Controller::findEmptyRegions()
{
	std::vector<std::vector<std::pair<int, int>>> regions;
	std::set<std::pair<int, int>> visited;

	// Find all empty tiles and group them into connected regions
	for (int row = 2; row < m_board.getRows() - 2; ++row) {
		for (int col = 2; col < m_board.getCols() - 2; ++col) {
			if (!m_board.isFilledTile(row, col) && visited.find({ row, col }) == visited.end()) {
				// Found unvisited empty tile - explore its region
				std::vector<std::pair<int, int>> region = exploreRegion(row, col, visited);
				if (!region.empty()) {
					regions.push_back(region);
				}
			}
		}
	}

	return regions;
}

std::vector<std::pair<int, int>> Controller::exploreRegion(int startRow, int startCol, std::set<std::pair<int, int>>& visited)
{
	std::vector<std::pair<int, int>> region;
	std::queue<std::pair<int, int>> toExplore;

	toExplore.push({ startRow, startCol });

	while (!toExplore.empty()) {
		auto [row, col] = toExplore.front();
		toExplore.pop();

		// Skip if already visited or out of bounds
		if (visited.find({ row, col }) != visited.end()) continue;
		if (row < 2 || row >= m_board.getRows() - 2 || col < 2 || col >= m_board.getCols() - 2) continue;
		if (m_board.isFilledTile(row, col)) continue;

		// Add to region and mark as visited
		visited.insert({ row, col });
		region.push_back({ row, col });

		// Add neighbors to explore
		toExplore.push({ row - 1, col });
		toExplore.push({ row + 1, col });
		toExplore.push({ row, col - 1 });
		toExplore.push({ row, col + 1 });
	}

	return region;
}

bool Controller::regionContainsEnemy(const std::vector<std::pair<int, int>>& region)
{
	for (const auto& enemyPtr : m_board.getEnemies()) {
		sf::Vector2f enemyPos = enemyPtr->getPosition();
		int enemyRow = static_cast<int>(enemyPos.y) / tileSize;
		int enemyCol = static_cast<int>(enemyPos.x) / tileSize;

		// Check if enemy is in this region
		for (const auto& [row, col] : region) {
			if (enemyRow == row && enemyCol == col) {
				return true;
			}
		}
	}
	return false;
}

void Controller::claimTerritory()
{
	std::cout << "=== CLAIM TERRITORY CALLED ===" << std::endl;

	// Convert trail to filled tiles (your existing code)
	const auto& trailTiles = m_player.getTrail().getTiles();
	std::cout << "Trail has " << trailTiles.size() << " tiles" << std::endl;

	for (const auto& trailTile : trailTiles) {
		sf::Vector2f pos = trailTile->getPosition();
		int row = static_cast<int>(pos.y) / tileSize;
		int col = static_cast<int>(pos.x) / tileSize;
		m_board.setTile(row, col, std::make_unique<FullTile>());
	}
	m_player.getTrail().clearTrail();

	// Find all empty regions
	auto regions = findEmptyRegions();
	std::cout << "Found " << regions.size() << " empty regions" << std::endl;

	// Fill regions that don't contain enemies
	int filledRegions = 0;
	for (size_t i = 0; i < regions.size(); ++i) {
		bool hasEnemy = regionContainsEnemy(regions[i]);
		std::cout << "Region " << i << " (size " << regions[i].size() << ") has enemy: " << (hasEnemy ? "YES" : "NO") << std::endl;

		if (!hasEnemy) {
			// Fill this region!
			for (const auto& [row, col] : regions[i]) {
				m_board.setTile(row, col, std::make_unique<FullTile>());
			}
			filledRegions++;
			std::cout << "Filled region " << i << std::endl;
		}
	}

	std::cout << "Filled " << filledRegions << " regions without enemies" << std::endl;
}

void Controller::resetGame()
{
	m_board.reset();
	m_player.reset();
	m_running = false;
	m_levelManager.reset(m_currentLevelData);
	loadNextLevel(m_currentLevelData);
}
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

	// Update the window size based on the data read from the file
	sf::Vector2u windowSize = m_levelManager.getWindowSize();
    m_window.create(sf::VideoMode(windowSize.x, windowSize.y), "Xonix");

	int rows = m_window.getSize().y / tileSize - 4;
	int cols = m_window.getSize().x / tileSize;

	m_board = Board(rows, cols); // leave 4 tileSize space on bottom for stats
	m_player.setStartPosition(sf::Vector2f(cols / 2 - tileSize, 0));
	m_player.setLives(m_levelManager.getInitialLives());
}


void Controller::run()
{
	LevelData levelData;
	
    waitScreen(std::string("Press Space to Start")); // Pass a temporary std::string object
	loadNextLevel(levelData); // Load the first level

	while (m_window.isOpen())
	{
		m_deltaTime = m_clock.restart();

		if (m_deltaTime.asSeconds() > 0.1f) // Limit deltaTime to avoid too fast updates
			m_deltaTime = sf::seconds(0.016f);
		
		handleEvents();
		update(levelData);
		draw();
	}
}

void Controller::handleEvents()
{
	sf::Event event;
	while (m_window.pollEvent(event))
	{
		if (event.type == sf::Event::Closed)
			m_window.close();
	}
	// React to key presses for player movement
	handleKeyPressed(event.key.code, m_deltaTime);
}

void Controller::update(LevelData& levelData)
{
	m_board.update(m_deltaTime);
	handleCollisions();
	updatePlayerState();

	int filledPercentage = static_cast<int>(m_board.getFilledPercentage() * 100);
	if (filledPercentage >= m_requiredPercentage)
	{
		showLevelCompleteScreen();
		loadNextLevel(levelData);
		return;
	}

	if (m_player.getLives() < 0)
	{
		m_running = false;
		waitScreen("Game Over!");
	}
}

void Controller::draw()
{
	m_window.clear(sf::Color::Black);

	handleStats();
	m_board.draw(m_window);
	m_player.getTrail().draw(m_window);
	m_player.draw(m_window);

	m_window.display();
}

void Controller::handleKeyPressed(sf::Keyboard::Key keyCode, sf::Time deltaTime)
{
	m_player.setDirection(keyCode);
	m_player.move(deltaTime);
}

void Controller::loadNextLevel(LevelData& levelData)
{
	sf::Vector2f startPosition = m_player.getStartPosition();
	m_levelManager.loadNextLevel(levelData);
	m_player.setPosition(startPosition);
	//m_player.setLives(m_levelManager.getInitialLives());
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

// draw game stats on the screen
void Controller::handleStats()
{
	int remainingLives = m_player.getLives();
	int filledPercentage = static_cast<int>(m_board.getFilledPercentage() * 100);
	int requiredPercentage = m_requiredPercentage;
	int livesSize = 20;
	int scoreSize = 18;
	float margin = 10.f;
	float verticalSpacing = 18.f;

	sf::Text lives;
	lives.setFont(m_font);
	lives.setString("Lives: " + std::to_string(remainingLives));
	lives.setCharacterSize(livesSize);
	lives.setPosition(margin, m_window.getSize().y - 2 * (livesSize + margin));

	// Lives are colored Red when player has no more left
	if (m_player.getLives() == 0)
	{
		lives.setFillColor(sf::Color::Red);
		lives.setStyle(sf::Text::Bold);
	} 
	else {
		lives.setFillColor(sf::Color::Yellow);
	}
	
	// Score text
	sf::Text scoreText;
	scoreText.setFont(m_font);
	scoreText.setString("Score: " + std::to_string(m_score));
	scoreText.setCharacterSize(scoreSize);
	scoreText.setFillColor(sf::Color::Cyan);

	scoreText.setPosition(
		lives.getPosition().x,
		lives.getPosition().y + lives.getLocalBounds().height + 8.f
	);

	// Progress bar dimensions
	float barWidth = 300.f;
	float barHeight = 32.f;
	float barBorder = 4.f;
	float barX = (m_window.getSize().x - barWidth) / 2.f;
	float barY = m_window.getSize().y - barHeight - 2 * margin;

	// Border rectangle (empty bar)
	sf::RectangleShape barBorderRect(sf::Vector2f(barWidth, barHeight));
	barBorderRect.setPosition(barX, barY);
	barBorderRect.setFillColor(sf::Color::Transparent);
	barBorderRect.setOutlineThickness(barBorder);
	barBorderRect.setOutlineColor(sf::Color::White);

	// Filled rectangle (progress)
	float fillWidth = (filledPercentage / 100.f) * barWidth;
	sf::RectangleShape barFillRect(sf::Vector2f(fillWidth, barHeight));
	barFillRect.setPosition(barX, barY);
	barFillRect.setFillColor(sf::Color::Green);

	// Progress text (centered in bar)
	sf::Text progressText;
	progressText.setFont(m_font);
	progressText.setString(std::to_string(filledPercentage) + " / " + std::to_string(requiredPercentage) + "%");
	progressText.setCharacterSize(18);
	progressText.setFillColor(sf::Color::White);
	progressText.setOutlineColor(sf::Color::Black);
	progressText.setOutlineThickness(2.f);

	sf::FloatRect textRect = progressText.getLocalBounds();
	progressText.setOrigin(textRect.left + textRect.width / 2.0f, textRect.top + textRect.height / 2.0f);
	progressText.setPosition(barX + barWidth / 2.f, barY + barHeight / 2.f);

	// Draw to window
	m_window.draw(lives);
	m_window.draw(scoreText);
	m_window.draw(barBorderRect);
	m_window.draw(barFillRect);
	m_window.draw(progressText);
}


// wait for user to press spacebar before starting the game
void Controller::waitScreen(const std::string& displayMessage)
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
		sf::Text msgText(displayMessage, m_font, 30);
		msgText.setFillColor(sf::Color::White);
		msgText.setPosition(m_window.getSize().x / 2 - msgText.getGlobalBounds().width / 2,
			m_window.getSize().y / 2 - msgText.getGlobalBounds().height / 2);
		m_window.draw(msgText);
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
	float prevPercenatge = m_board.getFilledPercentage();

	// Convert trail to filled tiles
	const auto& trailTiles = m_player.getTrail().getTiles();

	for (const auto& trailTile : trailTiles) {
		sf::Vector2f pos = trailTile->getPosition();
		int row = static_cast<int>(pos.y) / tileSize;
		int col = static_cast<int>(pos.x) / tileSize;
		m_board.setTile(row, col, std::make_unique<FullTile>());
	}
	m_player.getTrail().clearTrail();

	// Find all empty regions
	auto regions = findEmptyRegions();

	for (size_t i = 0; i < regions.size(); ++i) {
		bool hasEnemy = regionContainsEnemy(regions[i]);
		if (!hasEnemy) {
			// Fill this region!
			for (const auto& [row, col] : regions[i]) {
				m_board.setTile(row, col, std::make_unique<FullTile>());
			}
		}
	}
	float updatedPercentage = m_board.getFilledPercentage();
	int pointsPerPercent = 10;
	int percentCovered = static_cast<int>((updatedPercentage - prevPercenatge) * 100);
	m_score += percentCovered * pointsPerPercent + 1;
}

void Controller::showLevelCompleteScreen()
{
	m_window.clear(sf::Color::Black);
	sf::Text msgText("Level Complete!", m_font, 36);
	msgText.setFillColor(sf::Color::Green);
	msgText.setStyle(sf::Text::Bold);
	msgText.setPosition(
		m_window.getSize().x / 2 - msgText.getGlobalBounds().width / 2,
		m_window.getSize().y / 2 - msgText.getGlobalBounds().height / 2
	);
	m_window.draw(msgText);
	m_window.display();

	// Pause for 2 seconds
	sf::sleep(sf::seconds(2));
}
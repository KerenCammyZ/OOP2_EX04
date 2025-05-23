#include "Board.h"
#include "FullTile.h"
#include "EmptyTile.h"
#include "GlobalSizes.h"
#include <SFML/Graphics.hpp>
#include <cstdlib> // for srand and rand
#include <ctime> // for time
#include <iostream>

Board::Board() : m_rows(0), m_cols(0)
{
    // Default constructor
}

Board::Board(int rows, int cols)
    : m_rows(rows), m_cols(cols)
{
	// initializeBoard()
}

// Reset the board to its initial state (at current level)
void Board::reset()
{
    int enemyCount{ static_cast<int>(m_enemies.size()) };
	m_enemies.clear();
	m_board.clear();
    // clear() trail
	initializeBoard(enemyCount);
}

// Initialize the board with empty tiles and border tiles
// Also set the initial positions and directions of enemies
void Board::initializeBoard(int numOfEnemies=0)
{
    m_board.clear();
    m_enemies.clear();
    // set initial board state
    for (int i = 0; i < m_rows; ++i) {  
       for (int j = 0; j < m_cols; ++j) {  
           // Determine if the current tile should be a border tile  
           bool is_border_tile = (i < 2 || i >= (m_rows - 2) || j < 2 || j >= (m_cols - 2));  

           if (is_border_tile) {  
               m_board[{i, j}] = std::make_unique<FullTile>();  
           }  
           else {  
               m_board[{i, j}] = std::make_unique<EmptyTile>();  
           }  
       }  
    }

    // set enemy starting directions and positions
    for (int i = 0; i < numOfEnemies; i++)
    {
        // set random positions
        srand(static_cast<unsigned>(time(0) + i)); // for enemies
        int posX{ 2 + rand() % (m_cols - 4) };
        int posY{ 2 + rand() % (m_rows - 4) };
	    double directionX{ static_cast<float>((rand() % 2 == 0) ? -1 : 1 )};
        double directionY{ static_cast<float>((rand() % 2 == 0) ? -1 : 1 )};

        auto e = std::make_unique<Enemy>();
        
        e->setPosition(sf::Vector2f(posX * tileSize, posY * tileSize));
        e->setDirection(sf::Vector2f(directionX, directionY));        
        m_enemies.push_back(std::move(e));
    }
}

// draw all tiles and enemies using their current positions
void Board::draw(sf::RenderWindow& window) const
{
    // Draw Tiles
    for (const auto& pair : m_board) {
        const std::pair<int, int>& pos = pair.first;
        const std::unique_ptr<Tile>& tilePtr = pair.second;

        if (tilePtr) {
            tilePtr->setPosition(sf::Vector2f(
                static_cast<float>(pos.second * tileSize),
                static_cast<float>(pos.first * tileSize)
            ));
            tilePtr->draw(window);
        }
        else 
        {
			throw std::runtime_error("Null tile pointer encountered while drawing the board.");
            // This case should ideally not happen if make_unique succeeds for all.
            // std::cout << "Warning: Null tilePtr at pos (" << pos.first << "," << pos.second << ")" << std::endl;
        }
    }
    // Draw Enemies
    for (const auto& enemy : m_enemies)
    {
        enemy->draw(window);
    }
}

// Update board state
void Board::update(sf::Time deltaTime) const
{
    // update enemy positions
    for (const auto& enemy : m_enemies)
    {
        enemy->move(deltaTime);
    }
}

// Set a tile at a specific position
void Board::setTile(int row, int col, std::unique_ptr<Tile> tile)
{
    if (row >= 0 && row < m_rows && col >= 0 && col < m_cols) {
        m_board[{row, col}] = std::move(tile);
    } else {
        throw std::out_of_range("Invalid tile position");
	}
}

// Get a tile at a specific position
Tile* Board::getTileAt(const sf::Vector2f& position) const
{
	// Convert pixel coordinates to tile indices
    int row = static_cast<int>(position.y) / tileSize;
    int col = static_cast<int>(position.x) / tileSize;

	// Check if the position is within the bounds of the board
	auto it = m_board.find({ row, col });
    if (it != m_board.end()) {
        return it->second.get();
    }
	// If the position is out of bounds, return nullptr
    return nullptr;
}

// Add iterator support
Board::iterator Board::find(const std::pair<int, int>& key)
{
    return m_board.find(key);
}

Board::const_iterator Board::find(const std::pair<int, int>& key) const
{
    return m_board.find(key);
}

Board::iterator Board::end()
{
    return m_board.end();
}

Board::const_iterator Board::end() const
{
    return m_board.end();
}

#include "Board.h"
#include "FullTile.h"
#include "EmptyTile.h"
#include "GlobalSizes.h"
#include <SFML/Graphics.hpp>
#include <cstdlib>
#include <ctime>
#include <queue>
#include <iostream>

Board::Board() : m_rows(0), m_cols(0)
{
    // Default constructor
}

Board::Board(int rows, int cols)
    : m_rows(rows), m_cols(cols)
{
    // Constructor
}

void Board::reset()
{
    int enemyCount = static_cast<int>(m_enemies.size());
    m_enemies.clear();
    m_board.clear();
    initializeBoard(enemyCount);
}

void Board::initializeBoard(int numOfEnemies)
{
    m_board.clear();
    m_enemies.clear();

    // Initialize board with border tiles (filled) and interior tiles (empty)
    for (int i = 0; i < m_rows; ++i) {
        for (int j = 0; j < m_cols; ++j) {
            // Create border of filled tiles (2 tiles thick)
            bool is_border_tile = (i < 2 || i >= (m_rows - 2) || j < 2 || j >= (m_cols - 2));

            if (is_border_tile) {
                m_board[{i, j}] = std::make_unique<FullTile>();
            }
            else {
                m_board[{i, j}] = std::make_unique<EmptyTile>();
            }
        }
    }

    // Initialize enemies with random positions and directions
    static bool srandInitialized = false;
    if (!srandInitialized) {
        srand(static_cast<unsigned>(time(0)));
        srandInitialized = true;
    }

    for (int i = 0; i < numOfEnemies; i++) {
        // Random position in interior area (avoiding borders)
        int posX = 2 + rand() % (m_cols - 4);
        int posY = 2 + rand() % (m_rows - 4);

        // Random direction (diagonal movement)
        float directionX = (rand() % 2 == 0) ? -1.0f : 1.0f;
        float directionY = (rand() % 2 == 0) ? -1.0f : 1.0f;

        auto enemy = std::make_unique<Enemy>();
        enemy->setPosition(sf::Vector2f(posX * tileSize, posY * tileSize));
        enemy->setDirection(sf::Vector2f(directionX, directionY));
        m_enemies.push_back(std::move(enemy));
    }
}

void Board::draw(sf::RenderWindow& window) const
{
    // Draw all tiles
    for (const auto& pair : m_board) {
        const std::pair<int, int>& pos = pair.first;
        const std::unique_ptr<Tile>& tilePtr = pair.second;

        if (tilePtr) {
            // Set tile position based on grid coordinates
            tilePtr->setPosition(sf::Vector2f(
                static_cast<float>(pos.second * tileSize),
                static_cast<float>(pos.first * tileSize)
            ));
            tilePtr->draw(window);
        }
        else {
            throw std::runtime_error("Null tile pointer encountered while drawing the board.");
        }
    }

    // Draw all enemies
    for (const auto& enemy : m_enemies) {
        enemy->draw(window);
    }
}

void Board::update(sf::Time deltaTime) const
{
    // Update enemy positions
    for (const auto& enemy : m_enemies) {
        enemy->move(deltaTime);
    }
}

void Board::setTile(int row, int col, std::unique_ptr<Tile> tile)
{
    if (row >= 0 && row < m_rows && col >= 0 && col < m_cols) {
        m_board[{row, col}] = std::move(tile);
    }
    else {
        throw std::out_of_range("Invalid tile position");
    }
}

Tile* Board::getTileAt(const sf::Vector2f& position) const
{
    // Convert pixel coordinates to tile indices
    int row = static_cast<int>(position.y) / tileSize;
    int col = static_cast<int>(position.x) / tileSize;

    // Check if position is within bounds
    auto it = m_board.find({ row, col });
    if (it != m_board.end()) {
        return it->second.get();
    }
    return nullptr;
}

bool Board::isFilledTile(int row, int col) const
{
    auto it = m_board.find({ row, col });
    if (it != m_board.end()) {
        return it->second->getType() == TileType::Full;
    }
    return false; // Out of bounds considered not filled
}

float Board::getFilledPercentage() const
{
    int filled = 0;
    int total = m_rows * m_cols;
    for (const auto& pair : m_board) {
        if (pair.second && pair.second->getType() == TileType::Full)
            ++filled;
    }
    return total > 0 ? static_cast<float>(filled) / total : 0.f;
}
// Iterator support methods
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
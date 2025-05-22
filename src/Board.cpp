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
    // initializeBoard();
}

void Board::initializeBoard(int numOfEnemies=0)
{
    m_board.clear();
    for (int i = 0; i < m_rows; ++i) {
        for (int j = 0; j < m_cols; ++j) {
            // Determine if the current tile should be a border tile
            bool is_border_tile = (i == 0 || i == (m_rows - 1) || j == 0 || j == (m_cols - 1));

            if (is_border_tile) {
                m_board[{i, j}] = std::make_unique<FullTile>();
            }
            else {
                m_board[{i, j}] = std::make_unique<EmptyTile>();
            }
        }
    }
    // set enemy start positions
    srand(static_cast<unsigned>(time(0))); // seed random starting positions
    for (int i = 0; i < numOfEnemies; i++)
    {
        int posX{ 1 + rand() % (m_cols - 2) };
        int posY{ 1 + rand() % (m_rows - 2) };

        auto e = std::make_unique<Enemy>();
        e->setPosition(sf::Vector2f(posX * tileSize, posY * tileSize));
        m_enemies.push_back(std::move(e));
    }
}

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
        sf::Vector2f originalPos = enemy->getLocation();
        enemy->setPosition(sf::Vector2f(originalPos.x, originalPos.y));
        enemy->draw(window);
    }
    
}

void Board::setTile(int row, int col, std::unique_ptr<Tile> tile)
{
    if (row >= 0 && row < m_rows && col >= 0 && col < m_cols) {
        m_board[{row, col}] = std::move(tile);
    } else {
        throw std::out_of_range("Invalid tile position");
	}
}

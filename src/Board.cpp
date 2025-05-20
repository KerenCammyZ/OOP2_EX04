#include "Board.h"
#include "FullTile.h"
#include "EmptyTile.h"
#include <SFML/Graphics.hpp>
#include <iostream>
#include "GlobalSizes.h"

Board::Board(int rows, int cols)
    : m_rows(rows), m_cols(cols)
{
    initializeBoard();
}

void Board::initializeBoard()
{
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
}

void Board::reset(sf::RenderWindow& window)
{// Reset the board to its initial state
    initializeBoard();
    draw(window);
	std::cout << "Board reset to initial state." << std::endl;
}

void Board::draw(sf::RenderWindow& window) const
{
    int width_offset = (window.getSize().x - (m_cols * tileSize)) / 2;
    for (const auto& pair : m_board) {
        const std::pair<int, int>& pos = pair.first;
        const std::unique_ptr<Tile>& tilePtr = pair.second;

        if (tilePtr) {
            tilePtr->setPosition(sf::Vector2f(
                static_cast<float>(width_offset + pos.second * tileSize),
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
}

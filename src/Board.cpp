#include "Board.h"
#include "FullTile.h" 
#include "EmptyTile.h" 
#include <SFML/Graphics.hpp> 
#include <iostream>     

const int TILE_SIZE = 20;

Board::Board(int rows, int cols) : m_rows(rows), m_cols(cols) {
   
    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            // Determine if the current tile should be a border tile
            bool is_border_tile = (i == 0 || i == (rows - 1) || j == 0 || j == (cols - 1));

            if (is_border_tile) {
                m_board[{i, j}] = std::make_unique<FullTile>();
            }
            else {
                m_board[{i, j}] = std::make_unique<EmptyTile>();
            }
        }
    }
}

void Board::draw(sf::RenderWindow& window) const {
    for (const auto& pair : m_board) {
        const std::pair<int, int>& pos = pair.first;
        const std::unique_ptr<Tile>& tilePtr = pair.second;

        if (tilePtr) {
            tilePtr->setPosition(sf::Vector2f(static_cast<float>(pos.second * TILE_SIZE),
                static_cast<float>(pos.first * TILE_SIZE)));
            tilePtr->draw(window);
        }
        else {
            // This case should ideally not happen if make_unique succeeds for all.
            // std::cout << "Warning: Null tilePtr at pos (" << pos.first << "," << pos.second << ")" << std::endl;
        }
    }
}

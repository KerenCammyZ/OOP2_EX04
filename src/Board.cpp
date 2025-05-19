#include "Board.h"
#include "FullTile.h"
#include "EmptyTile.h"
#include <SFML/Graphics.hpp>
#include <iostream>

const int TILE_SIZE = 20;

Board::Board(int rows, int cols, int tileSize)
    : m_rows(rows), m_cols(cols), m_tileSize(tileSize)
{
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

void Board::draw(sf::RenderWindow& window) const
{
    int width_offset = (window.getSize().x - (m_cols * m_tileSize)) / 2;
    for (const auto& pair : m_board) {
        const std::pair<int, int>& pos = pair.first;
        const std::unique_ptr<Tile>& tilePtr = pair.second;

        if (tilePtr) {
            tilePtr->setPosition(sf::Vector2f(
                static_cast<float>(width_offset + pos.second * m_tileSize),
                static_cast<float>(pos.first * m_tileSize)
            ));
            tilePtr->draw(window);
        }
        else {
            // This case should ideally not happen if make_unique succeeds for all.
            // std::cout << "Warning: Null tilePtr at pos (" << pos.first << "," << pos.second << ")" << std::endl;
        }
    }
}

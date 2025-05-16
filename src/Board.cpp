#include "Board.h"
const int TILE_SIZE = 32; // Assuming each tile is 32x32 pixels

Board::Board(int rows, int cols): m_rows(rows), m_cols(cols)
{
	for (int i = 0; i < rows; ++i) 
	{
		for (int j = 0; j < cols; ++j) 
		{
			// If on the edge (top, bottom, left, or right), use FullTile
			if (i == 0 || i == rows - 1 || j == 0 || j == cols - 1)
			{
				m_board[{i, j}] = std::make_unique<FullTile>();
			}
			else
			{
				m_board[{i, j}] = std::make_unique<EmptyTile>();
			}
		}
	}
}

void Board::draw(sf::RenderWindow& window) const
{
	for (const auto& [pos, tilePtr] : m_board) 
	{
		if (tilePtr)
		{
			// Fix: Use sf::Vector2f to set position
			tilePtr->setPosition(sf::Vector2f(pos.first * TILE_SIZE, pos.second * TILE_SIZE));
			tilePtr->draw(window);
		}
	}
}

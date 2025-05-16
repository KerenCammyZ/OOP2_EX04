#pragma once
#include "FullTile.h"
#include "Tile.h"
#include "EmptyTile.h"
#include <unordered_map>
#include <functional>
#include <string>
//#include <SFML/Graphics.hpp>

namespace std {
	template <>
	struct hash<std::pair<int, int>> {
		std::size_t operator()(const std::pair<int, int>& p) const noexcept {
			return std::hash<int>()(p.first) ^ (std::hash<int>()(p.second) << 1);
		}
	};
}

class Board
{
public:
	Board(int rows, int cols);
	Board(const Board&) = default;
	void draw(sf::RenderWindow& window) const;

private:
	std::unordered_map<std::pair<int, int>, std::unique_ptr<Tile>,
		std::hash<std::pair<int, int>>> m_board;
	int m_rows;
	int m_cols;
};
#pragma once
#include "Tile.h"
#include "FullTile.h"
#include "EmptyTile.h"
#include <unordered_map>
#include <functional>
#include <string>


// Hash function for std::pair<int, int> to be used in unordered_map
// This is necessary because std::pair does not have a default hash function in the standard library.
namespace std {
    template <>
    struct hash<std::pair<int, int>> {
        std::size_t operator()(const std::pair<int, int>& p) const noexcept {
            // takes a pair of integers and combines their hashes using XOR and bit shifting
            return std::hash<int>()(p.first) ^ (std::hash<int>()(p.second) << 1);
        }
    };
}


class Board
{
public:
    Board(int rows, int cols, int tileSize);
    Board(const Board&) = default;
    void draw(sf::RenderWindow& window) const;

private:
    std::unordered_map<std::pair<int, int>, std::unique_ptr<Tile>> m_board;
    int m_rows;
    int m_cols;
    int m_tileSize;
};
/*
TODO: replace previous code with:

struct PairHash {
    std::size_t operator()(const std::pair<int, int>& p) const noexcept {
        return std::hash<int>()(p.first) ^ (std::hash<int>()(p.second) << 1);
    }
};

std::unordered_map<std::pair<int, int>, std::unique_ptr<Tile>, PairHash> m_board;


GitHub Copilot: "specializing standard library templates in the std namespace is undefined behavior;
instead, define your hash struct in your own namespace and use it in your unordered_map."
*/
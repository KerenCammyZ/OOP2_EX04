//#pragma once
//#include "Tile.h"
//#include "FullTile.h"
//#include "EmptyTile.h"
//#include "Enemy.h"
//#include <unordered_map>
//#include <functional>
//#include <string>
//
//
//// Hash function for std::pair<int, int> to be used in unordered_map
//// This is necessary because std::pair does not have a default hash function in the standard library.
//struct PairHash {
//    std::size_t operator()(const std::pair<int, int>& p) const noexcept {
//        return std::hash<int>()(p.first) ^ (std::hash<int>()(p.second) << 1);
//    }
//};
//
//
//class Board
//{
//public:
//    Board();
//    Board(int rows, int cols);
//    Board(const Board&) = default;
//    void initializeBoard(int numOfEnemies);
//    void draw(sf::RenderWindow& window) const;
//	int getRows() const { return m_rows; }
//    int getCols() const { return m_cols; }
//
//private:
//    int m_rows;
//    int m_cols;
//    std::vector<std::unique_ptr<Enemy>> m_enemies;
//    std::unordered_map<std::pair<int, int>, std::unique_ptr<Tile>, PairHash> m_board;
//};  

#pragma once
#include "Tile.h"
#include "FullTile.h"
#include "EmptyTile.h"
#include "Enemy.h"
#include <unordered_map>
#include <functional>
#include <string>


// Hash function for std::pair<int, int> to be used in unordered_map
// This is necessary because std::pair does not have a default hash function in the standard library.
struct PairHash {
    std::size_t operator()(const std::pair<int, int>& p) const noexcept {
        return std::hash<int>()(p.first) ^ (std::hash<int>()(p.second) << 1);
    }
};


class Board
{
public:
    Board();
    Board(int rows, int cols);
    // Deleted copy constructor and assignment operator
    Board(const Board&) = delete;
    Board& operator=(const Board&) = delete;
    // Default move constructor and assignment operator
    Board(Board&&) = default;
    Board& operator=(Board&&) = default;
    void initializeBoard(int numOfEnemies);
    void draw(sf::RenderWindow& window) const;
    int getRows() const { return m_rows; }
    int getCols() const { return m_cols; }

private:
    int m_rows;
    int m_cols;
    std::vector<std::unique_ptr<Enemy>> m_enemies;
    std::unordered_map<std::pair<int, int>, std::unique_ptr<Tile>, PairHash> m_board;
};
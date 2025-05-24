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

using TileMap = std::unordered_map<std::pair<int, int>, std::unique_ptr<Tile>, PairHash>;
using Enemies = std::vector<std::unique_ptr<Enemy>>;


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
    void update(sf::Time deltaTime) const;

    void setTile(int row, int col, std::unique_ptr<Tile> tile);
    Tile* getTileAt(const sf::Vector2f& position) const;

    void reset(); // reset board
    //void claimTerritory(const std::vector<std::shared_ptr<Tile>>& trail);
    bool isFilledTile(int row, int col) const;
    
    // Add iterator support      
    using iterator = TileMap::iterator;
    using const_iterator = TileMap::const_iterator;
    iterator find(const std::pair<int, int>& key);
    const_iterator find(const std::pair<int, int>& key) const;
    iterator end();
    const_iterator end() const;

    
    int getRows() const { return m_rows; }
    int getCols() const { return m_cols; }
	const Enemies& getEnemies() const { return m_enemies; }
    const TileMap& getTiles() const { return m_board; }
    float getFilledPercentage() const;
    

private:
    int m_rows;
    int m_cols;
    TileMap m_board;
    Enemies m_enemies;
};
    
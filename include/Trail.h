#pragma once
#include "Tile.h"
#include <vector>

//using ClaimedTiles = std::vector<std::shared_ptr<Tile>>;


class Trail 
{
public:
	//constructor and destructor
	Trail();
	~Trail() = default;
	
	//other functions
	void draw(sf::RenderWindow& window);
	void addTile(std::shared_ptr<Tile> tile);
	void clearTrail();

	//setters and getters
	void setSize(int size) { m_size = size; }
	int getSize() const { return m_size; }
	//const ClaimedTiles& getTiles() const { return m_tiles; }

private:
	int m_size;
	//ClaimedTiles m_tiles;
	std::vector<std::shared_ptr<Tile>> m_tiles;
};
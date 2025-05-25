#include "Trail.h"
#include <SFML\Graphics.hpp>

Trail::Trail() : m_size(0){}

void Trail::addTile(std::shared_ptr<Tile> tile)
{
	tile->setColor(sf::Color::Magenta);
	m_tiles.push_back(tile);
}

void Trail::clearTrail()
{
	m_tiles.clear();
}

void Trail::draw(sf::RenderWindow& window)
{
	if(m_tiles.empty())
		return;
	for (auto& tile : m_tiles)
	{
		window.draw(tile->getShape());
	}
}
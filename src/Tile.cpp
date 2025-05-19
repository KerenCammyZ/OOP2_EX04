#include "Tile.h"
#include <SFML/Graphics/RectangleShape.hpp> 
#include <iostream>                       


Tile::Tile()
{
    m_shape = std::make_unique<sf::RectangleShape>(sf::Vector2f(tileSize, tileSize));
}

Tile Tile::operator=(const Tile& other)
{
    if (this != &other)
    {
        GameObject::operator=(other); 
    }
    return *this;
}

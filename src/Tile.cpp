#include "Tile.h"
#include <SFML/Graphics/RectangleShape.hpp> 
#include <iostream>                       


Tile::Tile() :
    GameObject(std::make_unique<sf::RectangleShape>(sf::Vector2f(20.f, 20.f)))
{

}


Tile Tile::operator=(const Tile& other)
{
    if (this != &other)
    {
        GameObject::operator=(other); 
    }
    return *this;
}
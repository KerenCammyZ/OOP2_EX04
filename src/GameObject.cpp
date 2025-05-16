#include "GameObject.h"

//constructors and destructors  
GameObject::GameObject()  
: m_shape(std::make_unique<sf::RectangleShape>(sf::Vector2f(50.f, 50.f))) // Default to a 50x50 rectangle  
{  
   m_shape->setFillColor(sf::Color::White); // Default color  
   m_position = { 0.f, 0.f }; // Default position  
   m_startPosition = m_position;  
   m_oldPosition = m_position;  
}

GameObject::GameObject(std::unique_ptr<sf::Shape> shape)
: m_shape(std::move(shape))
{

}

//draw object on screen
void GameObject::draw(sf::RenderWindow& window)
{
window.draw(*m_shape);
}

sf::Vector2f GameObject::getLocation() const
{
return m_position;
}

sf::FloatRect GameObject::getGlobalBounds() const
{
return m_shape->getGlobalBounds();
}

sf::Vector2f GameObject::getStartPosition() const
{
return m_startPosition;
}

sf::Vector2f GameObject::getOldPosition() const
{
return m_oldPosition;
}

sf::Shape& GameObject::getShape() const
{
	 return *m_shape; 
}

void GameObject::setColor(const sf::Color& color)
{
m_shape->setFillColor(color);
}

void GameObject::setPosition(sf::Vector2f position)
{
m_shape->setPosition(position);
}

void GameObject::setStartPosition()
{
//m_shape.setPosition(50.f, 50.f);
}

void GameObject::setDrawSettings(int posRow, int posCol)
{

}

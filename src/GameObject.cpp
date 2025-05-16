#include "GameObject.h"

//constructors and destructors
GameObject::GameObject()
{
	
}

//draw object on screen
void GameObject::draw(sf::RenderWindow& window)
{
	window.draw(m_shape);
}

sf::Vector2f GameObject::getLocation() const
{
	return m_position;
}

sf::FloatRect GameObject::getGlobalBounds() const
{
	return m_shape.getGlobalBounds();
}

sf::Vector2f GameObject::getStartPosition() const
{
	return m_startPosition;
}

sf::Vector2f GameObject::getOldPosition() const
{
	return m_oldPosition;
}

sf::RectangleShape GameObject::getShape() const
{
	return m_shape;
}

void GameObject::setColor(const sf::Color& color)
{
	m_shape.setFillColor(color);
}

void GameObject::setPosition(sf::Vector2f position)
{
	m_shape.setPosition(position);
}

void GameObject::setStartPosition()
{
	//m_shape.setPosition(50.f, 50.f);
}

void GameObject::setDrawSettings(int posRow, int posCol)
{

}

#include "GameObject.h"

GameObject::GameObject(sf::Vector2f position)
	: m_position(position)
{
	m_shape.setPosition(m_position);
	m_shape.setFillColor(sf::Color::White);
	m_shape.setOutlineThickness(1.f);
	m_shape.setOutlineColor(sf::Color::Blue);
}

void GameObject::setColor(const sf::Color& color)
{
	m_shape.setFillColor(color);
}

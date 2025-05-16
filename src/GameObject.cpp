#include "GameObject.h"

//constructors and destructors  
GameObject::GameObject()  
: m_shape(std::make_unique<sf::RectangleShape>(sf::Vector2f(50.f, 50.f))) // Default to a 50x50 rectangle  
{  
   m_shape->setFillColor(sf::Color::White); // Default color 
   m_position = { 0.f, 0.f }; // Default position  
   m_startPosition = m_position;  
   m_oldPosition = m_position;  
   m_shape->setPosition(m_position);
}

GameObject::GameObject(std::unique_ptr<sf::Shape> shape)
: m_shape(std::move(shape))
{

}

GameObject::GameObject(const sf::Vector2f& position, std::unique_ptr<sf::Shape> shape)
{
    m_shape = std::move(shape); // Move the shape into the object
	m_shape->setPosition(position); // Set the position of the shape
    m_position = position; // Set the position
    m_startPosition = position; // Set the start position
    m_oldPosition = position; // Set the old position
	m_tileSize = 50.f; // Default tile size, adjust as needed
}

GameObject::GameObject(const GameObject& other)
{
	m_shape = std::make_unique<sf::RectangleShape>(*(dynamic_cast<sf::RectangleShape*>(other.m_shape.get()))); // Copy the shape
}

GameObject GameObject::operator=(const GameObject& other)
{
    if (this == &other)
        return *this;

    // Copy shape (assumes RectangleShape, adjust if you support more types)
    if (other.m_shape)
    {
        m_shape = std::make_unique<sf::RectangleShape>(
            *(dynamic_cast<sf::RectangleShape*>(other.m_shape.get()))
        );
    }
    else
    {
        m_shape.reset();
    }

    m_position = other.m_position;
    m_startPosition = other.m_startPosition;
    m_oldPosition = other.m_oldPosition;
    m_tileSize = other.m_tileSize;

    return *this;

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

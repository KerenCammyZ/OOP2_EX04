#include "GameObject.h"
#include <iostream> 

GameObject::GameObject()
    : m_shape(std::make_unique<sf::RectangleShape>(sf::Vector2f(tileSize, tileSize)))
{
    m_shape->setFillColor(sf::Color::White);
    m_position = { 0.f, 0.f };
    m_startPosition = m_position;
    m_oldPosition = m_position;
    m_shape->setPosition(m_position);
}

GameObject::GameObject(std::unique_ptr<sf::Shape> shape)
    : m_shape(std::move(shape)) {}

GameObject::GameObject(const sf::Vector2f& position, std::unique_ptr<sf::Shape> shape)
    : m_shape(std::move(shape)),
    m_position(position),
    m_startPosition(position),
    m_oldPosition(position)
{
    if (m_shape) {
        m_shape->setPosition(m_position);
    }
}


GameObject::GameObject(const GameObject& other)
    : m_shape(other.m_shape ? std::make_unique<sf::RectangleShape>(*(dynamic_cast<sf::RectangleShape*>(other.m_shape.get()))) : nullptr),
    m_position(other.m_position),
    m_startPosition(other.m_startPosition),
    m_oldPosition(other.m_oldPosition)
{
    if (m_shape) {
        m_shape->setPosition(m_position); 
    }
}

// Assignment operator
GameObject GameObject::operator=(const GameObject& other)
{
    if (this == &other)
        return *this;

    // Deep copy the shape
    if (other.m_shape) {
        // Assuming RectangleShape; more robust code would check other.m_shape's actual type
        m_shape = std::make_unique<sf::RectangleShape>(
            *(dynamic_cast<sf::RectangleShape*>(other.m_shape.get()))
        );
        if (m_shape) { // if successful
            m_shape->setPosition(other.m_position); // set its position
        }
    }
    else {
        m_shape.reset(); // If other has no shape, this one shouldn't either
    }

    m_position = other.m_position;
    m_startPosition = other.m_startPosition;
    m_oldPosition = other.m_oldPosition;

    return *this;
}

// Draw object on screen
void GameObject::draw(sf::RenderWindow& window)
{
    if (m_shape) { // Only draw if the shape exists
        window.draw(*m_shape);
    }
}

// Getters
sf::Vector2f GameObject::getLocation() const
{
    return m_position; 
}

sf::FloatRect GameObject::getGlobalBounds() const
{
    if (m_shape) {
        return m_shape->getGlobalBounds();
    }
    return sf::FloatRect(); // Return empty rect if no shape
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
    if (!m_shape) {
        throw std::runtime_error("Attempted to getShape() on a GameObject with no shape.");
    }
    return *m_shape;
}

// Setters
void GameObject::setColor(const sf::Color& color)
{
    if (m_shape) {
        m_shape->setFillColor(color);
    }
}

void GameObject::setPosition(sf::Vector2f position)
{
   
    m_position = position; 
    if (m_shape) {
        m_shape->setPosition(position);
    }
}

void GameObject::setStartPosition()
{
    // m_shape.setPosition(50.f, 50.f); // Example of what it might do
}

// Collision checking (basic AABB)
bool GameObject::checkCollision(GameObject& unknownObj) const
{
    if (m_shape && unknownObj.m_shape) {
        return m_shape->getGlobalBounds().intersects(unknownObj.getGlobalBounds());
    }
    return false; // No collision if one or both objects lack a shape
}

#include "Player.h"
#include "MovingObject.h"
#include <memory>

Player::Player()
{
	m_shape = std::make_unique<sf::RectangleShape>(sf::Vector2f(tileSize, tileSize));
	setColor(sf::Color::Magenta);
	setOutlineColor(sf::Color::Black);
	setPosition(sf::Vector2f(0, 0));
	m_lives = 3;
}

void Player::setDirection(sf::Keyboard::Key keyCode)
{
		if ((sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) ||
			(sf::Keyboard::isKeyPressed(sf::Keyboard::W)))
		{
			m_direction = sf::Vector2f(0, -1);
		}
		else if ((sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) ||
			(sf::Keyboard::isKeyPressed(sf::Keyboard::S)))
		{
			m_direction = sf::Vector2f(0, 1);
		}
		else if ((sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) ||
			(sf::Keyboard::isKeyPressed(sf::Keyboard::A)))
		{
			m_direction = sf::Vector2f(-1, 0);
		}
		else if ((sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) ||
			(sf::Keyboard::isKeyPressed(sf::Keyboard::D)))
		{
			m_direction = sf::Vector2f(1, 0);
		}
		else
		{
			m_direction = sf::Vector2f(0, 0);
		}
}

void Player::removeLife()
{
	m_lives--;
}

int Player::getLives()
{
	return m_lives;
}

void Player::setLives(int life)
{
	m_lives = life;
}

bool Player::checkTrailCompleted(TileType currentTileType)
{
	bool wasOnEmpty = m_OnEmptyTile;
	bool nowOnFilled = (currentTileType == TileType::Full);

	m_OnEmptyTile = (currentTileType != TileType::Full);
	return (wasOnEmpty && nowOnFilled);

}

void Player::handleCollision(Enemy& enemy)
{
	removeLife();
	setPosition(getStartPosition());
	getTrail().clearTrail();
	m_OnEmptyTile = false;
}

void Player::move(sf::Time deltaTime)  
{  
	m_oldPosition = m_shape->getPosition();  
	m_shape->move(m_direction * m_speed * deltaTime.asSeconds());  
	setPosition(m_shape->getPosition());  

	// Add a tile to the trail at the current position
	// 
	//  -- moved code to Controller::updatePlayerState()
	
}

void Player::reset()
{
	m_lives = 3;
	m_OnEmptyTile = false;
	setPosition(getStartPosition());
	getTrail().clearTrail();
}
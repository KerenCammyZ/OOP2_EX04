#pragma once
#include "MovingObject.h"

class Player : public MovingObject
{
public:
	Player();
	~Player() override = default;
	virtual void move(sf::Time deltaTime);

	//setters and getters
	void setDirection(sf::Keyboard::Key keyCode);
	/*void removeLife();
	int getLife();*/

	virtual void handleCollision(GameObject& unknownObj) override {};
	virtual void handleCollision(Enemy& enemy) override {};
	virtual void handleCollision(Player& player) override {};
	virtual void handleCollision(Tile& tile) override {};


private:
	//int m_life = 3;
	sf::Vector2f m_direction;
	float m_speed = 160.f;
};
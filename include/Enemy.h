#pragma once  
#include "MovingObject.h"  

class Enemy : public MovingObject  
{  
public:  
	Enemy();  

    ~Enemy() override = default; 

    virtual void move(sf::Time deltaTime) override;
	void reboundSides();
	void reboundTopBottom();

	void setSpeed(const float speed);
	void setDirection(const sf::Vector2f direction);
	float getSpeed() const;
	sf::Vector2f getDirection() const;

	virtual void handleCollision(GameObject& unknownObj) override {};
	virtual void handleCollision(Enemy& enemy) override {};
	virtual void handleCollision(Player& player) override {};
	virtual void handleCollision(Tile& tile) override {};

private:
	float m_speed = { 120.f };
	sf::Vector2f m_direction{ 1, 1 };
};

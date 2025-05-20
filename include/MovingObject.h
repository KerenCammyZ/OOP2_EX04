#pragma once
#include "GameObject.h"

class MovingObject : public GameObject
{
public:
	MovingObject();
	~MovingObject() override = default;
	virtual void move(sf::Time deltaTime) = 0;

	virtual void handleCollision(GameObject& unknownObj) override {};
	virtual void handleCollision(Enemy& enemy) override {};
	virtual void handleCollision(Player& player) override {};
	virtual void handleCollision(Boundry& boundry) override {};
	virtual void handleCollision(Tile& tile) override {};
private:

};
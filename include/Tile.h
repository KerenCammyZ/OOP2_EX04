#pragma once
#include "GameObject.h"

class Tile : public GameObject
{
public:
	Tile();
	~Tile() override = default;
	Tile operator=(const Tile& other);

	virtual void handleCollision(GameObject& unknownObj) override {};
	virtual void handleCollision(Enemy& enemy) override {};
	virtual void handleCollision(Player& player) override {};
	virtual void handleCollision(Boundry& boundry) override {};
	virtual void handleCollision(Tile& tile) override {};

private:
};
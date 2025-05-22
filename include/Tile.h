#pragma once
#include "GameObject.h"

class Tile : public GameObject
{
public:
	Tile();
	Tile(int x, int y, sf::Color color);
	~Tile() override = default;
	Tile operator=(const Tile& other);

	virtual void handleCollision(GameObject& unknownObj) override {};
	virtual void handleCollision(Enemy& enemy) override {};
	virtual void handleCollision(Player& player) override {};
	virtual void handleCollision(Tile& tile) override {};

private:
};
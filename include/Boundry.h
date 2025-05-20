#pragma once
#include "GameObject.h"

class Boundry : public GameObject
{
public:
	Boundry() = default;
	Boundry(int width, int height);

	virtual void handleCollision(GameObject& unknownObj) override {};
	virtual void handleCollision(Enemy& enemy) override {};
	virtual void handleCollision(Player& player) override {};
	virtual void handleCollision(Boundry& boundry) override {};
	virtual void handleCollision(Tile& tile) override {};

private:
	int m_width;
	int m_height;
};
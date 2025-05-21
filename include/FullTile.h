#pragma once
#include "Tile.h"
#include "Player.h"
#include "Enemy.h"

class FullTile : public Tile 
{
public:
	FullTile();
	~FullTile() override = default;

	virtual void handleCollision(GameObject& unknownObj) override {};
	virtual void handleCollision(Enemy& enemy) override {};
	virtual void handleCollision(Player& player) override {};
	virtual void handleCollision(Tile& tile) override {};

private:

};
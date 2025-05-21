#pragma once
#include "Tile.h"

class EmptyTile : public Tile
{
public:
	EmptyTile();
	~EmptyTile() override = default;
	
	virtual void handleCollision(GameObject& unknownObj) override {};
	virtual void handleCollision(Enemy& enemy) override {};
	virtual void handleCollision(Player& player) override {};
	virtual void handleCollision(Tile& tile) override {};

private:

};
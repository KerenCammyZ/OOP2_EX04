#pragma once
#include "MovingObject.h"
#include "Trail.h"

class Player : public MovingObject
{
public:
	Player();
	~Player() override = default;
	virtual void move(sf::Time deltaTime);

	//setters and getters
	void setDirection(sf::Keyboard::Key keyCode);
	void removeLife();
	int getLives();
	void setLives(int life);
	Trail& getTrail() { return m_trail; }
	bool checkTrailCompleted(TileType currentTileType);

	virtual void handleCollision(Enemy& enemy) override;
	virtual void handleCollision(GameObject& unknownObj) override {};
	virtual void handleCollision(Player& player) override {};
	virtual void handleCollision(Tile& tile) override {};

private:
	int m_lives;
	sf::Vector2f m_direction;
	float m_speed = 320.f;

	Trail m_trail;
	bool m_OnEmptyTile{ false };
};
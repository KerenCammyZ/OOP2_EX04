#include <SFML\Graphics.hpp>
class GameObject 
{
public:
	//constructor and destructor
	GameObject();
	virtual ~GameObject() {};
	//copy constructor and assignment operator (maybe not needed)

	//draw object on the screen
	void draw(sf::RenderWindow& window);
	//virtual void update(float deltaTime) = 0;
	//virtual void handleInput(int key, int action) = 0;

	//setters and getters
	sf::Vector2f getLocation() const;
	sf::FloatRect getGlobalBounds() const;
	sf::Vector2f getStartPosition() const;
	sf::Vector2f getOldPosition() const;

	void setColor(const sf::Color& color);
	void setPosition(sf::Vector2f position);
	void setStartPosition();
	void setDrawSettings(int posRow, int posCol);

	//handle collision with other game objects
	bool checkCollision(GameObject& unknownObj) const;

	//virtual void handleCollision(GameObject& unknownObj) = 0;
	//virtual void handleCollision(Enemy& enemy) {};
	//virtual void handleCollision(Player& player) {};
	
protected:
	int m_tileSize = 50; //can change later
	sf::RectangleShape m_shape;
	sf::Vector2f m_position;
	sf::Vector2f m_oldPosition;
	sf::Vector2f m_startPosition;

};
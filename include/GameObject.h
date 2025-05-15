
class GameObject 
{
public:
	GameObject();
	virtual ~GameObject();
	virtual void update(float deltaTime) = 0;
	virtual void render() = 0;
	virtual void handleInput(int key, int action) = 0;
private:

}

#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H
#include <SFML\Graphics.hpp>

class GameObject
{
protected:
	sf::Texture _texture;
	sf::Sprite _sprite;

public:
	GameObject();
	~GameObject();

	void update();
};

#endif // GAMEOBJECT_H
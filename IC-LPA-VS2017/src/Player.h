#ifndef PLAYER_H
#define PLAYER_H
#include "GameObject.h"
#include <SFML\Graphics.hpp>

class Player : public GameObject, public sf::Drawable
{
private:

public:
	Player();
	~Player();

	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
};

#endif // !PLAYER_H


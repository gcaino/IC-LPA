#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H
// -----------------------------------------
#include "GameObject.h"
#include <SFML\Graphics.hpp>
// -----------------------------------------
namespace lpa
// -----------------------------------------
{
// -----------------------------------------
typedef unsigned int uint;
// -----------------------------------------
class Character : public GameObject
{
protected:
	enum DirectionAxis
	{
		LEFT,
		RIGHT,
		UP,
		DOWN
	};
	struct Direction
	{
		DirectionAxis	_axisX;
		DirectionAxis	_axisY;
	};

	Direction		_direction;
	Direction		_prevDirection;
	sf::Vector2f	_position;
	sf::Vector2f	_prevPosition;
	float			_velocity;
	uint			_health;
	uint			_strength;
	uint			_evasion;
	uint			_level;
	bool			_alive;
	sf::Texture		_texture;
	//sf::Sprite		_sprite;

public:
	Character();
	virtual ~Character();

	//sf::Sprite		getSprite() const							{ return _sprite; }
	sf::Vector2f	getPosition() const							{ return _position; }
	void			setPosition(sf::Vector2f newPosition)		{ _position = newPosition; }
	Direction		getDirection() const						{ return _direction; }
	void			setDirection(Direction newDirection)		{ _direction = newDirection; }
	sf::Vector2f	getPrevPosition() const						{ return _prevPosition; }
	void			setPrevPosition(sf::Vector2f prevPosition)	{ _position = prevPosition; }
	bool			isAlive() const								{ return _alive; }
	void			setAlive(bool alive)						{ _alive = alive; }

	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const = 0;
	void calculateDirection();
	void rotateSprite();
};
// -----------------------------------------
}
// -----------------------------------------
#endif // GAMEOBJECT_H
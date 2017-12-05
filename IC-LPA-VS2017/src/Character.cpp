#include "Character.h"
// -----------------------------------------
namespace lpa
// -----------------------------------------
{
// -----------------------------------------
Character::Character()
	: _position(0.f, 0.f)
	, _velocity(100.f)
	, _health(50)
	, _strength(5)
	, _evasion(0)
	, _level(1)
	, _alive(false)
	//, _sprite()
	, _texture()
{
	_direction._axisX = RIGHT;
	_prevDirection._axisX = RIGHT;
}
Character::~Character()
{
}
void Character::calculateDirection()
{
	_prevDirection = _direction;

	if (_position.x > _prevPosition.x)		_direction._axisX = RIGHT;
	else if (_position.x < _prevPosition.x)	_direction._axisX = LEFT;

	if (_position.y > _prevPosition.y)		_direction._axisY = DOWN;
	else if (_position.y < _prevPosition.y)	_direction._axisY = UP;
}
void Character::rotateSprite()
{
	if (_prevDirection._axisX != _direction._axisX)
		_sprite.scale(-1,1);
}
// -----------------------------------------
}

#include "Character.h"
// -----------------------------------------
#include "Constants.h"
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
	, _texture()
	, _animatedSprite(sf::seconds(0.1f), true, false)
	, _animatedSpriteBlood(sf::seconds(0.1f), true, false)
	, _drawBlood(false)
{
	_direction._axisX = RIGHT;
	_prevDirection._axisX = RIGHT;

	_bloodTexture.loadFromFile(Constants::texturePathBlood);
	_bloodAnimation.setSpriteSheet(_bloodTexture);
	
	_bloodAnimation.addFrame(sf::IntRect(640, 0, 128, 128));
	_bloodAnimation.addFrame(sf::IntRect(0, 0, 128, 128));
	_bloodAnimation.addFrame(sf::IntRect(128, 0, 128, 128));
	_bloodAnimation.addFrame(sf::IntRect(256, 0, 128, 128));
	_bloodAnimation.addFrame(sf::IntRect(384, 0, 128, 128));
	_bloodAnimation.addFrame(sf::IntRect(512, 0, 128, 128));
	_bloodAnimation.addFrame(sf::IntRect(640, 0, 128, 128));

	_animatedSpriteBlood.setAnimation(_bloodAnimation);
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
	{
		_animatedSprite.scale(-1, 1);
	}	
}
// -----------------------------------------
}

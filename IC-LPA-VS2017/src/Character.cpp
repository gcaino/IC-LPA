#include "Character.h"
// -----------------------------------------
namespace lpa
{
	Character::Character()
		: _position()
		, _velocity(1.f)
		, _sprite()
		, _texture()
		, _isMoving(false)
	{
	}

	Character::~Character()
	{
	}

	void Character::update(sf::Time elapsedTime)
	{
		
	}

	void Character::draw(sf::RenderTarget & target, sf::RenderStates states) const
	{
		target.draw(_sprite);
	}
}

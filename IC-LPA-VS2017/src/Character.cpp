#include "Character.h"
// -----------------------------------------
namespace lpa
{
	Character::Character()
		: _position(0.f, 0.f)
		, _velocity(100.f)
		, _health(100)
		, _strength(5)
		, _isAlive(false)
		, _sprite()
		, _texture()
	{
	}

	Character::~Character()
	{
	}
}

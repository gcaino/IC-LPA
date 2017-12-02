#include "Character.h"
// -----------------------------------------
namespace lpa
{
	Character::Character()
		: _position(0.f, 0.f)
		, _velocity(100.f)
		, _health(50)
		, _strength(5)
		, _alive(false)
		, _sprite()
		, _texture()
	{
	}

	Character::~Character()
	{
	}
}

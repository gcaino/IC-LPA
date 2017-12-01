#include "Enemy.h"
// -----------------------------------------
namespace lpa
{
    Enemy::Enemy()
    {
        if (!_texture.loadFromFile("assets/textures/knight-01.png")) {}
		_sprite.setTexture(_texture);
    }

    Enemy::~Enemy()
    {
        //dtor
    }
}

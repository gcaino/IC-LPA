#include <iostream>
#include "Enemy.h"
#include "Constants.h"
// -----------------------------------------
namespace lpa
{
    Enemy::Enemy()
    {
        if (!_texture.loadFromFile(Constants::texturesPath + "orc-01.png")) {}
		_sprite.setTexture(_texture);
		//std::cout << "Create Enemy" << std::endl;
    }

    Enemy::~Enemy()
    {
		//std::cout << "Destroy Enemy" << std::endl;
    }

	void Enemy::update(sf::Time elapsedTime)
	{
		_sprite.setPosition(_position);
	}

	void Enemy::draw(sf::RenderTarget & target, sf::RenderStates states) const
	{
		target.draw(_sprite);
	}
}

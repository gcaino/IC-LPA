#include <iostream>
#include "Enemy.h"
#include "Player.h"
#include "Constants.h"
// -----------------------------------------
namespace lpa
{
	Enemy::Enemy()
    {
        if (!_texture.loadFromFile(Constants::texturesPath + "orc-01.png")) {}
		_sprite.setTexture(_texture);
		_velocity = ENEMY_VELOCITY;

		_speedAttack = ENEMY_SPEED_ATTACK;
		_timeSinceLastAttack = _clockAttack.restart();
		//std::cout << "Create Enemy" << std::endl;
    }

    Enemy::~Enemy()
    {
		//std::cout << "Destroy Enemy" << std::endl;
    }

	void Enemy::update(sf::Time elapsedTime, Player* pPlayer)
	{
		move(elapsedTime, pPlayer->getPosition());
	}

	void Enemy::draw(sf::RenderTarget & target, sf::RenderStates states) const
	{
		target.draw(_sprite);
	}

	void Enemy::move(sf::Time elapsedTime, sf::Vector2f posPlayer)
	{
		_prevPosition = _position;

		if (posPlayer.x > _position.x)
			_position.x += _velocity * elapsedTime.asSeconds();
		if (posPlayer.x < _position.x)
			_position.x -= _velocity * elapsedTime.asSeconds();
		if (posPlayer.y > _position.y)
			_position.y += _velocity * elapsedTime.asSeconds();
		if (posPlayer.y < _position.y)
			_position.y -= _velocity * elapsedTime.asSeconds();

		_sprite.setPosition(_position);
	}

	void Enemy::movePreviousPosition()
	{
		_position = _prevPosition;
		_sprite.setPosition(_position);
	}

	void Enemy::attack(Player* pPlayer)
	{
		_timeSinceLastAttack = _clockAttack.getElapsedTime();
		if (_timeSinceLastAttack > _speedAttack)
		{
			std::cout << "Enemey Attack" << std::endl;
			_clockAttack.restart();
		}
	}
}

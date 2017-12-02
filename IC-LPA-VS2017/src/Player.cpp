#include <iostream>
#include "Constants.h"
#include "Player.h"
#include "CollisionManager.h"
// -----------------------------------------
namespace lpa
{
	Player::Player()
	{
		if (!_texture.loadFromFile(Constants::texturesPath + "knight-01.png")) {}
		_sprite.setTexture(_texture);

		_alive = true;
		_speedAttack = PLAYER_SPEED_ATTACK;
		_timeSinceLastAttack = _clockAttack.restart();

		resetPosition();
		//std::cout << "Create Player" << std::endl;
	}

	Player::~Player()
	{
	}

	void Player::handlerInputs()
	{
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left) || 
			sf::Keyboard::isKeyPressed(sf::Keyboard::A))
		{
			moveLeft();
		}
		else
		{
			stopLeft();
		}

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right) ||
			sf::Keyboard::isKeyPressed(sf::Keyboard::D))
		{
			moveRigth();
		}
		else
		{
			stopRigth();
		}

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up) ||
			sf::Keyboard::isKeyPressed(sf::Keyboard::W))
		{
			moveUp();
		}
		else
		{
			stopUp();
		}

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down) ||
			sf::Keyboard::isKeyPressed(sf::Keyboard::S))
		{
			moveDown();
		}
		else
		{
			stopDown();
		}

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Return) ||
			sf::Mouse::isButtonPressed(sf::Mouse::Left))
		{
			attack();
		}
	}

	void Player::update(sf::Time elapsedTime)
	{
		move(elapsedTime);
	}

	void Player::draw(sf::RenderTarget & target, sf::RenderStates states) const
	{
		target.draw(_sprite);
	}

	void Player::resetPosition()
	{
		_position.x = Constants::WINDOW_WIDTH_MAX / 2 - _sprite.getGlobalBounds().width / 2;
		_position.y = Constants::WINDOW_HEIGHT_MAX / 2 - _sprite.getGlobalBounds().height / 2;
		_sprite.setPosition(_position);
	}

	void Player::attack()
	{
		_timeSinceLastAttack = _clockAttack.getElapsedTime();
		if (_timeSinceLastAttack > _speedAttack)
		{
			std::cout << "Player Attack" << std::endl;
			_clockAttack.restart();
		}
	}

	void Player::move(sf::Time elapsedTime)
	{
		_prevPosition = _position;

		if (_upPressed)		_position.y -= _velocity * elapsedTime.asSeconds();
		if (_downPressed)	_position.y += _velocity * elapsedTime.asSeconds();
		if (_rightPressed)	_position.x += _velocity * elapsedTime.asSeconds();
		if (_leftPressed)	_position.x -= _velocity * elapsedTime.asSeconds();

		_sprite.setPosition(_position);
	}

	void Player::movePreviousPosition()
	{
		_position = _prevPosition;
		_sprite.setPosition(_position);
	}
}

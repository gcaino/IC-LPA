#include "Constants.h"
#include "Player.h"
// -----------------------------------------
namespace lpa
{
	Player::Player()
	{
		if (!_texture.loadFromFile("assets/textures/knight-01.png")) {}
		_sprite.setTexture(_texture);
	}

	Player::~Player()
	{
	}

	void Player::handlerInputs()
	{
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
		{
			moveLeft();
		}
		else
		{
			stopLeft();
		}

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
		{
			moveRigth();
		}
		else
		{
			stopRigth();
		}

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
		{
			moveUp();
		}
		else
		{
			stopUp();
		}

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
		{
			moveDown();
		}
		else
		{
			stopDown();
		}
	}

	void Player::update(sf::Time elapsedTime)
	{
		if (_upPressed)
		{
			_position.y -= _velocity * elapsedTime.asSeconds();
		}

		if (_downPressed)
		{
			_position.y += _velocity * elapsedTime.asSeconds();
		}

		if (_rightPressed)
		{
			_position.x += _velocity * elapsedTime.asSeconds();
		}

		if (_leftPressed)
		{
			_position.x -= _velocity * elapsedTime.asSeconds();
		}

		_sprite.setPosition(_position);
	}
}
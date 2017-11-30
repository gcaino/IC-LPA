#include "Constants.h"
#include "Player.h"
// -----------------------------------------
namespace lpa
{
	Player::Player()
	{
		if (!_texture.loadFromFile("assets/textures/2_knight_.png")) {}
		_sprite.setTexture(_texture);
	}

	Player::~Player()
	{
	}

	void Player::handlerInputs()
	{
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
		{

		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
		{

		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
		{

		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
		{

		}
	}

	void Player::update(sf::Time elapsedTime)
	{

	}
}
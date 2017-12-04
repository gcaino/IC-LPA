#include "Player.h"
// -----------------------------------------
#include "CollisionManager.h"
#include "Constants.h"
#include "Enemy.h"
#include "Wave.h"
#include <iostream>
// -----------------------------------------
namespace lpa
// -----------------------------------------
{
// -----------------------------------------
using namespace Constants;
// -----------------------------------------
Player::Player()
	: PLAYER_SPEED_ATTACK(sf::seconds(0.5f))
	, PLAYER_START_HEALTH(200)
	, _attacking(false)
	, _moving(false)
{
	_texture.loadFromFile(texturePathPlayer);
	_sprite.setTexture(_texture);
	_sprite.setOrigin(_sprite.getGlobalBounds().width / 2, _sprite.getGlobalBounds().height);
	_health = PLAYER_START_HEALTH;
	_speedAttack = PLAYER_SPEED_ATTACK;
	_alive = true;
	_timeSinceLastAttack = _clockAttack.restart();
	resetPosition();
	//std::cout << "Create Player" << std::endl;
}
Player::~Player()
{
}
void Player::handlerInputs()
{
	if (!_alive)
		return;

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
}
void Player::handlerInputsAttack(Wave* pWave, const sf::RenderWindow& window)
{
	if (sf::Mouse::isButtonPressed(sf::Mouse::Left) ||
		sf::Keyboard::isKeyPressed(sf::Keyboard::Return))
	{
		_attacking = true;
	}
	else
	{
		_attacking = false;
	}
}
void Player::update(sf::Time elapsedTime)
{
	move(elapsedTime);
	calculateDirection();
}
void Player::draw(sf::RenderTarget & target, sf::RenderStates states) const
{
	target.draw(_sprite);
}
void Player::resetPosition()
{
	_position.x = WINDOW_WIDTH_MAX / 2;
	_position.y = WINDOW_HEIGHT_MAX / 2 + _sprite.getGlobalBounds().height / 2;
	_sprite.setPosition(_position);
}
void Player::attack(Enemy* enemy, sf::Vector2i targetCoords)
{
	_timeSinceLastAttack = _clockAttack.getElapsedTime();
	if (_timeSinceLastAttack > _speedAttack)
	{
		std::cout << "Player Attack - Coordinates: x: " << targetCoords.x << " - y: " << targetCoords.y << std::endl;
		if (enemy->getSprite().getGlobalBounds().contains(static_cast<sf::Vector2f>(targetCoords)))
		{
			std::cout << "Attack with mouse: Pum Pum Pum" << std::endl;
		}
		enemy->takeDamage(calculateDamage());
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
	
	if (_upPressed || _downPressed || _rightPressed || _leftPressed)	
		_moving = true;
	else	
		_moving = false;
}
void Player::movePreviousPosition()
{
	_position = _prevPosition;
	_sprite.setPosition(_position);
}
uint Player::calculateDamage()
{
	return	_strength;
}
void Player::takeDamage(uint damage)
{
	_health -= damage;
	std::cout << "Player Health: " << _health << std::endl;
	if (_health <= 0)
	{
		_health = 0;
		die();
	}	
}
void Player::die()
{
	_alive = false;
	std::cout << "Player Died" << std::endl;
}
// -----------------------------------------
}

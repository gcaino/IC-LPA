#include "Enemy.h"
// -----------------------------------------
#include "Player.h"
#include "Constants.h"
#include <SFML\System.hpp>
#include <iostream>
#include <algorithm>
// -----------------------------------------
namespace lpa
// -----------------------------------------
{
// -----------------------------------------
Enemy::Enemy()
	: ENEMY_VELOCITY(20.f)
	, ENEMY_SPEED_ATTACK(sf::seconds(3.f))
	, _points(10)
	, _following(true)
	, _rangeAttack(false)
	, _timeToFollow(sf::seconds(2.f))
	, _timeSinceNotFollowing(sf::seconds(0.f))
	, _clockFollowingActive(false)
{
	_texture.loadFromFile(Constants::texturePathOrc);
	_sprite.setTexture(_texture);
	_sprite.setOrigin(_sprite.getGlobalBounds().width / 2, _sprite.getGlobalBounds().height);
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
	move(elapsedTime, pPlayer);
	calculateDirection();
	rotateSprite();
	iteratePlayersAttackables(pPlayer);
}
void Enemy::draw(sf::RenderTarget & target, sf::RenderStates states) const
{
	target.draw(_sprite);
}
void Enemy::move(sf::Time elapsedTime, Player* pPlayer)
{
	if (pPlayer->isAlive() && _following)
	{
		_prevPosition = _position;

		sf::Vector2f posPlayer = pPlayer->getPosition();
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
}
void Enemy::movePreviousPosition()
{
	_position = _prevPosition;
	_sprite.setPosition(_position);
}
void Enemy::moveRandomDirection()
{
	// TODO método para evitar que los enemigos se queden atorados en el mapa
}
void Enemy::waitToFollow()
{
	_timeSinceNotFollowing = _clockFollowing.getElapsedTime();
	if (_timeSinceNotFollowing > _timeToFollow)
	{
		_following = true;
		_clockFollowingActive = false;
	}
}
void Enemy::restartClockToFollow()
{
	_clockFollowing.restart();
	_clockFollowingActive = true;
}
void Enemy::iteratePlayersAttackables(Player* pPlayer)
{
	if (isItemAttackablesPlayersList(pPlayer))
		attack(pPlayer);
}
void Enemy::attack(Player* pPlayer)
{
	_timeSinceLastAttack = _clockAttack.getElapsedTime();
	if (_timeSinceLastAttack > _speedAttack)
	{
		std::cout << "Enemy Attack" << std::endl;
		pPlayer->takeDamage(calculateDamage());
		_clockAttack.restart();
	}
}
void Enemy::takeDamage(unsigned int damage)
{
	_health -= damage;
	std::cout << "Enemy Health: " << _health << std::endl;
	if (_health <= 0)
		die();
}
uint Enemy::calculateDamage()
{
	return	_strength;
}
void Enemy::die()
{
	_alive = false;
	std::cout << "Enemy Died" << std::endl;
}
void Enemy::addAttackablePlayer(Player* pPlayer)
{
	if (isItemAttackablesPlayersList(pPlayer))
		return;
	
	_attackablesPlayers.push_back(pPlayer);
}
void Enemy::removeAttackablePlayer(Player* pPlayer)
{
	if (isItemAttackablesPlayersList(pPlayer))
		_attackablesPlayers.remove(pPlayer);
}
bool Enemy::isItemAttackablesPlayersList(Player* pPlayer)
{
	return (std::find(_attackablesPlayers.begin(), _attackablesPlayers.end(), pPlayer) != _attackablesPlayers.end());
}
// -----------------------------------------
}

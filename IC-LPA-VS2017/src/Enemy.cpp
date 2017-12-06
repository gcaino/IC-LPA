#include "Enemy.h"
// -----------------------------------------
#include "AnimatedSprite.h"
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
using namespace Constants;
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
	setupAnimations();
	_animatedSprite.setOrigin(_animatedSprite.getGlobalBounds().width / 2, _animatedSprite.getGlobalBounds().height);

	_velocity = ENEMY_VELOCITY;
	_speedAttack = ENEMY_SPEED_ATTACK;
	_timeSinceLastAttack = _clockAttack.restart();
	//std::cout << "Create Enemy" << std::endl;
}
Enemy::~Enemy()
{
	//std::cout << "Destroy Enemy" << std::endl;
}
void Enemy::setupAnimations()
{
	// IDLE
	_textureIdle.loadFromFile(texturePlayerIdleAnimation);
	_idleAnimation.setSpriteSheet(_textureIdle);

	_idleAnimation.addFrame(sf::IntRect(0, 0, 133, 114));
	_idleAnimation.addFrame(sf::IntRect(133, 0, 133, 114));
	_idleAnimation.addFrame(sf::IntRect(266, 0, 133, 114));
	_idleAnimation.addFrame(sf::IntRect(399, 0, 133, 114));
	_idleAnimation.addFrame(sf::IntRect(532, 0, 133, 114));
	_idleAnimation.addFrame(sf::IntRect(665, 0, 133, 114));
	_idleAnimation.addFrame(sf::IntRect(798, 0, 133, 114));
	// WALK
	_textureWalk.loadFromFile(texturePlayerWalkAnimation);
	_walkingAnimation.setSpriteSheet(_textureWalk);

	_walkingAnimation.addFrame(sf::IntRect(0, 0, 136, 114));
	_walkingAnimation.addFrame(sf::IntRect(136, 0, 136, 114));
	_walkingAnimation.addFrame(sf::IntRect(272, 0, 136, 114));
	_walkingAnimation.addFrame(sf::IntRect(408, 0, 136, 114));
	_walkingAnimation.addFrame(sf::IntRect(544, 0, 136, 114));
	_walkingAnimation.addFrame(sf::IntRect(680, 0, 136, 114));
	_walkingAnimation.addFrame(sf::IntRect(816, 0, 136, 114));
	// ATTACK
	_textureAttack.loadFromFile(texturePlayerAttackAnimation);
	_attackAnimation.setSpriteSheet(_textureAttack);

	_attackAnimation.addFrame(sf::IntRect(0, 0, 137, 120));
	_attackAnimation.addFrame(sf::IntRect(137, 0, 137, 120));
	_attackAnimation.addFrame(sf::IntRect(274, 0, 137, 120));
	_attackAnimation.addFrame(sf::IntRect(411, 0, 137, 120));
	_attackAnimation.addFrame(sf::IntRect(548, 0, 137, 120));
	_attackAnimation.addFrame(sf::IntRect(685, 0, 137, 120));
	_attackAnimation.addFrame(sf::IntRect(822, 0, 137, 120));
	// HURT
	_textureHurt.loadFromFile(texturePlayerHurtAnimation);
	_hurtAnimation.setSpriteSheet(_textureHurt);

	_hurtAnimation.addFrame(sf::IntRect(0, 0, 124, 123));
	_hurtAnimation.addFrame(sf::IntRect(124, 0, 124, 123));
	_hurtAnimation.addFrame(sf::IntRect(248, 0, 124, 123));
	_hurtAnimation.addFrame(sf::IntRect(372, 0, 124, 123));
	_hurtAnimation.addFrame(sf::IntRect(496, 0, 124, 123));
	_hurtAnimation.addFrame(sf::IntRect(620, 0, 124, 123));
	_hurtAnimation.addFrame(sf::IntRect(744, 0, 124, 123));
	// DIE
	_textureDie.loadFromFile(texturePlayerDieAnimation);
	_dieAnimation.setSpriteSheet(_textureDie);

	_dieAnimation.addFrame(sf::IntRect(880, 0, 176, 129));
	_dieAnimation.addFrame(sf::IntRect(0, 0, 176, 129));
	_dieAnimation.addFrame(sf::IntRect(176, 0, 176, 129));
	_dieAnimation.addFrame(sf::IntRect(352, 0, 176, 129));
	_dieAnimation.addFrame(sf::IntRect(528, 0, 176, 129));
	_dieAnimation.addFrame(sf::IntRect(704, 0, 176, 129));
	_dieAnimation.addFrame(sf::IntRect(880, 0, 176, 129));

	_currentAnimation = &_idleAnimation;
	_animatedSprite.setAnimation(*_currentAnimation);
}
void Enemy::update(sf::Time elapsedTime, Player* pPlayer)
{
	if (!pPlayer->isAlive()) return;

	move(elapsedTime, pPlayer);
	calculateDirection();
	rotateSprite();
	iteratePlayersAttackables(pPlayer);
	verifyDeath(elapsedTime);

	_animatedSprite.update(elapsedTime);
}
void Enemy::draw(sf::RenderTarget & target, sf::RenderStates states) const
{
	target.draw(_animatedSprite);
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

		_animatedSprite.setPosition(_position);
	}

	if (_following)
	{
		_currentAnimation = &_walkingAnimation;
		_animatedSprite.play(*_currentAnimation);
	}
	else
	{
		if (_currentAnimation == &_walkingAnimation)
		{
			_animatedSprite.stop();
		}

		if (!_animatedSprite.isPlaying())
		{
			_currentAnimation = &_idleAnimation;
			_animatedSprite.play(*_currentAnimation);
		}
	}
}
void Enemy::movePreviousPosition()
{
	_position = _prevPosition;
	_animatedSprite.setPosition(_position);
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

		_currentAnimation = &_attackAnimation;
		_animatedSprite.play(*_currentAnimation);

		_clockAttack.restart();
	}
}
void Enemy::takeDamage(unsigned int damage)
{
	_health -= damage;
	std::cout << "Enemy Health: " << _health << std::endl;
	if (_health <= 0)
	{
		_health = 0;
		return;
	}

	if (!_animatedSprite.isPlaying() || _currentAnimation == &_idleAnimation)
	{
		_animatedSprite.pause();
		_currentAnimation = &_hurtAnimation;
		_animatedSprite.play(*_currentAnimation);
	}

	if (!_animatedSpriteBlood.isPlaying() && _currentAnimation == &_hurtAnimation)
		_animatedSpriteBlood.play();
}
uint Enemy::calculateDamage()
{
	return	_strength;
}
void Enemy::verifyDeath(sf::Time elapsedTime)
{
	if (_health <= 0)
	{
		if (_currentAnimation != &_dieAnimation)
		{
			_animatedSprite.pause();
			_currentAnimation = &_dieAnimation;
			_animatedSprite.play(*_currentAnimation);
			_animatedSprite.setFrame(1);
		}

		_elapsedDeadTime += elapsedTime;
		if (_elapsedDeadTime > _deadTime)
		{
			_alive = false;
			std::cout << "Enemy Died" << std::endl;
		}
	}
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

#include "Player.h"
// -----------------------------------------
#include "CollisionManager.h"
#include "Constants.h"
#include "Enemy.h"
#include "Wave.h"
#include <iostream>
#include <iterator>
#include <algorithm>
#include <map>
// -----------------------------------------
namespace lpa
// -----------------------------------------
{
// -----------------------------------------
using namespace Constants;
// -----------------------------------------
/**
 * Función utilitaria, utilizada para comparar pares de valores y obtener
 * el enemigo con el máximo valor en el eje y. 
 * Al momento de atacar se almacenan los enemigos atacables en un diccionario,
 * utilizando como valor el eje y se logra atacar al enemigo visible y no al solapado.
 */
typedef std::map<Enemy*, float> pair;
bool comparePositionY(pair::value_type pos1, pair::value_type pos2)
{
	return (pos1 < pos2);
}
// -----------------------------------------
Player::Player()
	: PLAYER_SPEED_ATTACK(sf::seconds(0.5f))
	, PLAYER_START_HEALTH(200)
	, _attacking(false)
	, _moving(false)
	, _active(true)
	, _rangeAttack()
{
	setupAnimations();
	_animatedSprite.setOrigin(_animatedSprite.getGlobalBounds().width / 2, _animatedSprite.getGlobalBounds().height);
	_animatedSpriteBlood.setOrigin(_animatedSprite.getGlobalBounds().width / 2, _animatedSprite.getGlobalBounds().height);
	resetPosition();

	_health = PLAYER_START_HEALTH;
	_speedAttack = PLAYER_SPEED_ATTACK;
	_alive = true;
	_timeSinceLastAttack = _clockAttack.restart();
	_deadTime = sf::seconds(2.f);
	_elapsedDeadTime = sf::seconds(0.f);
	
	//std::cout << "Create Player" << std::endl;
}
Player::~Player()
{
}
void Player::setupAnimations()
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
void Player::handlerInputs()
{
	if (!_active) return;

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
	if (!_active) return;
	// TODO - Para atacar con una tecla hay que tener en cuenta la dirección donde está pegando,
	// sino le puede pegar a otros que están en la lista de atacables
	if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
	{
		_attacking = true;

		_currentAnimation = &_attackAnimation;
		_animatedSprite.play(*_currentAnimation);
	}
	else
	{
		_attacking = false;
	}

	if (_attacking)
	{
		sf::Vector2i targetCoords = sf::Mouse::getPosition(window);

		uint maxWaveEnemies = pWave->getMaxEnemies();

		std::map<Enemy*, float> tempEnemyDictionary;
		for (uint i = 0; i < maxWaveEnemies; i++)
		{
			Enemy* pEnemy = &pWave->getEnemyRefByIndex(i);
			if (pEnemy->isAlive())
			{
				if (pEnemy->getAnimatedSprite().getGlobalBounds().contains(static_cast<sf::Vector2f>(targetCoords)))
				{
					std::cout << "Attack with mouse, Coordinates: x: " << targetCoords.x << " - y: " << targetCoords.y << std::endl;
					// Verifica si está en la lista de enmigos atacables (se incluyen por estar en rango de ataque)
					if (isItemAttackablesEnemiesList(pEnemy))
					{
						tempEnemyDictionary.insert(std::pair<Enemy*, float>(pEnemy, pEnemy->getPosition().y));
					}
				}
			}
		}
		// Ordena los items por la posición en el eje y, y toma el mayor valor
		// Para eliminar primero a los enemigos de la capa superior
		if (!tempEnemyDictionary.empty())
		{
			size_t result = 0;
			result = tempEnemyDictionary.size();
			std::map<Enemy*, float>::iterator it;
			it = std::max_element(tempEnemyDictionary.begin(), tempEnemyDictionary.end(), comparePositionY);
			attack(it->first);
		}
	}
}
void Player::update(sf::Time elapsedTime)
{
	if (_active)
	{
		move(elapsedTime);
		calculateDirection();
		rotateSprite();
	}

	verifyDeath(elapsedTime);

	setAttributesAnimations();
	_animatedSprite.update(elapsedTime);
	_animatedSpriteBlood.update(elapsedTime);
}
void Player::draw(sf::RenderTarget & target, sf::RenderStates states) const
{
	target.draw(_animatedSprite);
}
void Player::resetPosition()
{
	_position.x = WINDOW_WIDTH_MAX / 2;
	_position.y = WINDOW_HEIGHT_MAX / 2 + _animatedSprite.getGlobalBounds().height;
	_animatedSprite.setPosition(_position);
}
void Player::attack(Enemy* enemy)
{
	_timeSinceLastAttack = _clockAttack.getElapsedTime();
	if (_timeSinceLastAttack > _speedAttack)
	{
		enemy->takeDamage(calculateDamage());
		_attacking = false;

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

	_animatedSprite.setPosition(_position);
	_animatedSpriteBlood.setPosition(_position);

	if (_upPressed || _downPressed || _rightPressed || _leftPressed)
	{
		_moving = true;
		_currentAnimation = &_walkingAnimation;
		_animatedSprite.play(*_currentAnimation);
	}
	else
	{
		_moving = false;
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
void Player::movePreviousPosition()
{
	_position = _prevPosition;
	_animatedSprite.setPosition(_position);
}
uint Player::calculateDamage()
{
	return	_strength;
}
void Player::takeDamage(uint damage)
{
	_health -= damage;
	if (_health <= 0)
	{
		_health = 0;
		return;
	}
	std::cout << "Player Health: " << _health << std::endl;

	if (!_animatedSprite.isPlaying() || _currentAnimation == &_idleAnimation)
	{
		_animatedSprite.pause();
		_currentAnimation = &_hurtAnimation;
		_animatedSprite.play(*_currentAnimation);
	}

	if (!_animatedSpriteBlood.isPlaying() && _currentAnimation == &_hurtAnimation)
		_animatedSpriteBlood.play();
}
void Player::verifyDeath(sf::Time elapsedTime)
{
	if (_health <= 0)
	{
		if (_active && _currentAnimation != &_dieAnimation)
		{
			_animatedSprite.pause();
			_currentAnimation = &_dieAnimation;
			_animatedSprite.play(*_currentAnimation);
			_animatedSprite.setFrame(1);
			_active = false;
		}

		_elapsedDeadTime += elapsedTime;
		if (_elapsedDeadTime > _deadTime)
		{
			_alive = false;
			std::cout << "Player Died" << std::endl;
		}
	}
}
void Player::addAttackableEnemy(Enemy* pEnemy)
{
	if (isItemAttackablesEnemiesList(pEnemy))
		return;

	_attackablesEnemies.push_back(pEnemy);
}
void Player::removeAttackableEnemy(Enemy* pEnemy)
{
	if (isItemAttackablesEnemiesList(pEnemy))
		_attackablesEnemies.remove(pEnemy);
}
bool Player::isItemAttackablesEnemiesList(const Enemy* pEnemy)
{
	return (std::find(_attackablesEnemies.begin(), _attackablesEnemies.end(), pEnemy) != _attackablesEnemies.end());
}
void Player::setAttributesAnimations()
{
	if (_currentAnimation == &_idleAnimation)
	{
		_animatedSprite.setFrameTime(sf::seconds(0.2f));
	}
	else
	{
		_animatedSprite.setFrameTime(sf::seconds(0.1f));
	}

	if (_animatedSpriteBlood.isPlaying())
	{
		_drawBlood = true;
	}
	else
	{
		_drawBlood = false;
	}
}
// -----------------------------------------
}

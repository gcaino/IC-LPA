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
	, PLAYER_START_HEALTH(500)
	, _attacking(false)
	, _moving(false)
	, _rangeAttack()
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
	// TODO - Para atacar con una tecla hay que tener en cuenta la dirección donde está pegando,
	// sino le puede pegar a otros que están en la lista de atacables
	if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
	{
		_attacking = true;
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
				if (pEnemy->getSprite().getGlobalBounds().contains(static_cast<sf::Vector2f>(targetCoords)))
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
	_position.y = WINDOW_HEIGHT_MAX / 2 + _sprite.getGlobalBounds().height;
	_sprite.setPosition(_position);
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
// -----------------------------------------
}

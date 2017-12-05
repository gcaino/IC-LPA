#include "GameWorld.h"
// -----------------------------------------
#include "Constants.h"
#include "CollisionManager.h"
#include "GameObject.h"
#include <iostream>
#include <list>
#include <iterator>
#include <cmath>
// -----------------------------------------
namespace lpa
// -----------------------------------------
{
bool compareAxisY(const sf::Sprite& first, const sf::Sprite& second)
{
	return (first.getPosition().y < second.getPosition().y);
}
// -----------------------------------------
GameWorld::GameWorld(const sf::RenderWindow& window)
	: _indexCurrentWave(0)
	, _spawnManager(&_waves[0])
	, _window(&window)
	, _score(0)
	, _highScore(0)
{
}
GameWorld::~GameWorld()
{
}
void GameWorld::handlerInputs()
{
	if (!_player.isAlive())
		return;

	_player.handlerInputs();
	_player.handlerInputsAttack(_waves, *_window);
}
void GameWorld::update(sf::Time elapsedTime)
{
	if (!_player.isAlive())
		return;

	_player.update(elapsedTime);
	_waves[_indexCurrentWave].update(elapsedTime, &_player);
	
	collisionDetectionPlayerLimitsArena();
	collisionDetectionEnemiesLimitsArena();
	collisionDetectionPlayerEnemies();
	collisionDetectionEnemyEmemies();

	_spawnManager.update(elapsedTime);
}
void GameWorld::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
}
void GameWorld::draw(sf::RenderTarget& target, sf::RenderStates states)
{
	std::list<sf::Sprite> sprites;
	sprites.push_back(_arena.getSprite());
	sprites.push_back(_player.getSprite());

	uint maxWaveEnemies = _waves[_indexCurrentWave].getMaxEnemies();
	for (uint i = 0; i < maxWaveEnemies; i++)
	{
		if (_waves[_indexCurrentWave].getEnemyRefByIndex(i).isAlive())
		{
			sprites.push_back(_waves[_indexCurrentWave].getEnemyRefByIndex(i).getSprite());
		}
	}

	sprites.sort(compareAxisY);
	
	std::list<sf::Sprite>::iterator it;
	for (it = sprites.begin(); it != sprites.end(); ++it)
	{
		// Escalar Texturas (Comentado, no me termina de gustar el gameplay que genera y el pixelado)
		/*if (it != sprites.begin())
		{
			float targetSizeY	= static_cast<float>(target.getSize().y / 2);
			float spritePosY	= (*it).getPosition().y;
			float diffAbs		= abs(targetSizeY - spritePosY);
			float diffRel		= diffAbs / targetSizeY;

			if (diffRel > 0.25f)	diffRel = 0.25f;

			if (spritePosY < targetSizeY)
			{
				(*it).setScale(1 - diffRel, 1 - diffRel);
			}
			else if (spritePosY > targetSizeY)
			{
				(*it).setScale(1 + diffRel, 1 + diffRel);
			}
			else
			{
				(*it).setScale(1, 1);
			}
		}*/
		// Dibujar
		target.draw(*it, sf::RenderStates::Default);
	}
}
void GameWorld::collisionDetectionPlayerLimitsArena()
{
	sf::Image imageArenaCollision = _arena.getImageCollision();
	
	if (CollisionManager::pixelTest(_player.getSprite(), imageArenaCollision))
	{
		//std::cout << "Player Pixel Collision" << std::endl;
		_player.movePreviousPosition();
	}
}
void GameWorld::collisionDetectionEnemiesLimitsArena()
{
	sf::Image imageArenaCollision = _arena.getImageCollision();
	uint maxWaveEnemies = _waves[_indexCurrentWave].getMaxEnemies();
	for (uint i = 0; i < maxWaveEnemies; i++)
	{
		Enemy* enemy = &_waves[_indexCurrentWave].getEnemyRefByIndex(i);
		if (enemy->isAlive())
		{
			if (CollisionManager::pixelTest(enemy->getSprite(), imageArenaCollision))
			{
				//std::cout << "Enemy Pixel Collision" << std::endl;
				enemy->movePreviousPosition();
			}
		}
	}
}
void GameWorld::collisionDetectionPlayerEnemies()
{
	uint maxWaveEnemies = _waves[_indexCurrentWave].getMaxEnemies();
	for (uint i = 0; i < maxWaveEnemies; i++)
	{
		Enemy* pEnemy = &_waves[_indexCurrentWave].getEnemyRefByIndex(i);
		if (pEnemy->isAlive())
		{
			// Movement
			if (CollisionManager::boundingBoxTest(pEnemy->getSprite(), _player.getSprite(), 0.15f))
			{
				collisionPlayerActions(pEnemy);
				collisionEnemyActions(pEnemy);
			}
			else
			{
				notCollisionEnemyActions(pEnemy);
			}
			// Range Attack Player
			if (CollisionManager::boundingBoxRangeAttack(_player.getSprite(), pEnemy->getSprite()))
			{
				_player.addAttackableEnemy(pEnemy);
				//std::cout << "Enemy is attackable" << std::endl;
			}
			else
			{
				_player.removeAttackableEnemy(pEnemy);
			}
			// Range Attack Enemies
			if (CollisionManager::boundingBoxRangeAttack(pEnemy->getSprite(), _player.getSprite()))
			{
				pEnemy->addAttackablePlayer(&_player);
				//std::cout << "Player is attackable" << std::endl;
			}
			else
			{
				pEnemy->removeAttackablePlayer(&_player);
			}
		}
	}
}
void GameWorld::collisionDetectionEnemyEmemies()
{
	uint maxWaveEnemies = _waves[_indexCurrentWave].getMaxEnemies();
	for (uint i = 0; i < maxWaveEnemies - 1; i++)
	{
		Enemy* enemy = &_waves[_indexCurrentWave].getEnemyRefByIndex(i);
		if (enemy->isAlive())
		{
			for (uint j = i + 1; j < maxWaveEnemies; j++)
			{
				Enemy* enemy2 = &_waves[_indexCurrentWave].getEnemyRefByIndex(j);
				if (enemy2->isAlive())
				{
					if (CollisionManager::boundingBoxTest(enemy->getSprite(), enemy2->getSprite(), 0.1f))
					{
						enemy->movePreviousPosition();
					}
				}
			}
		}
	}
}
void GameWorld::collisionPlayerActions(Enemy* pEnemy)
{
	if (_player.isMoving())
	{
		_player.movePreviousPosition();
	}
}
void GameWorld::collisionEnemyActions(Enemy* pEnemy)
{
	pEnemy->movePreviousPosition();
	//pEnemy->attack(&_player);
	pEnemy->setFollowing(false);
}
void GameWorld::notCollisionEnemyActions(Enemy* pEnemy)
{
	if (!pEnemy->isFollowing()) 
	{
		if (!pEnemy->isClockFollowingActive())
			pEnemy->restartClockToFollow();
		
		pEnemy->waitToFollow();
	}
}
// -----------------------------------------
}

#include "GameWorld.h"
// -----------------------------------------
#include "CollisionManager.h"
#include "GameObject.h"
#include <iostream>
#include <list>
#include <iterator>
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
	
	collisionDetectionPlayerEnemies();

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
		target.draw(*it, sf::RenderStates::Default);
	}
}
void GameWorld::collisionDetectionPlayerEnemies()
{
	uint maxWaveEnemies = _waves[_indexCurrentWave].getMaxEnemies();
	for (uint i = 0; i < maxWaveEnemies; i++)
	{
		Enemy* enemy = &_waves[_indexCurrentWave].getEnemyRefByIndex(i);
		if (enemy->isAlive())
		{
			if (CollisionManager::boundingBoxTest(enemy->getSprite(), _player.getSprite()))
			{
				collisionPlayerActions(enemy);
				collisionEnemyActions(enemy);
			}
			else
			{
				notCollisionEnemyActions(enemy);
			}
		}
	}
}
void GameWorld::collisionPlayerActions(Enemy* pEnemy)
{
	_player.movePreviousPosition();
}
void GameWorld::collisionEnemyActions(Enemy* pEnemy)
{
	pEnemy->movePreviousPosition();
	pEnemy->attack(&_player);
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

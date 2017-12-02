#include <iostream>
#include "GameWorld.h"
#include "CollisionManager.h"
// -----------------------------------------
namespace lpa
{
	GameWorld::GameWorld()
		: _indexCurrentWave(0)
		, _spawnManager(&_waves[0])
	{
	}

	GameWorld::~GameWorld()
	{
	}

	void GameWorld::handlerInputs()
	{
		_player.handlerInputs();
	}

	void GameWorld::update(sf::Time elapsedTime)
	{
		_player.update(elapsedTime);
		_spawnManager.update(elapsedTime);
		_waves[_indexCurrentWave].update(elapsedTime, &_player);

		uint maxWaveEnemies = _waves[_indexCurrentWave].getMaxEnemies();
		Enemy* enemy = nullptr;
		for (uint i = 0; i < maxWaveEnemies; i++)
		{
			enemy = &_waves[_indexCurrentWave].getEnemyRefByIndex(i);
			if (CollisionManager::boundingBoxTest(_player.getSprite(), enemy->getSprite()))
			{
				//_player.movePreviousPosition();
				enemy->movePreviousPosition();
				enemy->attack(&_player);
			}
		}
	}

	void GameWorld::draw(sf::RenderTarget& target, sf::RenderStates states) const
	{
		_arena.draw(target, states);
		_player.draw(target, states);
		_waves[_indexCurrentWave].draw(target, states);
	}
}

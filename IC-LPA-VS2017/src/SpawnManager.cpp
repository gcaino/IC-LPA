#include <cstdlib>
#include <iostream>
#include "SpawnManager.h"
#include "Constants.h"
// -----------------------------------------
using namespace Constants;

namespace lpa
{
	SpawnManager::SpawnManager(Wave* wave)
		: _spawnPoints{ SPAWN_POINT_UNO, SPAWN_POINT_DOS }
		, _spawnTime(SPAWN_TIME)
		, _timeSinceLastSpawn(sf::seconds(0.f))
		, _wave(wave)
	{
		//std::cout << _wave << std::endl;
	}

	SpawnManager::~SpawnManager()
	{
		std::cout << "Destroy SpawnManager" << std::endl;
	}

	void SpawnManager::update(sf::Time elapsedTime)
	{
		_timeSinceLastSpawn += elapsedTime;
		if (_timeSinceLastSpawn >= _spawnTime)
		{
			spawnEnemies();
			_timeSinceLastSpawn = sf::seconds(0.f);
		}
	}

	void SpawnManager::spawnEnemies()
	{
		if (_wave->getRemainingEnemies() > 0)
		{
			uint randomPoint = std::rand() % SPAWN_POINTS_MAX;
			uint indexCurrentEnemy = _wave->getIndexCurrentEnemy();

			Enemy& currentEnemy = _wave->getEnemyRefByIndex(indexCurrentEnemy);
			currentEnemy.setIsAlive(true);
			currentEnemy.setPosition(_spawnPoints[randomPoint]);

			_wave->increaseIndexCurrentEnemy();
			_wave->decreaseRemainingEnemies();

			std::cout << "Spawn Enemy" << std::endl;
		}
	}
}

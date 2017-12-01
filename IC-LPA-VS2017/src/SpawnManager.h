#ifndef SPAWN_MANAGER_H
#define SPAWN_MANAGER_H
// -----------------------------------------
#include <SFML\Graphics.hpp>
#include "Constants.h"
#include "Wave.h"
// -----------------------------------------
namespace lpa
{
	class SpawnManager
	{
	private:
		sf::Vector2f	_spawnPoints[2];
		sf::Time		_spawnTime;
		sf::Time		_timeSinceLastSpawn;
		Wave*			_wave;

		void spawnEnemies();

	public:
		SpawnManager(Wave* wave);
		~SpawnManager();

		void update(sf::Time elapsedTime);
	};
}
#endif // SPAWN_MANAGER_H


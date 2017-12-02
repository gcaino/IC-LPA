#include <iostream>
#include "GameWorld.h"
#include "CollisionManager.h"
// -----------------------------------------
namespace lpa
{
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

	void GameWorld::handlerInputs(const sf::Window& window)
	{
		_player.handlerInputs(window);
	}

	void GameWorld::update(sf::Time elapsedTime)
	{
		_player.update(elapsedTime);
		_waves[_indexCurrentWave].update(elapsedTime, &_player);

		uint maxWaveEnemies = _waves[_indexCurrentWave].getMaxEnemies();
		Enemy* enemy = nullptr;
		for (uint i = 0; i < maxWaveEnemies; i++)
		{
			enemy = &_waves[_indexCurrentWave].getEnemyRefByIndex(i);
			if (_player.isAlive() && enemy->isAlive())
			{
				if (CollisionManager::boundingBoxTest(enemy->getSprite(), _player.getSprite()))
				{
					//_player.movePreviousPosition();
					if (_player.isAttacking())
					{
						sf::Vector2i targetCoords = sf::Mouse::getPosition(*_window);
						_player.attack(enemy, targetCoords);
					}
					//enemy->movePreviousPosition();
					enemy->setFollowing(false);
					enemy->attack(&_player);
				}
				else
				{
					enemy->setFollowing(true);
				}
			}
		}
		if (_player.isAlive())
			_spawnManager.update(elapsedTime);
	}

	void GameWorld::draw(sf::RenderTarget& target, sf::RenderStates states) const
	{
		_arena.draw(target, states);
		_waves[_indexCurrentWave].draw(target, states);
		_player.draw(target, states);
	}
}

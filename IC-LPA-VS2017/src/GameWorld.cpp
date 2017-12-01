#include <iostream>
#include "GameWorld.h"
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
		_waves[_indexCurrentWave].update(elapsedTime);
	}

	void GameWorld::draw(sf::RenderTarget& target, sf::RenderStates states) const
	{
		_arena.draw(target, states);
		_player.draw(target, states);
		_waves[_indexCurrentWave].draw(target, states);
	}
}

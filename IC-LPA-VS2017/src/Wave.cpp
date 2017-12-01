#include <iostream>
#include "Wave.h"
#include "Constants.h"
// -----------------------------------------
namespace lpa
{
    Wave::Wave()
		: _remainingEnemies(Constants::ENEMY_MAX)
		, _indexCurrentEnemy(0)
    {
    }

    Wave::~Wave()
    {
		//std::cout << "Destroy Wave" << std::endl;
    }

	void Wave::update(sf::Time elapsedTime)
	{
		for (uint i = 0; i < ENEMY_MAX; i++)
		{
			if (_enemies[i].getIsAlive())
				_enemies[i].update(elapsedTime);
		}
	}

	void Wave::draw(sf::RenderTarget& target, sf::RenderStates states) const
	{
		for (uint i = 0; i < ENEMY_MAX; i++)
		{
			if (_enemies[i].getIsAlive())
				_enemies[i].draw(target, states);
		}
	}
}

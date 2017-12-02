#include <iostream>
#include "Wave.h"
#include "Player.h"
#include "Constants.h"
// -----------------------------------------
namespace lpa
{
    Wave::Wave()
		: _remainingEnemies(Constants::ENEMY_MAX)
		, _indexCurrentEnemy(0)
		, _maxEnemies(Constants::ENEMY_MAX)
    {
    }

    Wave::~Wave()
    {
		//std::cout << "Destroy Wave" << std::endl;
    }

	void Wave::update(sf::Time elapsedTime, Player* pPlayer)
	{
		for (uint i = 0; i < ENEMY_MAX; i++)
		{
			if (_enemies[i].isAlive())
			{
				_enemies[i].update(elapsedTime, pPlayer);
			}
		}
	}

	void Wave::draw(sf::RenderTarget& target, sf::RenderStates states) const
	{
		for (uint i = 0; i < ENEMY_MAX; i++)
		{
			if (_enemies[i].isAlive())
				_enemies[i].draw(target, states);
		}
	}
}

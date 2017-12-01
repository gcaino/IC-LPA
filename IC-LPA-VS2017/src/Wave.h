#ifndef WAVE_H
#define WAVE_H
// -----------------------------------------
#include "Constants.h"
#include "Enemy.h"
// -----------------------------------------
using namespace Constants;

namespace lpa
{
    class Wave
    {
    private:
        Enemy			_enemies[ENEMY_MAX];
		uint			_indexCurrentEnemy;
		uint			_remainingEnemies;

    public:
        Wave();
        ~Wave();

		uint	getRemainingEnemies() const		{ return _remainingEnemies; }
		Enemy&	getEnemyRefByIndex(uint index)	{ return _enemies[index]; }
		uint	getIndexCurrentEnemy() const	{ return _indexCurrentEnemy; }

		void	increaseIndexCurrentEnemy()		{ ++_indexCurrentEnemy; }
		void	decreaseRemainingEnemies()		{ if (_remainingEnemies == 0) return; --_remainingEnemies; }

		void update(sf::Time elapsedTime);
		virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
    };
}
#endif // WAVE_H

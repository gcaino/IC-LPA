#ifndef ENEMY_H
#define ENEMY_H
// -----------------------------------------
#include "Character.h"
#include <SFML\Graphics.hpp>
// -----------------------------------------
namespace lpa
{
	class Player;

    class Enemy : public Character
    {
	private:
		sf::Time	_speedAttack;
		sf::Time	_timeSinceLastAttack;
		sf::Clock	_clockAttack;

		void move(sf::Time elapsedTime, sf::Vector2f posPlayer);
		
    public:
        Enemy();
        ~Enemy();

		virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
		void update(sf::Time elapsedTime, Player* pPlayer);
		void movePreviousPosition();
		void attack(Player* pPlayer);
    };
}
#endif // ENEMY_H

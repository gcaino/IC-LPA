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
		unsigned int	_points;
		bool			_following;
		sf::Time		_speedAttack;
		sf::Time		_timeSinceLastAttack;
		sf::Clock		_clockAttack;

		void move(sf::Time elapsedTime, Player* pPlayer);
		uint calculateDamage();
		
    public:
        Enemy();
        ~Enemy();

		bool isFollowing() const			{ return _following; }
		void setFollowing(bool following)	{ _following = following; }

		virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
		void update(sf::Time elapsedTime, Player* pPlayer);
		void movePreviousPosition();
		void attack(Player* pPlayer);
		void takeDamage(unsigned int damage);
		void die();
    };
}
#endif // ENEMY_H

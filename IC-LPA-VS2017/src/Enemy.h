#ifndef ENEMY_H
#define ENEMY_H
// -----------------------------------------
#include "Character.h"
#include "GameObject.h"
#include <SFML\Graphics.hpp>
// -----------------------------------------
namespace lpa
// -----------------------------------------
{
// -----------------------------------------
typedef unsigned int uint;
// -----------------------------------------
class Player;
// -----------------------------------------
class Enemy : public Character
{
private:
	const float			ENEMY_VELOCITY;
	const sf::Time		ENEMY_SPEED_ATTACK;

	uint				_points;
	bool				_following;
	sf::Time			_speedAttack;
	sf::Time			_timeSinceLastAttack;
	sf::Clock			_clockAttack;

	sf::Time			_timeToFollow;
	sf::Time			_timeSinceNotFollowing;
	sf::Clock			_clockFollowing;
	bool				_clockFollowingActive;

	void move(sf::Time elapsedTime, Player* pPlayer);
	uint calculateDamage();
		
public:
    Enemy();
    ~Enemy();

	bool isFollowing() const			{ return _following; }
	void setFollowing(bool following)	{ _following = following; }
	bool isClockFollowingActive() const { return _clockFollowingActive; }
	
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
	void update(sf::Time elapsedTime, Player* pPlayer);
	void movePreviousPosition();
	void moveRandomDirection();
	void waitToFollow();
	void restartClockToFollow();
	void attack(Player* pPlayer);
	void takeDamage(unsigned int damage);
	void die();
};
// -----------------------------------------
}
// -----------------------------------------
#endif // ENEMY_H

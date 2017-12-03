#ifndef PLAYER_H
#define PLAYER_H
// -----------------------------------------
#include "Character.h"
#include "InputManager.h"
// -----------------------------------------
namespace lpa
// -----------------------------------------
{
// -----------------------------------------
class Enemy;
// -----------------------------------------
class Player : public Character, public InputManager
{
private:
	const sf::Time		PLAYER_SPEED_ATTACK;
	const unsigned int	PLAYER_START_HEALTH;

	sf::Time			_speedAttack;
	sf::Time			_timeSinceLastAttack;
	sf::Clock			_clockAttack;
	bool				_attacking;

	void move(sf::Time elapsedTime);
    void resetPosition();
	uint calculateDamage();
	void die();

public:
	Player();
	~Player();

	bool isAttacking() const { return _attacking; }

	void handlerInputs();
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
	void update(sf::Time elapsedTime);
	void movePreviousPosition();
	void attack(Enemy* enemy, sf::Vector2i targetCoords);
	void takeDamage(uint damage);
};
// -----------------------------------------
}
// -----------------------------------------
#endif // !PLAYER_H


#ifndef PLAYER_H
#define PLAYER_H
// -----------------------------------------
#include "Character.h"
#include "GameObject.h"
#include "InputManager.h"
#include <list>
// -----------------------------------------
namespace lpa
// -----------------------------------------
{
// -----------------------------------------
class Enemy;
class Wave;
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
	bool				_moving;
	float				_rangeAttack;

	std::list<Enemy*>	_attackablesEnemies;
	std::list<Enemy*>::iterator it;

	void move(sf::Time elapsedTime);
    void resetPosition();
	uint calculateDamage();
	void verifyDeath(sf::Time elapsedTime);
	void setAttributesAnimations();

public:
	Player();
	~Player();

	bool isAttacking() const			{ return _attacking; }
	void setAttacking(bool attacking)	{ _attacking = attacking; }
	bool isMoving() const				{ return _moving; }
	void setMoving(bool moving)			{ _moving = moving; }

	void addAttackableEnemy(Enemy* enemy);
	void removeAttackableEnemy(Enemy* enemy);
	bool isItemAttackablesEnemiesList(const Enemy* enemy);

	void setupAnimations();

	void handlerInputs();
	void handlerInputsAttack(Wave* pWave, const sf::RenderWindow& window);
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
	void update(sf::Time elapsedTime);
	void movePreviousPosition();
	void attack(Enemy* enemy);
	void takeDamage(uint damage);
};
// -----------------------------------------
}
// -----------------------------------------
#endif // !PLAYER_H


#ifndef PLAYER_H
#define PLAYER_H
// -----------------------------------------
#include "Character.h"
#include "InputManager.h"
// -----------------------------------------
namespace lpa
{
	class Enemy;

	class Player : public Character, public InputManager
	{
	private:
		sf::Time	_speedAttack;
		sf::Time	_timeSinceLastAttack;
		sf::Clock	_clockAttack;

		void move(sf::Time elapsedTime);
        void resetPosition();
		void attack();

	public:
		Player();
		~Player();

		void handlerInputs();
		virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
		void update(sf::Time elapsedTime);
		void movePreviousPosition();
	};
}
#endif // !PLAYER_H


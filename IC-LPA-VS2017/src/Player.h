#ifndef PLAYER_H
#define PLAYER_H
// -----------------------------------------
#include "Character.h"
#include "InputManager.h"
// -----------------------------------------
namespace lpa
{
	class Player : public Character, public InputManager
	{
	private:

	public:
		Player();
		~Player();

		void handlerInputs();
		virtual void update(sf::Time elapsedTime);
	};
}
#endif // !PLAYER_H


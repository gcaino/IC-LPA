#ifndef PLAYER_H
#define PLAYER_H
// -----------------------------------------
#include "Character.h"
// -----------------------------------------
namespace lpa
{
	class Player : public Character
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


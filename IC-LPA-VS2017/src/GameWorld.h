#ifndef GAMEWORLD_H
#define GAMEWORLD_H
// -----------------------------------------
#include <SFML\Graphics.hpp>
#include "Player.h"
// -----------------------------------------
namespace lpa
{
	class GameWorld : public sf::Drawable
	{
	private:
		Player _player;

	public:
		GameWorld();
		~GameWorld();

		void handlerInputs();
		void update(sf::Time elapsedTime);
		virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
	};
}
#endif // GAMEWORLD_H
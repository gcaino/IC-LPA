#ifndef GAMEWORLD_H
#define GAMEWORLD_H
// -----------------------------------------
#include "Player.h"
#include "Arena.h"
#include "Wave.h"
#include "Constants.h"
#include <SFML\Graphics.hpp>
// -----------------------------------------
namespace lpa
{
	class GameWorld : public sf::Drawable
	{
	private:
		Player _player;
		Arena  _arena;
		Wave   _waves[Constants::WAVE_MAX];

	public:
		GameWorld();
		~GameWorld();

		void handlerInputs();
		void update(sf::Time elapsedTime);
		virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
	};
}
#endif // GAMEWORLD_H

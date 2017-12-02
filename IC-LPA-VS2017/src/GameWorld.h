#ifndef GAMEWORLD_H
#define GAMEWORLD_H
// -----------------------------------------
#include "Player.h"
#include "Arena.h"
#include "Wave.h"
#include "Constants.h"
#include "SpawnManager.h"
#include <SFML\Graphics.hpp>
// -----------------------------------------
using namespace Constants;

namespace lpa
{
	class GameWorld : public sf::Drawable
	{
	private:
		Player				_player;
		Arena				_arena;
		uint				_indexCurrentWave;
		Wave				_waves[WAVE_MAX];
		SpawnManager		_spawnManager;

	public:
		GameWorld();
		~GameWorld();

		void handlerInputs();
		void update(sf::Time elapsedTime);
		virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
	};
}
#endif // GAMEWORLD_H

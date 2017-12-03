#ifndef GAMEWORLD_H
#define GAMEWORLD_H
// -----------------------------------------
#include "Arena.h"
#include "Player.h"
#include "SpawnManager.h"
#include "Wave.h"
#include <SFML\Graphics.hpp>
// -----------------------------------------
namespace lpa
// -----------------------------------------
{
// -----------------------------------------
typedef unsigned int uint;
const uint WAVE_MAX = 5;
// -----------------------------------------
class GameWorld : public sf::Drawable
{
private:
	const sf::RenderWindow*	_window;
	uint					_score;
	uint					_highScore;
	Player					_player;
	Arena					_arena;
	uint					_indexCurrentWave;
	Wave					_waves[WAVE_MAX];
	SpawnManager			_spawnManager;

	void collisionDetectionPlayerEnemies();

public:
	GameWorld(const sf::RenderWindow& window);
	~GameWorld();

	void handlerInputs();
	void update(sf::Time elapsedTime);
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
};
// -----------------------------------------
}
// -----------------------------------------
#endif // GAMEWORLD_H

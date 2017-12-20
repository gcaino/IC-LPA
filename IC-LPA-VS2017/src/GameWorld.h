#ifndef GAMEWORLD_H
#define GAMEWORLD_H
// -----------------------------------------
#include "Arena.h"
#include "Player.h"
#include "SpawnManager.h"
#include "Wave.h"
#include <SFML\Graphics.hpp>
#include <SFML\Audio.hpp>
#include <vector>
// -----------------------------------------
namespace lpa
// -----------------------------------------
{
// -----------------------------------------
typedef unsigned int uint;
const uint WAVE_MAX = 5;

struct Text
{
	sf::Text	text;
	bool		visible;
};
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

	sf::Music				_orcCampMusic;

	sf::Font				_orcHordeFont;
	Text					_waveText;
	Text					_scoreText;
	sf::Time				_elapsedWaitTime;
	sf::Time				_waitTime;
	std::vector<Text*>		_texts;

	void initTexts();
	void addTextsToDraw();
	void updateTexts();
	void showStartText(sf::Time elapsedTime);

	void initSounds();

	void collisionDetectionPlayerLimitsArena();
	void collisionDetectionEnemiesLimitsArena();
	void collisionDetectionPlayerEnemies();
	void collisionDetectionEnemyEmemies();
	void collisionPlayerActions(Enemy* pEnemy);
	void collisionEnemyActions(Enemy* pEnemy);
	void notCollisionEnemyActions(Enemy* pEnemy);

public:
	GameWorld(const sf::RenderWindow& window);
	~GameWorld();

	void handlerInputs();
	void update(sf::Time elapsedTime);
	void draw(sf::RenderTarget& target, sf::RenderStates states);
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
};
// -----------------------------------------
}
// -----------------------------------------
#endif // GAMEWORLD_H

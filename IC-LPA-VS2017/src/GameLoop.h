#ifndef GAMELOOP_H
#define GAMELOOP_H
// -----------------------------------------
#include <SFML\Graphics.hpp>
// -----------------------------------------
namespace lpa
// -----------------------------------------
{
// -----------------------------------------
class GameWorld;
// -----------------------------------------
class GameLoop
{
private:
	sf::RenderWindow	_window;
	bool				_paused;
	sf::Clock			_clock;
	sf::Time			_elapsedTime;
	GameWorld*			_gameWorld;

	void pause();

	void handlerEvents();
	void update(sf::Time elapsedTime);
	void draw();

public:
	GameLoop();
	~GameLoop();

	void run();
};
// -----------------------------------------
}
// -----------------------------------------
#endif // GAMELOOP_H
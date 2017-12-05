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
	const unsigned int	FPS;

	sf::RenderWindow	_window;
	bool				_paused;
	sf::Clock			_clock;
	sf::Time			_elapsedTime;
	GameWorld*			_gameWorld;

	sf::Texture			_textureMousePointer;
	sf::Sprite			_spriteMousePointer;

	void pause();
	void setMousePointer();
	void updateMousePointer();

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
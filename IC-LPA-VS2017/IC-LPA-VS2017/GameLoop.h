#ifndef GAMELOOP_H
#define GAMELOOP_H
#include <SFML\Graphics.hpp>
#include "GameWorld.h"

class GameLoop
{
private:
	sf::RenderWindow	_window;
	GameWorld*			_gameWorld;

	void handlerEvents();
	void update();
	void render();

public:
	GameLoop();
	~GameLoop();

	void run();
}; 

#endif // GAMELOOP_H
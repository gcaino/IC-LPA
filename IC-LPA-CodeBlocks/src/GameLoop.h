#ifndef GAMELOOP_H
#define GAMELOOP_H
// -----------------------------------------
#include <SFML\Graphics.hpp>
// -----------------------------------------
namespace lpa
{
	class GameWorld; // Forward declaration

	class GameLoop
	{
	private:
		sf::RenderWindow	_window;
		sf::Clock			_clock;
		sf::Time			_elapsedTime;
		GameWorld*			_gameWorld;

		void handlerEvents();
		void update(sf::Time elapsedTime);
		void draw();

	public:
		GameLoop();
		~GameLoop();

		void run();
	};
}
#endif // GAMELOOP_H
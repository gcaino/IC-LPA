#include "Constants.h"
#include "GameLoop.h"
#include "GameWorld.h"
#include <SFML\Graphics.hpp>
// -----------------------------------------
namespace lpa
{
	GameLoop::GameLoop()
	{
		_window.create(sf::VideoMode(Constants::WINDOW_WIDTH_MAX,
                               Constants::WINDOW_HEIGHT_MAX), "Final Project LPA");
		_gameWorld = new GameWorld(_window);
	}

	GameLoop::~GameLoop()
	{
		if (_gameWorld != nullptr)
			delete _gameWorld;
	}

	void GameLoop::run()
	{
		while (_window.isOpen())
		{
			_elapsedTime = _clock.restart();

			handlerEvents();
			update(_elapsedTime);
			draw();
		}
	}

	void GameLoop::handlerEvents()
	{
		sf::Event event;
		while (_window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				_window.close();

			if (event.type == sf::Event::KeyPressed)
			{
				if (event.key.code == sf::Keyboard::Escape)
					_window.close();
			}
		}
		_gameWorld->handlerInputs(_window);
	}

	void GameLoop::update(sf::Time elapsedTime)
	{
		_gameWorld->update(elapsedTime);
	}

	void GameLoop::draw()
	{
		_window.clear();
		_gameWorld->draw(_window, sf::RenderStates::Default);
		_window.display();
	}
}

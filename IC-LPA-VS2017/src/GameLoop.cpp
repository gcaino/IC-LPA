#include "GameLoop.h"
// -----------------------------------------
#include "Constants.h"
#include "GameWorld.h"
#include <SFML\Graphics.hpp>
#include <iostream>
// -----------------------------------------
namespace lpa
// -----------------------------------------
{
// -----------------------------------------
GameLoop::GameLoop()
	: _paused(false)
	, FPS(60)
{
	_window.create(sf::VideoMode(Constants::WINDOW_WIDTH_MAX,
								 Constants::WINDOW_HEIGHT_MAX), "Final Project LPA");
	_window.setFramerateLimit(FPS);
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
		handlerEvents();

		_elapsedTime = _clock.restart();
		//std::cout << 1.0f / _elapsedTime.asSeconds() << std::endl;

		if (!_paused)
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
			switch (event.key.code)
			{
			case sf::Keyboard::Escape:
				_window.close();
			case sf::Keyboard::P:
				pause();
			default:
				break;
			}				
		}
	}
	_gameWorld->handlerInputs();
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
void GameLoop::pause()
{
	(_paused) ? _paused = false : _paused = true;
}
// -----------------------------------------
}

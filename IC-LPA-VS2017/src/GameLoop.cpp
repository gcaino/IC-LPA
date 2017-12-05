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
	setMousePointer();
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
	updateMousePointer();

	if (!_paused)
		_gameWorld->update(elapsedTime);
}
void GameLoop::draw()
{
	_window.clear();
	_gameWorld->draw(_window, sf::RenderStates::Default);
	_window.draw(_spriteMousePointer, sf::RenderStates::Default);
	_window.display();
}
void GameLoop::pause()
{
	(_paused) ? _paused = false : _paused = true;
}
void GameLoop::setMousePointer()
{
	_window.setMouseCursorVisible(false);
	_textureMousePointer.loadFromFile(Constants::texturesPathMousePointerAxe);
	_spriteMousePointer.setTexture(_textureMousePointer);

	sf::Vector2f mousePointerOrigin;
	mousePointerOrigin.x = _spriteMousePointer.getGlobalBounds().width / 2;
	mousePointerOrigin.y = _spriteMousePointer.getLocalBounds().height / 2;
	_spriteMousePointer.setOrigin(mousePointerOrigin);
}
void GameLoop::updateMousePointer()
{
	sf::Vector2i mousePosition = static_cast<sf::Vector2i>(sf::Mouse::getPosition(_window));
	_spriteMousePointer.setPosition(static_cast<sf::Vector2f>(mousePosition));
}
// -----------------------------------------
}

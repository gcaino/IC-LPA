#include "GameLoop.h"
#include <SFML\Graphics.hpp>

GameLoop::GameLoop()
{
	_window.create(sf::VideoMode(800, 600), "Final Project LPA");
	_gameWorld = new GameWorld();
}

GameLoop::~GameLoop()
{
	delete _gameWorld;
}

void GameLoop::run()
{
	while (_window.isOpen())
	{
		handlerEvents();
		update();
		render();
	}
}

void GameLoop::handlerEvents()
{
	sf::Event event;
	while (_window.pollEvent(event))
	{
		if (event.type == sf::Event::Closed)
			_window.close();
	}
}

void GameLoop::update()
{
	_gameWorld->update();
}

void GameLoop::render()
{
	_window.clear();
	_window.draw(_gameWorld->getPlayer());
	_window.display();
}

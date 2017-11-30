#include "GameWorld.h"
// -----------------------------------------
namespace lpa
{
	GameWorld::GameWorld()
	{

	}

	GameWorld::~GameWorld()
	{
	}

	void GameWorld::handlerInputs()
	{
		_player.handlerInputs();
	}

	void GameWorld::update(sf::Time elapsedTime)
	{
		_player.update(elapsedTime);
	}

	void GameWorld::draw(sf::RenderTarget& target, sf::RenderStates states) const
	{
		_player.draw(target, states);
	}
}

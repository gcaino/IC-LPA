#include "CollisionManager.h"
// -----------------------------------------
namespace lpa
{
	CollisionManager::CollisionManager()
	{
	}

	CollisionManager::~CollisionManager()
	{
	}

	bool CollisionManager::boundingBoxTest(const sf::Sprite & Object1, const sf::Sprite & Object2)
	{
		sf::FloatRect boundingBoxObj1 = Object1.getGlobalBounds();
		sf::FloatRect boundingBoxObj2 = Object2.getGlobalBounds();

		if (boundingBoxObj1.intersects(boundingBoxObj2))
			return true;
		else
			return false;
	}
}
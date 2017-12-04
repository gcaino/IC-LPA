#include "CollisionManager.h"
// -----------------------------------------
#include <iostream>
// -----------------------------------------
namespace lpa
// -----------------------------------------
{
// -----------------------------------------
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

	boundingBoxObj1.left	*= 1.25f;
	boundingBoxObj1.top		*= 1.25f;
	boundingBoxObj1.width	*= 0.75f;
	boundingBoxObj1.height	*= 0.75f;

	boundingBoxObj2.left *= 1.25f;
	boundingBoxObj2.top *= 1.25f;
	boundingBoxObj2.width *= 0.75f;
	boundingBoxObj2.height *= 0.75f;

	if (boundingBoxObj1.intersects(boundingBoxObj2))
		return true;
	else
		return false;
}
bool CollisionManager::pixelTest(const sf::Sprite& sprite, const sf::Image& mapImage)
{
	sf::Vector2u spritePosition = static_cast<sf::Vector2u>(sprite.getPosition());
	sf::Color pixelColor = mapImage.getPixel(spritePosition.x, spritePosition.y);

	if (pixelColor == sf::Color::Red)
	{
		return true;
	}
	else
	{
		return false;
	}
}
// -----------------------------------------
}
#ifndef COLLISION_MANAGER_H
#define	COLLISION_MANAGER_H
// -----------------------------------------
#include <SFML\Graphics.hpp>
// -----------------------------------------
namespace lpa
// -----------------------------------------
{
// -----------------------------------------
class CollisionManager
{
public:
	CollisionManager();
	~CollisionManager();

	static bool boundingBoxTest(const sf::Sprite& Object1, const sf::Sprite& Object2);
};
// -----------------------------------------
}
// -----------------------------------------
#endif // !COLLISION_MANAGER_H

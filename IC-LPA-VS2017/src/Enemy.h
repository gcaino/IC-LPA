#ifndef ENEMY_H
#define ENEMY_H
// -----------------------------------------
#include "Character.h"
// -----------------------------------------
namespace lpa
{
    class Enemy : public Character
    {
    public:
        Enemy();
        ~Enemy();

		virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
		virtual void update(sf::Time elapsedTime);
    };
}
#endif // ENEMY_H

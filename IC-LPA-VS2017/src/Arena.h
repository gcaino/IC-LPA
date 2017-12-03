#ifndef ARENA_H
#define ARENA_H
// -----------------------------------
#include "GameObject.h"
#include <SFML\Graphics.hpp>
// -----------------------------------
namespace lpa
// -----------------------------------
{
// -----------------------------------
class Arena : public GameObject
{
private:
    //sf::Sprite      _sprite;
    sf::Texture     _texture;

public:
    Arena();
    ~Arena();

    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
};
// -----------------------------------
}
// -----------------------------------
#endif // ARENA_H

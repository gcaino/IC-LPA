#include "Arena.h"
#include <SFML\Graphics.hpp>
// ---------------------------
namespace lpa
{
    Arena::Arena()
    {
        if (!_texture.loadFromFile("assets\\textures\\arena-01.png")) {}
        _sprite.setTexture(_texture);
    }

    Arena::~Arena()
    {
        //dtor
    }

    void Arena::draw(sf::RenderTarget& target, sf::RenderStates states) const
    {
        target.draw(_sprite);
    }
}

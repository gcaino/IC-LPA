#include "Arena.h"
// ---------------------------
#include "Constants.h"
#include <SFML\Graphics.hpp>
// ---------------------------
namespace lpa
// ---------------------------
{
// ---------------------------
Arena::Arena()
{
	_texture.loadFromFile(Constants::texturesPath + "arena-01.png");
    _sprite.setTexture(_texture);
}
Arena::~Arena()
{
}
void Arena::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    target.draw(_sprite);
}
// ---------------------------
}

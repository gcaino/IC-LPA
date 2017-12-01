#ifndef ARENA_H
#define ARENA_H
// -----------------------------------
#include <SFML\Graphics.hpp>
// -----------------------------------
namespace lpa
{
    class Arena : public sf::Drawable
    {
    private:
        sf::Sprite      _sprite;
        sf::Texture     _texture;

    public:
        Arena();
        ~Arena();

        virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
    };
}
#endif // ARENA_H

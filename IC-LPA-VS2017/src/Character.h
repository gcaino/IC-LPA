#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H
// -----------------------------------------
#include <SFML\Graphics.hpp>
// -----------------------------------------
namespace lpa
{
	class Character : public sf::Drawable
	{
	protected:
		sf::Vector2f	_position;
		float			_velocity;
		sf::Texture		_texture;
		sf::Sprite		_sprite;

	public:
		Character();
		virtual ~Character();

		virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
		virtual void update(sf::Time elapsedTime);
	};
}
#endif // GAMEOBJECT_H
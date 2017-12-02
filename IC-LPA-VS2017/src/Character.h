#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H
// -----------------------------------------
#include <SFML\Graphics.hpp>
#include "Constants.h"
// -----------------------------------------
using namespace Constants;

namespace lpa
{
	// Abstract Class
	class Character : public sf::Drawable
	{
	protected:
		sf::Vector2f	_position;
		sf::Vector2f	_prevPosition;
		float			_velocity;
		uint			_health;
		uint			_strength;
		bool			_alive;
		sf::Texture		_texture;
		sf::Sprite		_sprite;

	public:
		Character();
		virtual ~Character();

		sf::Sprite		getSprite() const							{ return _sprite; }
		sf::Vector2f	getPosition() const							{ return _position; }
		void			setPosition(sf::Vector2f newPosition)		{ _position = newPosition; }
		sf::Vector2f	getPrevPosition() const						{ return _prevPosition; }
		void			setPrevPosition(sf::Vector2f prevPosition)	{ _position = prevPosition; }
		bool			isAlive() const								{ return _alive; }
		void			setIsAlive(bool isAlive)					{ _alive = isAlive; }

		virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const = 0;
	};
}
#endif // GAMEOBJECT_H
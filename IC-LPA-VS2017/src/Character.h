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
		float			_velocity;
		uint			_health;
		uint			_strength;
		bool			_isAlive;
		sf::Texture		_texture;
		sf::Sprite		_sprite;

	public:
		Character();
		virtual ~Character();

		void setPosition(sf::Vector2f newPosition) { _position = newPosition; }
		bool getIsAlive() const { return _isAlive; }
		void setIsAlive(bool isAlive) { _isAlive = isAlive; }

		virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const = 0;
		virtual void update(sf::Time elapsedTime) = 0;
	};
}
#endif // GAMEOBJECT_H
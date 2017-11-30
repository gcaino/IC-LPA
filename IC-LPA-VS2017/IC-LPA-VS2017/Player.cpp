#include "Player.h"

Player::Player()
{
	if (!_texture.loadFromFile("assets/textures/2_knight_.png")) {}
	_sprite.setTexture(_texture);
}

Player::~Player()
{
}

void Player::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	target.draw(_sprite);
}
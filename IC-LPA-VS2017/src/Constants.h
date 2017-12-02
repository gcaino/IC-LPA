#ifndef CONSTANTS_H
#define CONSTANTS_H
// -----------------------------------------
#include <SFML\System.hpp>
#include <string>
// -----------------------------------------
namespace Constants
{
	typedef unsigned int uint;

    const uint WINDOW_WIDTH_MAX = 800;
    const uint WINDOW_HEIGHT_MAX = 600;
    const uint WAVE_MAX = 5;
	const uint ENEMY_MAX = 9;

	const std::string	texturesPath = "assets/textures/";

	const uint SPAWN_POINTS_MAX = 2;
	const sf::Vector2f SPAWN_POINT_UNO(0, WINDOW_HEIGHT_MAX * 0.6f);
	const sf::Vector2f SPAWN_POINT_DOS(WINDOW_WIDTH_MAX - 100, WINDOW_HEIGHT_MAX * 0.6f);
	const sf::Time SPAWN_TIME = sf::seconds(7.f);

	const float ENEMY_VELOCITY = 20.f;
	const sf::Time ENEMY_SPEED_ATTACK = sf::seconds(3.f);
	const sf::Time PLAYER_SPEED_ATTACK = sf::seconds(1.f);
}
#endif // !CONSTANTS_H


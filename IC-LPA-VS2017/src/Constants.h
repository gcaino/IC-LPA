#ifndef CONSTANTS_H
#define CONSTANTS_H
// -----------------------------------------
#include <string>
#include <SFML\System.hpp>
// -----------------------------------------
namespace Constants
// -----------------------------------------
{
// -----------------------------------------
typedef unsigned int uint;

const uint WINDOW_WIDTH_MAX = 1024;
const uint WINDOW_HEIGHT_MAX = 768;

const std::string	texturesPath = "assets/textures/";
const std::string	texturesPathMousePointerSword = "assets/textures/mouse-pointer-32.png";
const std::string	texturesPathMousePointerAxe = "assets/textures/mouse-pointer-axe-32.png";
const std::string	texturePathArena = "assets/textures/arena-01-1024.png";
const std::string	texturePathArenaCollision = "assets/textures/arena-01-collision-1024.png";
const std::string	texturePathPlayer = "assets/textures/knight-01.png";
const std::string	texturePathOrc = "assets/textures/orc-01.png";
// -----------------------------------------
}
// -----------------------------------------
#endif // !CONSTANTS_H


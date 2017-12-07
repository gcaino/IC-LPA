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
const std::string	texturePathOrc = "assets/textures/orc-01.png";
const std::string	texturePathRedBlood = "assets/textures/spritesheets/effects/red-blood.png";
const std::string	texturePathGreenBlood = "assets/textures/spritesheets/effects/green-blood.png";

const std::string texturePlayerIdleAnimation = "assets/textures/spritesheets/player/knight-01-spritesheet-idle.png";
const std::string texturePlayerWalkAnimation = "assets/textures/spritesheets/player/knight-01-spritesheet-walk.png";
const std::string texturePlayerAttackAnimation = "assets/textures/spritesheets/player/knight-01-spritesheet-attack.png";
const std::string texturePlayerHurtAnimation = "assets/textures/spritesheets/player/knight-01-spritesheet-hurt.png";
const std::string texturePlayerDieAnimation = "assets/textures/spritesheets/player/knight-01-spritesheet-die.png";

const std::string textureOrcIdleAnimation = "assets/textures/spritesheets/enemies/orc-01-spritesheet-idle.png";
const std::string textureOrcWalkAnimation = "assets/textures/spritesheets/enemies/orc-01-spritesheet-walk.png";
const std::string textureOrcAttackAnimation = "assets/textures/spritesheets/enemies/orc-01-spritesheet-attack.png";
const std::string textureOrcHurtAnimation = "assets/textures/spritesheets/enemies/orc-01-spritesheet-hurt.png";
const std::string textureOrcDieAnimation = "assets/textures/spritesheets/enemies/orc-01-spritesheet-die.png";

// -----------------------------------------
}
// -----------------------------------------
#endif // !CONSTANTS_H


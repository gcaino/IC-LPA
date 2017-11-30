#ifndef GAMEWORLD_H
#define GAMEWORLD_H
#include "Player.h"

class GameWorld
{
private:
	Player _player;

public:
	GameWorld();
	~GameWorld();

	Player getPlayer() { return _player; }

	void update();
};

#endif // GAMEWORLD_H
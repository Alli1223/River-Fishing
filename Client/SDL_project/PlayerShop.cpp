#include "stdafx.h"
#include "PlayerShop.h"


PlayerShop::PlayerShop()
{
	setSize(500, 500);
	//setPosition(1000, 1000);
	setSpawnPoint(getRoomSize() / 2 * getTileSize(), getRoomSize() / 2 * getTileSize());
	setExitPoint(getRoomSize() / 2, getRoomSize());
	std::cout << "Spawn point: " << getRoomSize() / 2 * getTileSize() << " " << (getRoomSize() / 2) * getTileSize() << std::endl;
	std::cout << "Exit point: " << getRoomSize() / 2 * getTileSize() << " " << getRoomSize() * getTileSize() << std::endl;
	setEntrancePoint(getX(), getY());
}

PlayerShop::~PlayerShop()
{
}

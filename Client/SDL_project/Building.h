#pragma once
#include "Cell.h"
#include "Point.h"

class Building
{
public:
	//! Constructor
	Building();
	Building(json building);
	//! Destructor
	~Building();

	//! Tiles
	std::vector<std::vector<std::shared_ptr<Cell>>> tiles;
	//! GetPosition
	glm::vec2 getPosition() { return { x,y }; }
	//! get the position of the building
	int getX() { return x; }
	int getY() { return y; }
	//! Get the room size of the building
	int getRoomSize() { return roomSize; }
	//! get the size of the building
	int getWidth() { return width; }
	int getHeight() { return height; }

	//! Get and set spawn point for the building
	Point getSpawnPoint() { return spawnPoint; }
	Point setSpawnPoint(Point newSpawn) { return spawnPoint; }
	int setSpawnPoint(int x, int y) { return spawnPoint.setPosition(x, y); }
	//! Get and set exit point for the building
	Point getExitPoint() { return exitPoint; }
	Point setExitPoint(Point newExit) { return exitPoint; }
	int setExitPoint(int x, int y) { return exitPoint.setPosition(x, y); }
	//! Get return to level cell
	Point getReturnCell() { return returnCell; }
	Point setReturnPoint(Point newPoint) { return returnCell = newPoint; }
	int setReturnPoint(int x, int y) { return returnCell.setPosition(x, y); }
	//! Get and set the entrance point of the building
	Point getEntrancePoint() { return entrancePoint; }
	Point setEntrancePoint(Point newEntrance) { return entrancePoint = newEntrance; }
	int setEntrancePoint(int x, int y) { return entrancePoint.setPosition(x, y); }
	//! SetPosition of the building in the world
	int setPosition(int newX, int newY) { return x = newX, y = newY; }
	//! Set the size of the sprite
	int setSize(int newWith, int newHeight) { return width = newWith, height = newHeight; }
	//! Get the tile size in the building
	int getTileSize() { return tileSize; }
	//! Whether the house is viable in the main level
	bool isVisable = false;

	enum BuildingType
	{
		noBuilding,
		blacksmith,
		playerShop
	} buildingType;

private:
	int x, y;
	int width, height;
	int roomSize = 10;
	int tileSize = 50;
	
	Point spawnPoint;
	Point exitPoint;
	Point returnCell;
	Point entrancePoint;

};


#pragma once
#include "Cell.h"
#include "Chunk.h"
#include "Point.h"
#include "Camera.h"
#include "ProceduralTerrain.h"
#include "Building.h"
#include "PlayerShop.h"

//! This class generates the base of the level 
/*!
This class creates a vector of vector of shared pointers to cells
*/

class Level
{
public:
	//! A constructor
	Level();
	//! A deconstructor 
	~Level();

	static Level level;

	void Level::CreateLevel(int x, int y);
	
	//! The base grid that contains the cells
	std::vector<std::vector<std::shared_ptr<Cell>>> tiles;
	std::vector<std::shared_ptr<Building>> buildings;

	int getCellSize() { return cellSize; }
	int setCellSize(int newCellSize) { return cellSize = newCellSize; }
	int setCellsInWindowSize(int xVal, int yVal) { return cellsInWindow.x = xVal, cellsInWindow.y = yVal; }
	glm::ivec2 cellsInWindow;
protected:
	
	int levelWidth, levelHeight;
	int cellSize = 50;
	int defaultLevelSize = 50;
	PlayerShop shop;
};
#pragma once
#include "Texture.h"
#include "Timer.h"

class Cell
{
public:
	//! A constructor
	Cell();
	//! An alternate constructor
	/*!
	This constructor requires an X and Y for the Cell 
	*/
	Cell(int x, int y);
	Cell(json cellData);
	//! A destructor 
	~Cell();
	//! Gets the cells data and returns it in json format
	json getCellData();

	// Getter functions
	//! Gets the Cell's X value
	int getX() const { return x; }
	//! Gets the Cell's Y value
	int getY() const { return y; }

	
	// Setter functions
	//! Sets the Cells X value
	int setX(int newX) { return x = newX; }
	//! Sets the Cells Y value
	int setY(int newY) { return y = newY; }
	//! Sets the Cells X and Y values
	int setPos(int newX, int newY) { return x = newX, y = newY; }

	//! Whether the cell is part of a room
	bool isRoom = false;
	//! Whether the cell is walkable
	bool isWalkable = true;

	//! Variables used for terrain
	double terrainElevationValue = 0;
	double climate = 0;



	bool isGrass = false;
	bool isLongGrass = false;
	bool isLongGrass2 = false;
	bool isDirt = false;

	bool isTree = false;
	bool isWheat = false;

	bool isWater = false;
	bool isFishingBob = false;
	bool isSand = false;
	bool isSnow = false;
	bool isWood = false;
	bool isStone = false;
	bool isRock = false;

	
	enum PlantStage
	{
		noPlant,
		PlantStageOne,
		PlantStageTwo,
		PlantStageThree,
		PlantStageFour,
		PlantStageFive,
		PlantStageSix,
		PlantStageSeven
	} plantStage;

	enum TreeType
	{
		fernTree,
		oakTree,
		mapleTree,
		pineTree
	} treeType;
	

	enum GroundType
	{
		noLight,
		campFire,
		torch,
		streetLight,
	} groundType;

	Timer plantTimer;
	
	bool isVegetation = false;
	bool isFlower1 = false;
	bool isFlower2 = false;
	bool isBerryPlant = false;
	bool isBush = false;

	bool isTown = false;
	bool isBuilding = false;
	bool isStoneWall = false;
	bool isWoodFence = false;

		enum orientation
		{
			topLeft,
			topMiddle,
			topRight,
			middleLeft,
			middle,
			middleRight,
			bottomLeft,
			bottomMiddle,
			bottomRight,

			inv_topLeft,
			inv_topRight,
			inv_bottomLeft,
			inv_bottomRight
		} orientation;

private:
	//! The Cells X and Y values
	int x = 0, y = 0;
};
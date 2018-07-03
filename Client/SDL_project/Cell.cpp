#include "stdafx.h"
#include "Cell.h"


Cell::Cell()
{
}

// Create with a position
Cell::Cell(int x, int y)
{
	setX(x);
	setY(y);
}

// Create with json data
Cell::Cell(json cellData)
{
	
	int x = cellData.at("X").get<int>();
	int y = cellData.at("Y").get<int>();
	setPos(x, y);

	int plantGrowthStage;

	if (cellData.count("Grass") > 0)
		isGrass = cellData.at("Grass").get<bool>();
	if (cellData.count("Water") > 0)
		isWater = cellData.at("Water").get<bool>();
	if (cellData.count("Sand") > 0)
		isSand = cellData.at("Sand").get<bool>();
	if (cellData.count("Fence") > 0)
		isWoodFence = cellData.at("Fence").get<bool>();
	if (cellData.count("Dirt") > 0)
		isDirt = cellData.at("Dirt").get<bool>();
	if (cellData.count("Wheat") > 0)
		isWheat = cellData.at("Wheat").get<bool>();
	if (cellData.count("Wood") > 0)
		isWood = cellData.at("Wood").get<bool>();
	if (cellData.count("Stone") > 0)
		isStone = cellData.at("Stone").get<bool>();
	if (cellData.count("StoneWall") > 0)
		isStoneWall = cellData.at("StoneWall").get<bool>();
	if (cellData.count("PlantStage") > 0)
		plantStage = (Cell::PlantStage)cellData.at("PlantStage").get<int>();


}

Cell::~Cell(){
}

//TO modify these values, the other values in classes gameSettings.loadGameFromSave and Level.getCellFromJson need to be modified
json Cell::getCellData()
{	
	json cellData;
	cellData["X"] = x;
	cellData["Y"] = y;
	if(isWoodFence)
		cellData["Fence"] = isWoodFence;
	if(isDirt)
		cellData["Dirt"] = isDirt;
	if(isGrass)
		cellData["Grass"] = isGrass;
	if (isWater)
		cellData["Water"] = isWater;
	if (isSand)
		cellData["Sand"] = isSand;
	if(isWood)
		cellData["Wood"] = isWood;
	if(isStone)
		cellData["Stone"] = isStone;
	if (isRock)
		cellData["Rock"] = isRock;
	if (isTree)
		cellData["Tree"] = isTree;
	if (isFlower1)
		cellData["Flower1"] = isFlower1;
	if (isFlower2)
		cellData["Flower2"] = isFlower2;
	if(isStoneWall)
		cellData["StoneWall"] = isStoneWall;
	if(isWheat)
		cellData["Wheat"] = isWheat;
	if(plantStage >= 0 && plantStage< 10)
		cellData["PlantStage"] = plantStage;

	
	return cellData;
}


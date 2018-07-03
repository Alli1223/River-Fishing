#include "stdafx.h"
#include "Building.h"


Building::Building()
{
	for (int x = 0; x < roomSize; x++)
	{
		std::vector<std::shared_ptr<Cell>> column;

		tiles.push_back(column);
		for (int y = 0; y < roomSize; y++)
		{
			// Populates the column with pointers to cells
			Cell cell(x, y);

			cell.isWalkable = true;
			cell.isWood = true;

			auto sharedCell = std::make_shared<Cell>(cell);
			tiles[x].push_back(sharedCell);
		}
	}
}

Building::Building(json buildingData)
{
	setSpawnPoint(getRoomSize() / 2 * getTileSize(), getRoomSize() / 2 * getTileSize());
	setExitPoint(getRoomSize() / 2, getRoomSize());
	x = buildingData.at("X").get<int>();
	y = buildingData.at("Y").get<int>();
	setPosition(x, y);
	width = buildingData.at("Width").get<int>();
	height = buildingData.at("Height").get<int>();
	isVisable = buildingData.at("Visable").get<bool>();
	entrancePoint.setPosition(buildingData.at("EntranceX").get<int>(), buildingData.at("EntranceY").get<int>());

	// Create the tiles to be overwitten
	for (int x = 0; x < roomSize; x++)
	{
		std::vector<std::shared_ptr<Cell>> column;

		tiles.push_back(column);
		for (int y = 0; y < roomSize; y++)
		{
			// Populates the column with pointers to cells
			Cell cell(x, y);

			cell.isWalkable = true;

			auto sharedCell = std::make_shared<Cell>(cell);
			tiles[x].push_back(sharedCell);
		}
	}


	// Get the tiles
	json tileData = buildingData.at("Tiles");
	for (auto& tile : tileData)
	{
		Cell newCell;
		newCell = Cell(tile);
		tiles[newCell.getX()][newCell.getY()] = std::make_shared<Cell>(newCell);
	}
}



Building::~Building()
{
}

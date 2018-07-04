#include "stdafx.h"
#include "Level.h"

// Instantiate static level
Level Level::level;

Level::Level()
{
}



Level::~Level()
{
}


// Creates a grid of cells at a specified location
void Level::CreateLevel(int x, int y)
{

	for (int x = 0; x < Level::defaultLevelSize; x++)
	{
		std::vector<std::shared_ptr<Cell>> column;

		Level::tiles.push_back(column);
		for (int y = 0; y < Level::defaultLevelSize; y++)
		{
			// Populates the column with pointers to cells
			Cell cell(x, y);

			// Create the river
			if (x > (Level::cellsInWindow.x / 2) - 5 && x < (Level::cellsInWindow.x / 2) + 5)
			{
				cell.isWater = true;
				cell.isWalkable = false;
			}
			else
			{
				cell.isGrass = true;
				cell.isWalkable = true;
			}

			auto sharedCell = std::make_shared<Cell>(cell);
			Level::tiles[x].push_back(sharedCell);
		}
	}

	shop.setPosition(0, Level::cellsInWindow.x / 2);
	
}
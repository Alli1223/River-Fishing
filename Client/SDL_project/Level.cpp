#include "stdafx.h"
#include "Level.h"

Level::Level()
{

}



Level::~Level()
{
}


// Creates a grid of cells at a specified location
void Level::CreateLevel(int x, int y)
{

	for (int x = 0; x < defaultLevelSize; x++)
	{
		std::vector<std::shared_ptr<Cell>> column;

		tiles.push_back(column);
		for (int y = 0; y < defaultLevelSize; y++)
		{
			// Populates the column with pointers to cells
			Cell cell(x, y);

			cell.isWalkable = true;
			cell.isGrass = true;

			auto sharedCell = std::make_shared<Cell>(cell);
			tiles[x].push_back(sharedCell);
		}
	}
}
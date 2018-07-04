#include "stdafx.h"
#include "ProceduralTerrain.h"


ProceduralTerrain::ProceduralTerrain()
{
	//set random seed to seednumber
	srand(seed);

	Elevation.GenerateNoise(elevationSeed);
	ElevationLayerTwo.GenerateNoise(elevationSeed - 1234);
	ElevationLayerThree.GenerateNoise(elevationSeed + 1234);


	forrestNoise.GenerateNoise(forrestSeed);
	riverNoise.GenerateNoise(riverSeed);
	riverNoiseLayerTwo.GenerateNoise(riverSeed / 2);
}


ProceduralTerrain::~ProceduralTerrain()
{
}

void ProceduralTerrain::spawnRandomTrees()
{
	for (int i = numberOfTrees; i > 0; i--)
	{
		int x = rand() % Level::level.tiles.size();
		int y = rand() % Level::level.tiles[0].size();
		if (!Level::level.tiles[x][y]->isVegetation && !Level::level.tiles[x][y]->isWater)
		{
			Level::level.tiles[x][y]->isVegetation = true;
			Level::level.tiles[x][y]->isWalkable = false;

			Level::level.tiles[x][y]->isTree = true;
			
			int treeType = rand() % 3;
			if (treeType <= 0)
			{
				Level::level.tiles[x][y]->isTree = true;
				Level::level.tiles[x][y]->isWalkable = false;
				Level::level.tiles[x][y]->treeType = Cell::fernTree;
			}
			else if (treeType == 1)
			{
				Level::level.tiles[x][y]->isTree = true;
				Level::level.tiles[x][y]->isWalkable = false;
				Level::level.tiles[x][y]->treeType = Cell::pineTree;
			}
			else
			{
				Level::level.tiles[x][y]->isTree = true;
				Level::level.tiles[x][y]->treeType = Cell::oakTree;
				Level::level.tiles[x][y]->isWalkable = false;
			}
		}
	}
}

void ProceduralTerrain::spawnRandomVegetation()
{	
	for (int i = numberOfPlants; i > 0; i--)
	{
		int x = rand() % Level::level.tiles.size();
		int y = rand() % Level::level.tiles[0].size();
		
		if (!Level::level.tiles[x][y]->isVegetation && !Level::level.tiles[x][y]->isWater && !Level::level.tiles[x][y]->isSand)
		{
			Level::level.tiles[x][y]->isVegetation = true;
			int vegType = rand() % 3;

			switch (vegType)
			{
			case 0:
				Level::level.tiles[x][y]->isFlower1 = true;
				break;
			case 1:
				Level::level.tiles[x][y]->isFlower2 = true;
				break;
			case 2:
				Level::level.tiles[x][y]->isRock = true;
				break;
			}
		}
	}
}


void ProceduralTerrain::populateTerrain(std::vector<std::vector<std::shared_ptr<Cell>>> tiles)
{
	//Renders all he cells

	//Generate the grass
	//generateGround();
	//GenerateCellOrientations();

	//Cant spawn random items because that will cause de-sync between clients
	spawnRandomTrees();
	spawnRandomVegetation();
}

//TODO: Put all constant values in the headder
void ProceduralTerrain::generateGround()
{
	for (int x = 0; x < Level::level.tiles.size(); x++)
		for (int y = 0; y < Level::level.tiles[0].size(); y++)
		{


			float noiseX = Level::level.tiles[x][y]->getX();
			float noiseY = Level::level.tiles[x][y]->getY();

			// Layerd noise
			double terrainElevation = Elevation.noise((double)noiseX / terrainNoiseOffest, (double)noiseY / terrainNoiseOffest, 0.0) * 20.0;
			double terrainElevationTwo = ElevationLayerTwo.noise((double)noiseX / terrainNoiseOffest / 2.0, (double)noiseY / terrainNoiseOffest / 2.0, 0.0) * 20.0;
			double terrainElevationThree = ElevationLayerThree.noise((double)noiseX, (double)noiseY, 0.0) * 20.0;
			double sNoise = simNoise.noise(noiseX / 40, noiseY / 40);

			terrainElevation = sNoise + terrainElevationTwo + terrainElevation + terrainElevationThree + 2;
			double climate = sin(Level::level.tiles[x][y]->getY() / 500.0);


			double fNoise = forrestNoise.noise((double)noiseX / forrestNoiseOffset, (double)noiseY / forrestNoiseOffset, 0.0) * 20.0;
			fNoise += simNoise.noise(noiseX / forrestJaggedness, noiseY / forrestJaggedness);

			double gNoise = grassNoise.noise(noiseX / 15, noiseY / 15) + fNoise;
			double rNoise = (riverNoise.noise((double)noiseX / 300.0, (double)noiseY / 300.0, 0.0) * 20.0) + (riverNoiseLayerTwo.noise((double)noiseX / 300.0, (double)noiseY / 300.0, 0.0) * 20.0);
			rNoise += simNoise.noise(noiseX / riverBendyness, noiseY / riverBendyness);

			//set the cells terrain value
			Level::level.tiles[x][y]->terrainElevationValue = terrainElevation;

			if (climate > 0 || !thereIsClimate)
			{
				// TERRAIN NOISE
				if (terrainElevation >= -1.8 && terrainElevation <= 20.0)
				{
					Level::level.tiles[x][y]->isGrass = true;

				}
				else if (terrainElevation >= -2.3 && terrainElevation < -1.8)
				{
					Level::level.tiles[x][y]->isSand = true;
					Level::level.tiles[x][y]->isGrass = false;
					Level::level.tiles[x][y]->isWater = false;
				}
				else if (terrainElevation < -2.3)
				{
					Level::level.tiles[x][y]->isWater = true;
					Level::level.tiles[x][y]->isWalkable = false;
				}
				else if (terrainElevation > 10.0 && terrainElevation < 20.0)
				{
					Level::level.tiles[x][y]->isStone = true;
				}
				else if (terrainElevation > 20.0)
				{
					Level::level.tiles[x][y]->isSnow = true;
				}

				// FORREST NOISE ///////////
				// If spawn something cool when the forrest value is greater than the max set ( the center of a forrest)
				if (Level::level.tiles[x][y]->isGrass && fNoise > 14.0 && rand() % numberOfTrees == 1)
				{
					Level::level.tiles[x][y]->isTree = true;
					Level::level.tiles[x][y]->treeType == Cell::fernTree;
					Level::level.tiles[x][y]->isWalkable = false;
				}
				else if (Level::level.tiles[x][y]->isGrass && fNoise > 8.0 && fNoise < 12.0 && rand() % numberOfTrees == 1)
				{
					Level::level.tiles[x][y]->isTree = true;
					Level::level.tiles[x][y]->treeType == Cell::oakTree;
					Level::level.tiles[x][y]->isWalkable = false;
				}

				// Grass noise
				if (Level::level.tiles[x][y]->isGrass && gNoise > 4.0 && gNoise < 10.0)
				{
					int randSpawn = rand() % 10;
					if (randSpawn == 0)
						Level::level.tiles[x][y]->isLongGrass = true;
					else if (randSpawn == 1)
						Level::level.tiles[x][y]->isFlower1 = true;
					else if (randSpawn == 2)
						Level::level.tiles[x][y]->isFlower2 = true;
					else if (randSpawn == 3)
						Level::level.tiles[x][y]->isLongGrass2 = true;
				}


				// RIVER NOISE
				if (rNoise > 0.5 && rNoise < 1.0)
				{
					Level::level.tiles[x][y]->isWater = true;
					Level::level.tiles[x][y]->isGrass = false;
					Level::level.tiles[x][y]->terrainElevationValue = -2.1;

				}
				/*
				else if (rNoise >= 1.0 && rNoise < 1.3 || rNoise >= 0.3 && rNoise <= 0.5 && Level::level.tiles[x][y]->isGrass)
				{
					Level::level.tiles[x][y]->isSand = true;
					Level::level.tiles[x][y]->isGrass = false;
				}
				*/
			}

			else
			{
				if (terrainElevation > -1.8 && terrainElevation < 13.0)
					Level::level.tiles[x][y]->isSnow = true;
				else if (terrainElevation < -2)
					Level::level.tiles[x][y]->isWater = true; // Change to ice
			}
		}
}

void ProceduralTerrain::GenerateCellOrientations()
{
	/*
	int chunkSize = Level::level.getChunkSize();


	// In one row
	if (x - 1 >= 0 && x + 1 < chunkSize)
	{
		if (Level::level.tiles[x][y]->isWater && Level::level.tiles[x - 1][y]->isGrass)
		{
			Level::level.tiles[x][y]->orientation = Cell::orientation::middleLeft;
		}
		if (Level::level.tiles[x][y]->isWater && Level::level.tiles[x + 1][y]->isGrass)
		{
			Level::level.tiles[x][y]->orientation = Cell::orientation::middleLeft;
		}

		// Center of Chunk
		if (y - 1 >= 0 && y + 1 < chunkSize)
		{
			// Top Left
			if (Level::level.tiles[x][y]->isWater && Level::level.tiles[x - 1][y - 1]->isGrass && Level::level.tiles[x][y - 1]->isGrass && Level::level.tiles[x - 1][y]->isGrass)
			{
				Level::level.tiles[x][y]->orientation = Cell::orientation::topLeft;
			}
			else if (Level::level.tiles[x][y]->isWater && Level::level.tiles[x][y - 1]->isGrass)
			{
				Level::level.tiles[x][y]->orientation = Cell::orientation::topMiddle;
			}
			else if (Level::level.tiles[x][y]->isWater && Level::level.tiles[x + 1][y - 1]->isGrass && Level::level.tiles[x][y - 1]->isGrass && Level::level.tiles[x + 1][y]->isGrass)
			{
				Level::level.tiles[x][y]->orientation = Cell::orientation::topRight;
			}
			else if (Level::level.tiles[x][y]->isWater && Level::level.tiles[x - 1][y]->isGrass)
			{
				Level::level.tiles[x][y]->orientation = Cell::orientation::middleLeft;
			}
			else if (Level::level.tiles[x][y]->isWater && Level::level.tiles[x + 1][y]->isGrass)
			{
				Level::level.tiles[x][y]->orientation = Cell::orientation::middleRight;
			}
			else if (Level::level.tiles[x][y]->isWater && Level::level.tiles[x][y + 1]->isGrass)
			{
				Level::level.tiles[x][y]->orientation = Cell::orientation::bottomMiddle;
			}
			
		}
	}
	else if (y - 1 >= 0 && y + 1 < chunkSize)
	{
		if (Level::level.tiles[x][y]->isWater && Level::level.tiles[x][y - 1]->isGrass)
			Level::level.tiles[x][y]->orientation = Cell::orientation::topMiddle;
		if (Level::level.tiles[x][y]->isWater && Level::level.tiles[x][y + 1]->isGrass)
			Level::level.tiles[x][y]->orientation = Cell::orientation::topMiddle;

	}
	*/
}

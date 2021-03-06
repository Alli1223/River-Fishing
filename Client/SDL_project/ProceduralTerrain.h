#pragma once
#include "cell.h"
#include "PerlinNoise.h"
#include "SimplexNoise.h"
#include "Chunk.h"
#include "point.h"
#include "Camera.h"
#include "Level.h"


class ProceduralTerrain
{
public:
	ProceduralTerrain();
	~ProceduralTerrain();
	//! Elevation noise
	PerlinNoise Elevation;
	PerlinNoise ElevationLayerTwo;
	PerlinNoise ElevationLayerThree;
	SimplexNoise simNoise;
	SimplexNoise grassNoise;

	//! Other noise generations
	PerlinNoise forrestNoise;
	PerlinNoise riverNoise;
	PerlinNoise riverNoiseLayerTwo;


	//! Getters and setters for seed
	int getSeed() { return seed; }
	int setSeed(int newSeed) { return seed = newSeed; }

	//! function that calls the functions below
	void populateTerrain(std::vector<std::vector<std::shared_ptr<Cell>>> tiles);
	//! Spawns the trees in a chunk
	void spawnRandomTrees();
	//! Spawn the vegetation
	void spawnRandomVegetation();
	//! Generate the ground based of the elevation and climate
	void generateGround();
	void GenerateCellOrientations();

private:
	//! Seed values are random
	int seed = 5432;
	int forrestSeed = seed + 30;
	int elevationSeed = seed + 36945;
	int riverSeed = seed + 1255;

	// Lower is more
	int riverBendyness = 50;
	int forrestJaggedness = 50;

	//! Needs work
	//! Makes the sin of the y cell pos to be the climate
	//! Turns grass into snow and water into ice
	bool thereIsClimate = false;

	float terrainNoiseOffest = 180.0;
	float forrestNoiseOffset = 180.0;

	float forrestAmplifier = 1.5;

	// Number of items randomly placed in chunk
	int numberOfTrees = 100;
	int numberOfPlants = 1000;

};


#pragma once
#include "Cell.h"
class Chunk
{
public:
	Chunk();
	~Chunk();
	Chunk::Chunk(int initX, int initY);
	int getChunkSize() { return chunkSize; }
	std::vector<std::vector<std::shared_ptr<Cell>>> tiles;

	int getX() { return x; }
	int getY() { return y; }
	UINT32 plantGrowSpeed;
	
private:
	int x = 0;
	int y = 0;
	int chunkSize = 8;
	
	std::string chunkID;
};


#pragma once
#include "GameObject.h"
#include "PathFinder.h"
class Animal :
	public GameObject
{
public:
	Animal();
	~Animal();

	void move(glm::ivec2 goal);

	//! Pathfinder for the animal
	Pathfinder pathfinder;
	int pathPointIterator;
	void render(SDL_Renderer * renderer);

};


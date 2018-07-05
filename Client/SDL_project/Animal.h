#pragma once
#include "GameObject.h"
#include "PathFinder.h"
class Animal :
	public GameObject
{
public:
	Animal();
	~Animal();

	void FindPath(glm::ivec2 goal);
	void MoveTowards(glm::vec2 goal);
	//! Pathfinder for the animal
	Pathfinder pathfinder;
	int pathPointIterator;
	void render(SDL_Renderer * renderer);
protected:
	bool movingToDest = false;
	bool rotateTowardsDest = true;
	glm::vec2 currentGoal;

};


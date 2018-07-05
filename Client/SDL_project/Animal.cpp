#include "stdafx.h"
#include "Animal.h"


Animal::Animal() 
{
}


Animal::~Animal()
{
}

void Animal::MoveTowards(glm::vec2 goal)
{
	if (currentGoal != goal)
	{
		movingToDest = true;
		currentGoal = goal;
	}
		
	
	float deltaX = getX() - currentGoal.x;
	float deltaY = getY() - currentGoal.y;
	
	// calculate length (pythagoras)
	float length = sqrt(deltaX * deltaX + deltaY * deltaY);

	// Normalize 
	deltaX /= length;
	deltaY /= length;

	// Multiply direction by magnitude 
	deltaX *= getSpeed();
	deltaY *= getSpeed();

	// Calculate rotation
	if (rotateTowardsDest)
	{
		float angleInDegrees = atan2(deltaY, deltaX) * 180.0 / PI;

		// Apply correction to rotation
		rotation = angleInDegrees + 90;
	}

	// Check bounds
	if (getX() - deltaX > 0 && getY() - deltaY > 0)
	{
		setX(getX() - deltaX);
		setY(getY() - deltaY);
	}
	if ((int)getX() == (int)currentGoal.x && (int)getY() == (int)currentGoal.y)
		movingToDest = false;
}

void Animal::FindPath(glm::ivec2 goal)
{
	// If no path, then create it
	if (pathfinder.path.size() == 0)
		pathfinder.findPath(Level::level, (glm::ivec2)this->getPosition(), goal);
	else
	{
		// If path has been created

		float deltaY = getY() - pathfinder.path[pathPointIterator].getY() * 50.0;
		float deltaX = getX() - pathfinder.path[pathPointIterator].getX() * 50.0;

		// calculate length (pythagoras)
		float length = sqrt(deltaX * deltaX + deltaY * deltaY);

		// Normalize 
		deltaX /= length;
		deltaY /= length;

		// Multiply direction by magnitude 
		deltaX *= getSpeed();
		deltaY *= getSpeed();

		// Check bounds
		if (getX() - deltaX > 0 && getY() - deltaY > 0)
		{
			setX(getX() - deltaX);
			setY(getY() - deltaY);
		}

		// If the agent has reached the end of the path
		if (pathPointIterator >= pathfinder.path.size())
		{
			pathfinder.path.erase(pathfinder.path.begin(), pathfinder.path.end());
			
		}
		// When the object reaches the point in the path
		// Then iterate
		int x, y;
		x = (int)getX(), y = (int)getY();
		if ((int)getX() / Level::level.getCellSize() == pathfinder.path[pathPointIterator].getX() && (int)getY() / Level::level.getCellSize() == pathfinder.path[pathPointIterator].getY())
			pathPointIterator++;

		

	}
	
}

void Animal::render(SDL_Renderer * renderer)
{
	if(pathfinder.path.size() > 0)
		FindPath(pathfinder.currentGoal);
}
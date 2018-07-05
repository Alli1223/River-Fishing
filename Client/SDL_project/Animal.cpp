#include "stdafx.h"
#include "Animal.h"


Animal::Animal() 
{
}


Animal::~Animal()
{
}

void Animal::move(glm::ivec2 move)
{
	// If no path, then create it
	if (pathfinder.path.size() == 0)
		pathfinder.findPath(Level::level, (glm::ivec2)this->getPosition(), (glm::ivec2)this->getPosition());
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

		// Move
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
		if (getX() / Level::level.getCellSize() == pathfinder.path[pathPointIterator].getX() && getY() / Level::level.getCellSize() == pathfinder.path[pathPointIterator].getY())
			pathPointIterator++;

		

	}
	
}

void Animal::render(SDL_Renderer * renderer)
{

}
#include "stdafx.h"
#include "Character.h"


Character::Character()
{
}


Character::~Character()
{
}


void Character::Move(int newX, int newY)
{
	
}

void Character::Update(Level& level)
{
	// Set agents cell x & y tile values & point values
	int cellSize = level.getCellSize();
	setCellX(getX() / level.getCellSize());
	setCellY(getY() / level.getCellSize());
	getCharacterPointLocation() = Point(getCellX(), getCellY());

	// Enter the building
	int entranceSize = 50;
	for (int i = 0; i < level.buildings.size(); i++)
	{
		if (isInBuilding)
		{
			setCellX(getX() / level.buildings[i]->getTileSize());
			setCellY(getY() / level.buildings[i]->getTileSize());
		}

		if (getX() > level.buildings[i]->getEntrancePoint().getX() && getX() < level.buildings[i]->getEntrancePoint().getX() + entranceSize)
			if (getY() > level.buildings[i]->getEntrancePoint().getY() && getY() < level.buildings[i]->getEntrancePoint().getY() + entranceSize)
			{
				isInBuilding = true;
				level.buildings[i]->isVisable = false;
				level.buildings[i]->setReturnPoint(Point(getX() - 50, getY())); // offset return point by 50 to avoid re-entering
				setPosition(level.buildings[i]->getSpawnPoint().getX(), level.buildings[i]->getSpawnPoint().getY());
				break;
			}

		// If player is at the exit
		if (isInBuilding)
			if (getCellX() == level.buildings[i]->getExitPoint().getX() && getCellY() == level.buildings[i]->getExitPoint().getY())
			{
				isInBuilding = false;
				level.buildings[i]->isVisable = true;
				setPosition(level.buildings[i]->getReturnCell().getX(), level.buildings[i]->getReturnCell().getY());
			}
	}

	// ROTATE AGENT /////
	if (incrementalRotating)
	{

		if (rotation == 360 - rotationSpeed || rotation == 360)
			rotation = 0;
		if (rotation == -90 - rotationSpeed || rotation == -90)
			rotation = 270;
		// Perform agent rotation based on player input
		if (rotation != targetRotation)
		{
			// Edge case
			if (rotation == 270 && targetRotation == 0)
				targetRotation = 360;
			if (rotation == 0 && targetRotation == 270)
				targetRotation = -90;

			if (rotation < targetRotation)
				rotation += rotationSpeed;
			else if (rotation > targetRotation)
				rotation -= rotationSpeed;
		}
	}
}


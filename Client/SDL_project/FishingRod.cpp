#include "stdafx.h"
#include "FishingRod.h"


FishingRod::FishingRod() : fishingRodTexture(ResourceManager::fishTextureLocation + "rod.png"), castingBar("Resources\\Sprites\\SpriteSheets\\Items\\fishingPole.png")
{
	// Set texture settings
	objectTexture.atlasType = Texture::TextureType::Sprite;
	this->objectTexture = fishingRodTexture;
	

}


FishingRod::~FishingRod()
{
}

void FishingRod::CastLine()
{
	startCast = true;

	// If the player hsa started the cast then rotate
	if (playerRotation == maxRotate)
	{
		if (rotation < maxRotate)
			rotation++;
	}
	else if (playerRotation == 270)
	{
		if (rotation > -maxRotate || rotation == 0)
		{
			rotation--;
		}
	}
}

void FishingRod::SpawnBobber()
{
	int cellSize = Level::level.getCellSize();
	// Left
	if(rotation == 90)
		if (Level::level.tiles[getX() / cellSize - castingDistance][getY() / cellSize]->isWater)
		{
			bobber.setPosition((getX() / cellSize - castingDistance) * cellSize, getY());
			bobber.setSize(25);
		}

	// Right
	if (rotation == 270)
		if (Level::level.tiles[getX() / cellSize + castingDistance][getY() / cellSize]->isWater)
		{

		}
}

void FishingRod::UpdateRod()
{
	// Cast to the left
	if (playerRotation == 90)
	{
		castLeftOrRight = true;
		if (startCast == false && rotation >= 0)
		{
			//Slowly put the rod down
			if (!casting)
				rotation--;
			// start the casting throw
			if (casting)
				rotation -= castingSpeed;
		}
		//if the rotation has reached the max then cast
		else if (rotation >= maxRotate)
			casting = true;
		// if the player stops the cast reset

		if (casting)
		{
			SpawnBobber();
		}
	}

	// Cast to the right
	if (playerRotation == 270)
	{
		castLeftOrRight = false;
		if (startCast == false && rotation <= 0)
		{
			//Slowly put the rod down
			if (!casting)
				rotation++;
			// start the casting throw
			if (casting)
				rotation += castingSpeed;
		}
		//if the rotation has reached the max then cast
		else if (rotation <= -maxRotate)
			casting = true;
		// if the player stops the cast reset

		if (casting)
		{
			SpawnBobber();
		}
	}

	
}

void FishingRod::render(SDL_Renderer* renderer)
{
	UpdateRod();
	
	
	// Render casting bar
	castingBar.render(renderer, this->getX() - Camera::camera.getX(), this->getY() - Camera::camera.getY() - 50, castingLevel, 10);

	// Render fishingrod
	fishingRodTexture.renderRotation(renderer, this->getX() - Camera::camera.getX(), this->getY() - Camera::camera.getY(), this->getWidth(), this->getHeight(), rotation, castLeftOrRight);

	bobber.render(renderer);

	startCast = false;
}
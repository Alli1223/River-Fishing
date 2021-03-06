#include "stdafx.h"
#include "FishingRod.h"


FishingRod::FishingRod() : fishingRodTexture(ResourceManager::fishTextureLocation + "rod.png"), castingBar("Resources\\Sprites\\SpriteSheets\\Items\\fishingPole.png")
{
	// Set texture settings
	objectTexture.atlasType = Texture::TextureType::Sprite;
	this->objectTexture = fishingRodTexture;
	bobber.setPosition(-100, -100);
	

}


FishingRod::~FishingRod()
{
}

void FishingRod::CastLine()
{

	startCast = true;

	// If the player hsa started the cast then rotate
	if (playerRotation == 90)
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

	// reel in the bobber
	if (waitingForFish && rotation > -maxRotate / 2 && rotation < maxRotate / 2)
	{
		float lerp_x = bobber.getX() + (getX() - bobber.getX()) * 0.005f;
		float lerp_y = bobber.getY() + (getY() - bobber.getY()) * 0.005f;

		bobber.setX(lerp_x);
		bobber.setY(lerp_y);

	}

}

void FishingRod::SpawnBobber()
{
	// Create the bobber if we don't already have a line
	if (!waitingForFish)
	{
		int cellSize = Level::level.getCellSize();
		// Left
		if (playerRotation == 90)
			if (Level::level.tiles[getX() / cellSize - castingDistance][getY() / cellSize]->isWater)
			{
				bobber.setPosition((getX() / cellSize - castingDistance) * cellSize, getY() + (rand() % 50) + 25);
			}

		// Right
		if (playerRotation == 270)
			if (Level::level.tiles[getX() / cellSize + castingDistance][getY() / cellSize]->isWater)
			{
				bobber.setPosition((getX() / cellSize + castingDistance) * cellSize, getY() + (rand() % 50) + 25);
			}
		// We are now waiting for the fish
		waitingForFish = true;
		bobber.isBobbing = true;
	}
}

void FishingRod::Stop()
{
	startCast = false;
	casting = false;
	waitingForFish = false;
	bobber.isBobbing = false;
	bobber.setPosition(-100, -100);
	rotation = 0;

}

void FishingRod::UpdateRod()
{
	// Close if pole is unequiped
	if (!renderFishingRod)
		Stop();

	// Check if bobber has collided with pole
	if (this->collidesWith(bobber))
	{
		std::cout << "COLLISION!" << std::endl;
		Stop();
	}

	///CASTING
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
	if (renderFishingRod)
	{
		//Update the rod
		UpdateRod();
		//Draw the fishing line
		if (casting)
			SDL_RenderDrawLine(renderer, this->getX() - Camera::camera.getX(), this->getY() - Camera::camera.getY(), bobber.getX() - Camera::camera.getX(), bobber.getY() - Camera::camera.getY());

		// Render casting bar
		castingBar.render(renderer, this->getX() - Camera::camera.getX(), this->getY() - Camera::camera.getY() - 50, castingLevel, 10);

		// Render fishingrod
		fishingRodTexture.renderRotation(renderer, this->getX() - Camera::camera.getX(), this->getY() - Camera::camera.getY(), this->getWidth(), this->getHeight(), rotation, castLeftOrRight);

		bobber.render(renderer);

		startCast = false;
	}
}
#include "stdafx.h"
#include "Fish.h"


Fish::Fish() : fishTexture(ResourceManager::fishTextureLocation + "fish1.png"), fishTwoTexture(ResourceManager::fishTextureLocation + "fish2.png"), fishThreeTexture(ResourceManager::fishTextureLocation + "fish3.png")
{
	fishType = Fish::FishType(rand() % 3);
	speed =  rand() % 3 + 0.5f;
	transparency = 50;
	
	objectTexture = fishTexture;
	objectTexture.atlasType = Texture::TextureType::Sprite;
}


Fish::~Fish()
{
}

void Fish::render(SDL_Renderer* renderer)
{
	// Set the transparency of the fish
	fishTexture.alterTransparency(transparency);
	fishTwoTexture.alterTransparency(transparency);
	fishThreeTexture.alterTransparency(transparency);

	
	switch (fishType)
	{
	default:
		fishTexture.renderRotation(renderer, this->getX() - Camera::camera.getX(), this->getY() - Camera::camera.getY(), this->getWidth(), this->getHeight(), rotation);
		break;
	case Fish::FishType::one:
		fishTexture.renderRotation(renderer, this->getX() - Camera::camera.getX(), this->getY() - Camera::camera.getY(), this->getWidth(), this->getHeight(), rotation);
		break;
	case Fish::FishType::two:
		fishTwoTexture.renderRotation(renderer, this->getX() - Camera::camera.getX(), this->getY() - Camera::camera.getY(), this->getWidth(), this->getHeight(), rotation);
		break;
	case Fish::FishType::three:
		fishThreeTexture.renderRotation(renderer, this->getX() - Camera::camera.getX(), this->getY() - Camera::camera.getY(), this->getWidth(), this->getHeight(), rotation);
		break;
	}
	// update pathfinder movement
	if (pathfinder.path.size() > 0)
		FindPath(pathfinder.currentGoal);

	// Update linear movement
	if (movingToDest)
		MoveTowards(currentGoal);
}

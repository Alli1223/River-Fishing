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
	fishTexture.alterTransparency(transparency);
	fishTwoTexture.alterTransparency(transparency);
	fishThreeTexture.alterTransparency(transparency);

	switch (fishType)
	{
	default:
		fishTexture.render(renderer, this->getX() - Camera::camera.getX(), this->getY() - Camera::camera.getY(), this->getWidth(), this->getHeight());
		break;
	case Fish::FishType::one:
		fishTexture.render(renderer, this->getX() - Camera::camera.getX(), this->getY() - Camera::camera.getY(), this->getWidth(), this->getHeight());
		break;
	case Fish::FishType::two:
		fishTwoTexture.render(renderer, this->getX() - Camera::camera.getX(), this->getY() - Camera::camera.getY(), this->getWidth(), this->getHeight());
		break;
	case Fish::FishType::three:
		fishThreeTexture.render(renderer, this->getX() - Camera::camera.getX(), this->getY() - Camera::camera.getY(), this->getWidth(), this->getHeight());
		break;
	}
}

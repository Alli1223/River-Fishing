#include "stdafx.h"
#include "Fish.h"


Fish::Fish() : fishTexture(ResourceManager::fishTextureLocation + "fish1.png")
{
	speed =  rand() % 3 + 0.5f;
	transparency = 50;
	objectTexture = fishTexture;
	objectTexture.atlasType = Texture::TextureType::Sprite;
}


Fish::~Fish()
{
}

void Fish::render()
{
	switch (fishType)
	{
	default:
		fishTexture.render(renderer, this->getX() - Camera::camera.getX(), this->getY() - Camera::camera.getY(), this->getWidth(), this->getHeight());
		break;
	case Fish::FishType::one:
		break;
	case Fish::FishType::one:
		break;
	case Fish::FishType::one:
		break;
	}
}

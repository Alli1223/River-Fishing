#include "stdafx.h"
#include "Bobber.h"


Bobber::Bobber() : BobberTexture(ResourceManager::fishTextureLocation + "bobber.png")
{
	objectTexture.alterTransparency(150);
	objectTexture = BobberTexture;
	objectTexture.atlasType = Texture::TextureType::Sprite;
	setSize(25);
}


Bobber::~Bobber()
{
}
void Bobber::reset()
{
	isBobbing = false;
}
void Bobber::render(SDL_Renderer* renderer)
{

	if (isBobbing)
	{
		// If the bobber is no longer on water
		if (!Level::level.tiles[(int)this->getX() / Level::level.getCellSize()][(int)this->getY() / Level::level.getCellSize()]->isWater)
		{
			reset();
		}
		this->BobberTexture.renderRotation(renderer, this->getX() - Camera::camera.getX(), this->getY() - Camera::camera.getY() + (sin(SDL_GetTicks() / 500.0f) * 4.0f), this->getWidth(), this->getHeight(), cos(SDL_GetTicks() / 500));
	}
}

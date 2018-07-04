#include "stdafx.h"
#include "Bobber.h"


Bobber::Bobber() : BobberTexture(ResourceManager::fishTextureLocation + "bobber.png")
{
	objectTexture.alterTransparency(150);
	objectTexture = BobberTexture;
	objectTexture.atlasType = Texture::TextureType::Sprite;
}


Bobber::~Bobber()
{
}

void Bobber::render(SDL_Renderer* renderer)
{
	this->BobberTexture.renderRotation(renderer, this->getX() - Camera::camera.getX(), this->getY() - Camera::camera.getY() + (sin(SDL_GetTicks() / 500.0f) * 2.0f), this->getWidth(), this->getHeight() , cos(SDL_GetTicks() / 500));
}

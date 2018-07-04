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

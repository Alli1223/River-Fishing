#include "stdafx.h"
#include "Fish.h"


Fish::Fish() : fishTexture("Resources\\Sprites\\Animals\\Fish\\fish1.png")
{
	speed = 3;
	objectTexture = fishTexture;
	objectTexture.atlasType = Texture::TextureType::Sprite;
}


Fish::~Fish()
{
}

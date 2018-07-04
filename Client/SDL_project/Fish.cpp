#include "stdafx.h"
#include "Fish.h"


Fish::Fish() : fishTexture("Resources\\Sprites\\Cursor\\cursor.png")
{
	
	objectTexture = fishTexture;
	objectTexture.atlasType = Texture::TextureType::Sprite;
}


Fish::~Fish()
{
}

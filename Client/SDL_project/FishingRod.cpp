#include "stdafx.h"
#include "FishingRod.h"


FishingRod::FishingRod() : fishingRodTexture("Resources\\Sprites\\SpriteSheets\\Items\\fishingPole.png")
{
	// Set texture settings
	objectTexture.atlasType = Texture::TextureType::Sprite;
	this->objectTexture = fishingRodTexture;

}


FishingRod::~FishingRod()
{
}

void FishingRod::CastLine(int playerRotation)
{
	rotation = 0;

	// Cast to the right
	if (playerRotation == 90)
	{
		if (rotation < 90 && !startCast)
			rotation++;
		if (rotation >= 90)
			startCast = false;
		rotation - 5;
	}

}
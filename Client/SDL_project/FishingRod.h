#pragma once
#include "GameObject.h"

class FishingRod : public GameObject
{
public:
	FishingRod();
	~FishingRod();

	Texture fishingRodTexture;

	void CastLine(int PlayerRotation);
	bool startCast = false;

};


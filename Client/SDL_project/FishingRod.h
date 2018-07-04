#pragma once
#include "GameObject.h"
#include "Bobber.h"
class FishingRod : public GameObject
{
public:
	FishingRod();
	~FishingRod();

	Bobber bobber;
	Texture fishingRodTexture;

	void CastLine(int PlayerRotation);
	bool startCast = false;

};


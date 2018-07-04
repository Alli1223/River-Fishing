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

	Texture castingBar;

	int castingLevel;

	void CastLine(int PlayerRotation);
	void SpawnBobber();
	void UpdateRod();
	void render(SDL_Renderer * renderer);
	bool startCast = false;
	bool casting = false;



private:
	//! Used for flipping the fishing rod
	bool castLeftOrRight;
	int playerRotation;

	int castingSpeed = 5;

};


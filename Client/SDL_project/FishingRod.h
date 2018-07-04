#pragma once
#include "GameObject.h"
#include "Bobber.h"
#include "Level.h"
class FishingRod : public GameObject
{
public:
	FishingRod();
	~FishingRod();

	Bobber bobber;
	Texture fishingRodTexture;

	Texture castingBar;

	int castingLevel;

	void CastLine();
	void SpawnBobber();
	void UpdateRod();
	void render(SDL_Renderer * renderer);
	bool startCast = false;
	bool casting = false;

	int setPlayerRotation(int newRotation) { return playerRotation = newRotation; }

private:
	//! Used for flipping the fishing rod
	bool castLeftOrRight;
	int playerRotation;

	int castingSpeed = 7;

	int castingDistance = 2;

	//! Rotation of rod until max
	int maxRotate = 90;

};


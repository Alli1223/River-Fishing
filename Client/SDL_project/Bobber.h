#pragma once
#include "GameObject.h"
#include "Level.h"
#include "Fish.h"
class Bobber : public GameObject
{
public:
	Bobber();
	~Bobber();

	void reset();

	bool isBobbing = false;
	bool fishHooked = false;
	void render(SDL_Renderer* renderer);
	Texture BobberTexture;
}; 


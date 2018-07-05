#pragma once
#include "GameObject.h"
#include "Level.h"
class Bobber : public GameObject
{
public:
	Bobber();
	~Bobber();

	void reset();

	bool isBobbing = false;
	void render(SDL_Renderer* renderer);
	Texture BobberTexture;
}; 


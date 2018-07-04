#pragma once
#include "GameObject.h"
class Bobber : public GameObject
{
public:
	Bobber();
	~Bobber();

	void render(SDL_Renderer* renderer);
	Texture BobberTexture;
}; 


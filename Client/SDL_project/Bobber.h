#pragma once
#include "GameObject.h"
class Bobber : public GameObject
{
public:
	Bobber();
	~Bobber();

	bool isBobbing = false;
	void render(SDL_Renderer* renderer);
	Texture BobberTexture;
}; 


#pragma once
#include "Animal.h"

class Fish : public Animal
{
public:
	Fish();

	~Fish();

	

	enum FishType
	{
		none,
		one,
		two,
		three,
		four
	} fishType;

	Texture fishTexture;
	Texture fishTwoTexture;
	Texture fishThreeTexture;

	bool isSwimming = false;
	bool isHooked = false;
	void render(SDL_Renderer * renderer);
private:
	
};


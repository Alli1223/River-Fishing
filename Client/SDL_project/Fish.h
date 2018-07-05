#pragma once
#include "Animal.h"

class Fish : public Animal
{
public:
	Fish();

	~Fish();

	void render();

	enum FishType
	{
		none,
		one,
		two,
		three,
		four
	} fishType;
	Texture fishTexture;

private:
	
};


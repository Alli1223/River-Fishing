#pragma once
#include "Texture.h"
class Light
{
public:

	//! Constructor
	Light();
	//! Destructor
	~Light();

	

	enum LightType
	{
		noLight,
		campFire,
		torch,
		streetLight
	} lightType;

private:

};


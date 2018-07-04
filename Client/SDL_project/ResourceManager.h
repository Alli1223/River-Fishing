#pragma once
#include "Texture.h"
class ResourceManager
{
public:
	//! Contains all the textures
	static std::map<std::string, Texture> textures;

	//! Load a texture
	static void LoadTextureFromFile(std::string file, std::string name);

	//! Get a texture from the list
	static Texture GetTexture(std::string name);

	//! Constructor and Destructor
	ResourceManager();
	~ResourceManager();

	static std::string fishTextureLocation;
};


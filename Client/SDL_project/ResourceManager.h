#pragma once
#include "Texture.h"
class ResourceManager
{
public:
	//! Contains all the textures
	static std::map<std::string, Texture> textures;

	static void LoadTextureFromFile(std::string file, std::string name);

	//! Get a texture from the list
	static Texture GetTexture(std::string name);
	ResourceManager();
	~ResourceManager();
};


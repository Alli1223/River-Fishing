#include "stdafx.h"
#include "ResourceManager.h"

// Static textures list
std::map<std::string, Texture> ResourceManager::textures;

ResourceManager::ResourceManager()
{
	ResourceManager::LoadTextureFromFile("Resources\\Sprites\\SpriteSheets\\Characters\\Alien.png", "fish");
}

ResourceManager::~ResourceManager()
{
}

void ResourceManager::LoadTextureFromFile(std::string file, std::string name)
{
	textures.insert({ name, Texture(file.c_str()) });
}

Texture ResourceManager::GetTexture(std::string name)
{
	return textures.at(name);
}
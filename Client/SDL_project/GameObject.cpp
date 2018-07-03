#include "stdafx.h"
#include "GameObject.h"


GameObject::GameObject(): objectTexture("Resources\\Sprites\\SpriteSheets\\roguelikeSheet_transparent.png")
{
	objectTexture.setTileSize(16);
	objectTexture.setAtlasType(1);
	objectTexture.setTileWidth(56);
	
}

GameObject::~GameObject()
{
}


void GameObject::render(SDL_Renderer* renderer)
{
	this->objectTexture.renderAtlas(renderer, index, this->getX() - Camera::camera.getX(), this->getY() - Camera::camera.getY(), this->getWidth(), this->getHeight());

}
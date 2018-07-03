#include "stdafx.h"
#include "GameObject.h"


GameObject::GameObject(): objectTexture("Resources\\Sprites\\SpriteSheets\\roguelikeSheet_transparent.png")
{
}


GameObject::~GameObject()
{
}


void GameObject::render(SDL_Renderer* renderer)
{
	this->objectTexture.renderAtlas(renderer, this->getX(), this->getY(), this->getWidth(), this->getHeight(), index);
}
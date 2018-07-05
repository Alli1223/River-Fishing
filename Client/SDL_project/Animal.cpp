#include "stdafx.h"
#include "Animal.h"


Animal::Animal() 
{
}


Animal::~Animal()
{
}

void Animal::move(glm::ivec2 move)
{
	pathfinder.findPath(Level::level, (glm::ivec2)this->getPosition(), (glm::ivec2)this->getPosition());
}

void Animal::render(SDL_Renderer * renderer)
{

}
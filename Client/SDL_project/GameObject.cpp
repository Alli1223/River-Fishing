#include "stdafx.h"
#include "GameObject.h"


GameObject::GameObject(): objectTexture("Resources\\Sprites\\SpriteSheets\\roguelikeSheet_transparent.png")
{
	objectTexture.setTileSize(16);
	objectTexture.atlasType = Texture::TextureType::AtlasBorder16px;
	objectTexture.setTileWidth(56);
}

GameObject::GameObject(std::string file) : objectTexture(file)
{

}

GameObject::~GameObject()
{
}


void GameObject::render(SDL_Renderer* renderer)
{
	this->objectTexture.alterTransparency(transparency);
	switch (objectTexture.atlasType)
	{
	case Texture::TextureType::AtlasBorder16px:
		objectTexture.setTileSize(16);
		objectTexture.setTileWidth(56);
		this->objectTexture.renderAtlas(renderer,index, this->getX() - Camera::camera.getX(), this->getY() - Camera::camera.getY(), this->getWidth(), this->getHeight());
		break;
	case Texture::TextureType::Sprite:
		
		this->objectTexture.render(renderer, this->getX() - Camera::camera.getX(), this->getY() - Camera::camera.getY(), this->getWidth(), this->getHeight());
		break;
	default:
		this->objectTexture.render(renderer, this->getX() - Camera::camera.getX(), this->getY() - Camera::camera.getY(), this->getWidth(), this->getHeight());
		break;
	}
}

bool GameObject::collidesWith(GameObject object)
{
	int top1, top2, left1, left2, right1, right2, bottom1, bottom2;

	// This object
	top1 = this->getY() - (this->getHeight() / 2);
	left1 = this->getX() - (this->getWidth() / 2);
	right1 = this->getX() + (this->getWidth() / 2);
	bottom1 = this->getY() + (this->getHeight() / 2);


	// That object
	top2 = object.getY() - (object.getHeight() / 2);
	left2 = object.getX() - (object.getWidth() / 2);
	right2 = object.getX() + (object.getWidth() / 2);
	bottom2 = object.getY() + (object.getHeight() / 2);


		return !(left2 > right1 ||
			right2 < left1 ||
			top2 > bottom1 ||
			bottom2 <top1);

	if (SDL_HasIntersection(&this->getTexture().getRect(), &object.getTexture().getRect()) == SDL_TRUE)
	{
		return true;
	}
	else
		return false;

}
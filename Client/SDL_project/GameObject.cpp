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
	switch (objectTexture.atlasType)
	{
	case Texture::TextureType::AtlasBorder16px:
		objectTexture.setTileSize(16);
		objectTexture.setTileWidth(56);
		this->objectTexture.renderAtlas(renderer,index, this->getX() - Camera::camera.getX(), this->getY() - Camera::camera.getY(), this->getWidth(), this->getHeight());
		break;
	case Texture::TextureType::Sprite:
		this->objectTexture.alterTransparency(50);
		this->objectTexture.render(renderer, this->getX() - Camera::camera.getX(), this->getY() - Camera::camera.getY(), this->getWidth(), this->getHeight());
		break;
	default:
		this->objectTexture.render(renderer, this->getX() - Camera::camera.getX(), this->getY() - Camera::camera.getY(), this->getWidth(), this->getHeight());
		break;
	}
}
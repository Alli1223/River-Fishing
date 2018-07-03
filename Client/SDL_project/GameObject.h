#pragma once
#include "Texture.h"
class GameObject
{
public:
	//! Constructor
	GameObject();
	//! Destructor
	~GameObject();

	// Get and Set positions
	glm::ivec2 getPosition() { return position; }
	glm::ivec2 setPosition(glm::ivec2 Position) { return position = Position; }
	int getX() { return position.x; }
	int getY() { return position.y; }
	int setX(int X) { return position.x = X; }
	int setY(int Y) { return position.y = Y; }

	glm::ivec2 getSize() { return size; }
	glm::ivec2 setSize(glm::ivec2 newSize) { return size = newSize; }
	int setSize(int width, int height) { return size.x = width, size.y = height; }
	int getWidth() { return size.x; }
	int getHeight() { return size.y; }


private:
	//! Position of the object
	glm::ivec2 position;
	//! Size of the object
	glm::ivec2 size;
	//! Speed the object can travel at
	float speed;
	//! The rotation the object is
	float rotation;

	//! The index of where the sprite is in the atlas
	int index;

	//! Render the object
	void render(SDL_Renderer* renderer);

	//! The objects texture
	Texture objectTexture;
};


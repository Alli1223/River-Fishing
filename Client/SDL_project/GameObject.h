#pragma once
#include "Texture.h"
#include "Camera.h"
class GameObject
{
public:
	//! Constructor
	GameObject();
	GameObject(std::string file);
	//! Destructor
	~GameObject();

	// Get and Set positions
	glm::vec2 getPosition() { return position; }
	glm::vec2 setPosition(glm::vec2 Position) { return position = Position; }
	float setPosition(float x , float y) { return position.x = x, position.y = y; }
	float getX() { return position.x; }
	float getY() { return position.y; }
	float setX(float X) { return position.x = X; }
	float setY(float Y) { return position.y = Y; }

	glm::ivec2 getSize() { return size; }
	glm::ivec2 setSize(glm::ivec2 newSize) { return size = newSize; }
	int setSize(int width, int height) { return size.x = width, size.y = height; }
	int getWidth() { return size.x; }
	int getHeight() { return size.y; }

	float getSpeed() { return speed; }
	float setSpeed(float newSpeed) { speed = newSpeed; }

	//! Render the object
	void render(SDL_Renderer* renderer);

	//! The index of where the sprite is in the atlas
	int index;

	int transparency;

	Texture setTexture(Texture texture) { return objectTexture = texture; }
	Texture getTexture() { return objectTexture; }

protected:
	//! Position of the object
	glm::vec2 position;
	//! Size of the object
	glm::ivec2 size;
	//! Speed the object can travel at
	float speed;
	//! The rotation the object is
	float rotation;

	//! The objects texture
	Texture objectTexture;
};


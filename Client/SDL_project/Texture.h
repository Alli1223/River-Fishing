#pragma once

//! Loads and renders images in the window
/*!
This class is used for all the images in the game. It loads textures from a given file location 
and can alter the image transparency if the image is a PNG.
*/
class Texture
{
public:
	//! A constructor
	/*!
	Requires a file path to load the image from
	*/
	Texture(const std::string& fileName);
	//! A destructor
	~Texture();

	//! Loads the texture
	SDL_Texture* getTexture() { return texture; }
	
	std::string changeFileName(std::string newFileName) { return fileName = newFileName; };

	enum TextureType
	{
		AtlasNoBorder128px,
		AtlasBorder16px,
		AtlasNoBorder32px,
		Sprite,
		Animation
	} atlasType;

	//! Renders the image in the window
	void render(SDL_Renderer* renderer, int x, int y, int width, int height);
	//! Render an Atlas
	void renderAtlas(SDL_Renderer* renderer, int index, int x, int y, int width, int height);
	//! Renders the image in the window with rotation
	void renderRotation(SDL_Renderer* renderer, int x, int y, int width, int height, int angle);
	void renderRotation(SDL_Renderer * renderer, int x, int y, int width, int height, int angle, bool flip);
	//! Renders  the animation
	void renderAnim(SDL_Renderer* renderer, int sourceX, int sourceY, int destX, int destY, int pixelSize, int renderSize);
	void renderAnim(SDL_Renderer* renderer, int sourceX, int sourceY, int destX, int destY, int pixelSize, int renderSize, bool flipHorizontal);
	//! Render light
	void renderLight(SDL_Renderer* renderer, int sourceX, int sourceY, int destX, int destY, int pixelSize, int renderSize);
	//! Alters the alpha value of the image to make it appear transparent in the window
	void alterTransparency(int transparencyLevel);
	//! Alters the r,g,b colours of the texture
	void alterTextureColour(int r, int g, int b);
	void alterTextureColour(SDL_Color& color);
	void alterTextureColour(SDL_Color& color, int hueChange);

	//Set blending
	void setBlendMode(SDL_BlendMode blending);
	//! Set Atlas tile size
	int setTileSize(int size ) { return atlasTileSize = size; }
	//! Set Atlas tile width number
	int setTileWidth(int width) { return atlasTileWidth = width; }

	SDL_Rect& getRect() { return dstrect; }

	int index = 0;
private:
	//! The width of tile sets
	int atlasTileWidth = 16;
	//! Atlas tile size
	int atlasTileSize = 16;

	//! The image location
	std::string fileName;
	//! Pointer to the SDL Texture
	SDL_Texture* texture;

	SDL_Rect srcrect;
	SDL_Rect dstrect;
};

#include "stdafx.h"
#include "Rendering.h"

//! Constructor that initalises all the texture file locations
Rendering::Rendering() :
	healthBarTexture(playerStatsTextureLocation + "PlayerHealth.png"), oxygenBarTexture(playerStatsTextureLocation + "PlayerOxygen.png"),
	hungerBarTexture(playerStatsTextureLocation + "PlayerHunger.png"), tiredBarTexture(playerStatsTextureLocation + "PlayerTiredness.png"),
	light(playerStatsTextureLocation + "light.png"), lightsBackground(playerStatsTextureLocation + "black.png"),
	terrainAtlas(SpriteSheets + "mapPack_tilesheet.png"), roguelikeAtlas(SpriteSheets + "roguelikeSheet_transparent.png"), cropsAtlas(SpriteSheets + "crops.png"),

	// Summer
	summerAtlas(summerTerrainSpriteTextureLocation + "new_Summer_grass_1.png"),

	// Buildings
	ShopBuilding("Resources\\Buildings\\PotionShop.png")
{
	// Set other atlas stats
	terrainAtlas.setTileSize(128);
	terrainAtlas.setTileSize(16);

	summerAtlas.setTileSize(64);
	summerAtlas.setTileWidth(6);
	summerAtlas.atlasType = Texture::TextureType::AtlasNoBorder128px;
	// Set rogue atlas stats
	roguelikeAtlas.setTileSize(16);
	roguelikeAtlas.atlasType = Texture::TextureType::AtlasBorder16px;
	roguelikeAtlas.setTileWidth(56);

	cropsAtlas.setTileSize(32);
	cropsAtlas.setTileWidth(8);
	cropsAtlas.atlasType = Texture::TextureType::AtlasNoBorder128px;

}

//! Destructor
Rendering::~Rendering()
{
}

void Rendering::AddToBatchRendering(int ID, int x, int y, int& size, char layer)
{
	textureID texture;
	texture.index = ID;
	texture.x = x;
	texture.y = y;
	texture.width = size;
	texture.height = size;
	texture.layer = layer;
	allTextures.push_back(texture);
}


void Rendering::AlterTextures(Level& level)
{
	//SDL_SetTextureBlendMode(light.getTexture(), SDL_BLENDMODE_ADD);
	//light.alterTransparency(50);
	//SDL_SetTextureBlendMode(roguelikeAtlas.getTexture(), SDL_BLENDMODE_BLEND);
	//roguelikeAtlas.alterTextureColour(100, 100, 100);
		
}

void Rendering::renderCellsAroundObject(SDL_Renderer* renderer, Level& level, int& x, int& y, int& xPos, int& yPos)
{
	int levelSize = level.tiles.size();

	int above = y - 1;
	int below = y + 1;
	int left = x - 1;
	int right = x + 1;


	// In one row
	if (x - 1 >= 0 && x + 1 < levelSize)
	{
		if (level.tiles[x][y]->isWater && level.tiles[x - 1][y]->isGrass)
		{
			level.tiles[x][y]->orientation = Cell::orientation::middleLeft;
		}
		if (level.tiles[x][y]->isWater && level.tiles[x + 1][y]->isGrass)
		{
			level.tiles[x][y]->orientation = Cell::orientation::middleRight;
		}

		// Center of Chunk
		if (y - 1 >= 0 && y + 1 < levelSize)
		{
			if(level.tiles[x][y]->isWater)
				level.tiles[x][y]->orientation = Cell::orientation::middle;
			
			// Edges
			if (level.tiles[x][y]->isWater && level.tiles[x][y - 1]->isGrass)
			{
				level.tiles[x][y]->orientation = Cell::orientation::topMiddle;
			}
			if (level.tiles[x][y]->isWater && level.tiles[x - 1][y]->isGrass)
			{
				level.tiles[x][y]->orientation = Cell::orientation::middleLeft;
			}
			if (level.tiles[x][y]->isWater && level.tiles[x + 1][y]->isGrass)
			{
				level.tiles[x][y]->orientation = Cell::orientation::middleRight;
			}
			if (level.tiles[x][y]->isWater && level.tiles[x][y + 1]->isGrass)
			{
				level.tiles[x][y]->orientation = Cell::orientation::bottomMiddle;
			}

			// Top corners
			if (level.tiles[x][y]->isWater && !level.tiles[x - 1][y - 1]->isWater && !level.tiles[x][y - 1]->isWater && !level.tiles[x - 1][y]->isWater)
			{
				level.tiles[x][y]->orientation = Cell::orientation::topLeft;
			}
			else if (level.tiles[x][y]->isWater && !level.tiles[x + 1][y - 1]->isWater && !level.tiles[x][y - 1]->isWater && !level.tiles[x + 1][y]->isWater)
			{
				level.tiles[x][y]->orientation = Cell::orientation::topRight;
			}
			// Bottom corners
			else if (level.tiles[x][y]->isWater && !level.tiles[x - 1][y + 1]->isWater && !level.tiles[x][y + 1]->isWater && !level.tiles[x - 1][y]->isWater)
			{
				level.tiles[x][y]->orientation = Cell::orientation::bottomLeft;
			}
			else if (level.tiles[x][y]->isWater && !level.tiles[x + 1][y + 1]->isWater && !level.tiles[x][y + 1]->isWater && !level.tiles[x + 1][y]->isWater)
			{
				level.tiles[x][y]->orientation = Cell::orientation::bottomRight;
			}
			
			
			if (level.tiles[x][y]->isWater && level.tiles[x][below]->orientation == Cell::orientation::middleLeft && level.tiles[x][above]->isWater)
			{

			}


		}
	}
	else if (y - 1 >= 0 && y + 1 < levelSize)
	{
		if (level.tiles[x][y]->isWater && level.tiles[x][y - 1]->isGrass)
			level.tiles[x][y]->orientation = Cell::orientation::topMiddle;
		if (level.tiles[x][y]->isWater && level.tiles[x][y + 1]->isGrass)
			level.tiles[x][y]->orientation = Cell::orientation::bottomMiddle;

	}
}
void Rendering::RenderBuilding(std::shared_ptr<Building>& building, Camera& camera, GameSettings& gameSettings, Player& player, SDL_Renderer* renderer)
{
	int newX = 0, newY = 0;
	int xPos = 0, yPos = 0;
	int cellSize = building->getTileSize();

	glm::vec2 newPos = { camera.getX(), camera.getY() };
	newPos /= cellSize;

	for(int x = 0; x < building->tiles.size(); x++)
		for (int y = 0; y < building->tiles[0].size(); y++)
		{
			newX = building->tiles[x][y]->getX();
			newY = building->tiles[x][y]->getY();

			xPos = newX * cellSize + cellSize / 2;
			yPos = newY * cellSize + cellSize / 2;

			xPos -= camera.getX();
			yPos -= camera.getY();
			if (building->tiles[x][y]->isWater)
			{
				// Code for ripples
				//sin(sqrt(pow(level.tiles[x][y]->getX(),2) + pow(level.tiles[x][y]->getY(),2)) + SDL_GetTicks() / 500) > 0)
				if (sin(building->tiles[x][y]->getX() + SDL_GetTicks() / 500) > 0)
					AddToBatchRendering(waterID, xPos, yPos, cellSize, seaLevel);
				else
					AddToBatchRendering(water2ID, xPos, yPos, cellSize, seaLevel);

				switch (building->tiles[x][y]->orientation)
				{
				case Cell::orientation::topLeft:
					AddToBatchRendering(waterTopLeft, xPos, yPos, cellSize, ground);
					break;
				case Cell::orientation::topMiddle:
					AddToBatchRendering(waterTopMiddle, xPos, yPos, cellSize, ground);
					break;
				case Cell::orientation::topRight:
					AddToBatchRendering(waterTopRight, xPos, yPos, cellSize, ground);
					break;
				case Cell::orientation::middleLeft:
					AddToBatchRendering(waterMiddleLeft, xPos, yPos, cellSize, ground);
					break;
				case Cell::orientation::middle:
					AddToBatchRendering(waterMiddle, xPos, yPos, cellSize, ground);
					break;
				case Cell::orientation::middleRight:
					AddToBatchRendering(waterMiddleRight, xPos, yPos, cellSize, ground);
					break;
				case Cell::orientation::bottomLeft:
					AddToBatchRendering(waterBottomLeft, xPos, yPos, cellSize, ground);
					break;
				case Cell::orientation::bottomMiddle:
					AddToBatchRendering(waterBottomMiddle, xPos, yPos, cellSize, ground);
					break;
				case Cell::orientation::bottomRight:
					AddToBatchRendering(waterBottomRight, xPos, yPos, cellSize, ground);
					break;
				}
			}

			// Base Ground Textures rendered in decending order (Top layered textures at bottom of list)
			if (building->tiles[x][y]->isGrass)
				AddToBatchRendering(grassID, xPos, yPos, cellSize, ground);
			if (building->tiles[x][y]->isSand)
				AddToBatchRendering(sandID, xPos, yPos, cellSize, ground);

			if (building->tiles[x][y]->isDirt)
				AddToBatchRendering(dirtID, xPos, yPos, cellSize, ground);



			if (building->tiles[x][y]->isStoneWall)
				AddToBatchRendering(18, xPos, yPos, cellSize, onGround);
			else if (building->tiles[x][y]->isFlower1)
				AddToBatchRendering(blueFlower, xPos, yPos, cellSize, onGround);
			else if (building->tiles[x][y]->isFlower2)
				AddToBatchRendering(redFlower, xPos, yPos, cellSize, onGround);
			else if (building->tiles[x][y]->isBerryPlant)
				AddToBatchRendering(redBerryBush, xPos, yPos, cellSize, onGround);
			else if (building->tiles[x][y]->isBush)
				AddToBatchRendering(525, xPos, yPos, cellSize, onGround);
			else if (building->tiles[x][y]->isLongGrass)
				AddToBatchRendering(sandID, xPos, yPos, cellSize, onGround);
			else if (building->tiles[x][y]->isLongGrass2)
				AddToBatchRendering(sandID, xPos, yPos, cellSize, onGround);
			else if (building->tiles[x][y]->isSnow)
				AddToBatchRendering(sandID, xPos, yPos, cellSize, onGround);
			else if (building->tiles[x][y]->isRock)
				AddToBatchRendering(rockID, xPos, yPos, cellSize, onGround);
			else if (building->tiles[x][y]->isWood)
				AddToBatchRendering(longWood, xPos, yPos, cellSize, onGround);
			else if (building->tiles[x][y]->isStone)
				AddToBatchRendering(stoneID, xPos, yPos, cellSize, onGround);

		}
}
void Rendering::RenderLevel(Level& level, Camera& camera, GameSettings& gameSettings, Player& player, SDL_Renderer* renderer)
{
	int newX = 0, newY = 0;
	int xPos = 0, yPos = 0;
	int cellSize = level.getCellSize();

	// get the camera position
	glm::ivec2 cameraPos = { camera.getX(), camera.getY() };
	cameraPos /= cellSize;

	if (cameraPos.x < 0)
		cameraPos.x = 0;
	if (cameraPos.y < 0)
		cameraPos.y = 0;
	if (cameraPos.x + level.cellsInWindow.x >= level.tiles.size())
		cameraPos.x = level.tiles.size() - level.cellsInWindow.x;
	if (cameraPos.y + level.cellsInWindow.y >= level.tiles[0].size())
		cameraPos.y = level.tiles[0].size() - level.cellsInWindow.y;

	
	for (int x = cameraPos.x; x < cameraPos.x + level.cellsInWindow.x +1; x++)
		for (int y = cameraPos.y; y < cameraPos.y + level.cellsInWindow.y; y++)
		{
			if (cameraPos.y + level.cellsInWindow.y + 1 < level.tiles.size())
			
				newX = level.tiles[x][y]->getX();
				newY = level.tiles[x][y]->getY();

				if (newX > 4000000 || newX < 0)
					newX = 0;
				if (newY > 4000000 || newY < 0)
					newY = 0;
				xPos = newX * cellSize + cellSize / 2;
				yPos = newY * cellSize + cellSize / 2;

				xPos -= camera.getX();
				yPos -= camera.getY();





				if (level.tiles[x][y]->isWater)
				{
					// Code for ripples
					//sin(sqrt(pow(level.tiles[x][y]->getX(),2) + pow(level.tiles[x][y]->getY(),2)) + SDL_GetTicks() / 500) > 0)
					if (sin(level.tiles[x][y]->getX() + SDL_GetTicks() / 500) > 0)
						AddToBatchRendering(waterID, xPos, yPos, cellSize, seaLevel);
					else
						AddToBatchRendering(water2ID, xPos, yPos, cellSize, seaLevel);

					switch (level.tiles[x][y]->orientation)
					{
					case Cell::orientation::topLeft:
						AddToBatchRendering(waterTopLeft, xPos, yPos, cellSize, ground);
						break;
					case Cell::orientation::topMiddle:
						AddToBatchRendering(waterTopMiddle, xPos, yPos, cellSize, ground);
						break;
					case Cell::orientation::topRight:
						AddToBatchRendering(waterTopRight, xPos, yPos, cellSize, ground);
						break;
					case Cell::orientation::middleLeft:
						AddToBatchRendering(waterMiddleLeft, xPos, yPos, cellSize, ground);
						break;
					case Cell::orientation::middle:
						AddToBatchRendering(waterMiddle, xPos, yPos, cellSize, ground);
						break;
					case Cell::orientation::middleRight:
						AddToBatchRendering(waterMiddleRight, xPos, yPos, cellSize, ground);
						break;
					case Cell::orientation::bottomLeft:
						AddToBatchRendering(waterBottomLeft, xPos, yPos, cellSize, ground);
						break;
					case Cell::orientation::bottomMiddle:
						AddToBatchRendering(waterBottomMiddle, xPos, yPos, cellSize, ground);
						break;
					case Cell::orientation::bottomRight:
						AddToBatchRendering(waterBottomRight, xPos, yPos, cellSize, ground);
						break;
					}
				}

				// Base Ground Textures rendered in decending order (Top layered textures at bottom of list)
				if (level.tiles[x][y]->isGrass)
					AddToBatchRendering(grassID, xPos, yPos, cellSize, ground);
				if (level.tiles[x][y]->isSand)
					AddToBatchRendering(sandID, xPos, yPos, cellSize, ground);

				if (level.tiles[x][y]->isDirt)
					AddToBatchRendering(dirtID, xPos, yPos, cellSize, ground);



				if (level.tiles[x][y]->isStoneWall)
					AddToBatchRendering(18, xPos, yPos, cellSize, onGround);
				else if (level.tiles[x][y]->isFlower1)
					AddToBatchRendering(blueFlower, xPos, yPos, cellSize, onGround);
				else if (level.tiles[x][y]->isFlower2)
					AddToBatchRendering(redFlower, xPos, yPos, cellSize, onGround);
				else if (level.tiles[x][y]->isBerryPlant)
					AddToBatchRendering(redBerryBush, xPos, yPos, cellSize, onGround);
				else if (level.tiles[x][y]->isBush)
					AddToBatchRendering(525, xPos, yPos, cellSize, onGround);
				else if (level.tiles[x][y]->isLongGrass)
					AddToBatchRendering(sandID, xPos, yPos, cellSize, onGround);
				else if (level.tiles[x][y]->isLongGrass2)
					AddToBatchRendering(sandID, xPos, yPos, cellSize, onGround);
				else if (level.tiles[x][y]->isSnow)
					AddToBatchRendering(sandID, xPos, yPos, cellSize, onGround);
				else if (level.tiles[x][y]->isRock)
					AddToBatchRendering(rockID, xPos, yPos, cellSize, onGround);
				else if (level.tiles[x][y]->isWood)
					AddToBatchRendering(longWood, xPos, yPos, cellSize, onGround);
				else if (level.tiles[x][y]->isStone)
					AddToBatchRendering(stoneID, xPos, yPos, cellSize, onGround);



				if (level.tiles[x][y]->isWheat)
				{
					// Update seeds
					if (level.tiles[x][y]->plantTimer.getTicks() > gameSettings.plantGrowSpeed)
					{
						switch (level.tiles[x][y]->plantStage)
						{
						case Cell::PlantStage::PlantStageOne:
							level.tiles[x][y]->plantStage = Cell::PlantStage::PlantStageTwo;
							break;
						case Cell::PlantStage::PlantStageTwo:
							level.tiles[x][y]->plantStage = Cell::PlantStage::PlantStageThree;
							break;
						case Cell::PlantStage::PlantStageThree:
							level.tiles[x][y]->plantStage = Cell::PlantStage::PlantStageFour;
							break;
						case Cell::PlantStage::PlantStageFour:
							level.tiles[x][y]->plantStage = Cell::PlantStage::PlantStageFive;
							break;
						case Cell::PlantStage::PlantStageFive:
							level.tiles[x][y]->plantStage = Cell::PlantStage::PlantStageSix;
							break;
						case Cell::PlantStage::PlantStageSix:
							level.tiles[x][y]->plantStage = Cell::PlantStage::PlantStageSeven;
							break;
						case Cell::PlantStage::PlantStageSeven:
							level.tiles[x][y]->plantStage = Cell::PlantStage::PlantStageSeven;
							break;
						}
						level.tiles[x][y]->plantTimer.restart();
					}

					switch (level.tiles[x][y]->plantStage)
					{
					case Cell::PlantStage::PlantStageOne:
						AddToBatchRendering(1, xPos, yPos, cellSize, isCrops);
						break;
					case Cell::PlantStage::PlantStageTwo:
						AddToBatchRendering(2, xPos, yPos, cellSize, isCrops);
						break;
					case Cell::PlantStage::PlantStageThree:
						AddToBatchRendering(3, xPos, yPos, cellSize, isCrops);
						break;
					case Cell::PlantStage::PlantStageFour:
						AddToBatchRendering(4, xPos, yPos, cellSize, isCrops);
						break;
					case Cell::PlantStage::PlantStageFive:
						AddToBatchRendering(5, xPos, yPos, cellSize, isCrops);
						break;
					case Cell::PlantStage::PlantStageSix:
						AddToBatchRendering(6, xPos, yPos, cellSize, isCrops);
						break;
					case Cell::PlantStage::PlantStageSeven:
						AddToBatchRendering(7, xPos, yPos, cellSize, isCrops);
						break;
					}
				}

				if (level.tiles[x][y]->isTree)
				{
					AddToBatchRendering(treeBottom, xPos, yPos, cellSize, onGround);
					AddToBatchRendering(treeTop, xPos, yPos - cellSize, cellSize, abovePlayer);
				}

				switch (level.tiles[x][y]->groundType)
				{
				case Cell::GroundType::campFire:
					break;
				case Cell::GroundType::streetLight:
					break;
				case Cell::GroundType::torch:
					AddToBatchRendering(416, xPos, yPos, cellSize, abovePlayer);
					break;

				}


				// Fences
				if (level.tiles[x][y]->isWoodFence)
				{
					AddToBatchRendering(woodHalfFence, xPos, yPos, cellSize, onGround);

				}
				// Render object orientations
				renderCellsAroundObject(renderer, level, x, y, xPos, yPos);

				/*
				switch (level.tiles[x][y]->building)
				{
				case Cell::Building::playerShop:
					//level.buildings[0]->setPosition(xPos, yPos);
					level.buildings[0]->setPosition(level.tiles[x][y]->getX() * cellSize, level.tiles[x][y]->getY() * cellSize);
					level.buildings[0]->setEntrancePoint(level.buildings[0]->getX() - 80, level.buildings[0]->getY() + 100);
					level.buildings[0]->isVisable = true;
					break;
				}
				*/
			
		}
}





//! Renders the chunks of cells
void Rendering::RenderObjects(Level& level, SDL_Renderer* renderer, Camera& camera, Player& player, GameSettings& gameSettings, std::vector<std::shared_ptr<Player>>& allPlayers)
{	
	// Alter the textures
	AlterTextures(level);
	if(!player.isInBuilding)
		RenderLevel(level, camera, gameSettings, player, renderer);
	else
	{
		RenderBuilding(level.buildings[0], camera, gameSettings, player, renderer);
	}
	//! The index of where the sprite is in the atlas
	int index;
	// Batch render all the textures
	for each(auto &texture in allTextures)
	{
		switch (texture.layer)
		{
		case seaLevel:
			roguelikeAtlas.renderAtlas(renderer, texture.index, texture.x, texture.y, texture.width, texture.height);
			break;
		case ground:
			roguelikeAtlas.renderAtlas(renderer, texture.index, texture.x, texture.y, texture.width, texture.height);
			break;
		case onGround:
			//roguelikeAtlas.renderAtlas(renderer, texture.index, texture.x, texture.y, texture.width, texture.height);
			break;
		case isCrops:
			//cropsAtlas.renderAtlas(renderer, texture.index, texture.x, texture.y, texture.width, texture.height);
			break;
		}
	}
	
	for (int i = 0; i < level.buildings.size(); i++)
	{
		if (level.buildings[i]->isVisable)
			ShopBuilding.render(renderer, level.buildings[i]->getX() - camera.getX(), level.buildings[i]->getY() - camera.getY(), level.buildings[i]->getWidth(), level.buildings[i]->getHeight());
		SDL_Rect entrance;
		entrance.x = level.buildings[i]->getEntrancePoint().getX() - camera.getX();
		entrance.y = level.buildings[i]->getEntrancePoint().getY() - camera.getY();
		entrance.w = 50;
		entrance.h = 50;
		SDL_RenderDrawRect(renderer, &entrance);
	}
	

	// Render the player
	player.RenderPlayer(renderer, camera);
	//Update and render multi players
	for each (auto &player in allPlayers)
	{
		player->Update(level);
		player->RenderPlayer(renderer, camera);
	}

	// Batch render all the textures
	for each(auto &texture in allTextures)
	{
		switch (texture.layer)
		{
		case abovePlayer:
			//roguelikeAtlas.renderAtlas(renderer, texture.index, texture.x, texture.y, texture.width, texture.height);
			break;
		}
	}


	//hungerBarTexture.render(renderer, (gameSettings.mouseCellPos.x * level.getCellSize()) - (camera.getX() + level.getCellSize()) + level.getCellSize() * 1.5, (gameSettings.mouseCellPos.y  * level.getCellSize()) - (camera.getY() - level.getCellSize()) - level.getCellSize() / 2, level.getCellSize(), level.getCellSize());
	//light.renderLight(renderer, 0,0, player.getX()  - camera.getX(), player.getY()  - camera.getY() , level.getCellSize() * 10 + (sin(SDL_GetTicks() / 1000.0) * 50.0), level.getCellSize() * 10 + (sin(SDL_GetTicks() / 1000.0) * 50.0));

	
	
	allTextures.erase(allTextures.begin(), allTextures.end());
	
}

void Rendering::RenderPlayer(SDL_Renderer* renderer, Player& player,  Level& level, Camera& camera)
{
	//int x = player.getX() - camera.getX();
	//int y = player.getY() - camera.getY();
	//player.setPosition(x, y);
	//if (player.characterType == "Player")
		//characterTex.renderRotation(renderer, x, y, player.getSize(), player.getSize(), player.getRotation());
		//player.RenderPlayer(renderer);

}
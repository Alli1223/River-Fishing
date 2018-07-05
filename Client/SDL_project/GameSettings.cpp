#include "stdafx.h"
#include "GameSettings.h"


GameSettings::GameSettings()
{
	//Calculate and correct fps
}


GameSettings::~GameSettings()
{
}

void GameSettings::getScreenResolution()
{

	for (int i = 0; i < SDL_GetNumVideoDisplays(); ++i) {

		int should_be_zero = SDL_GetCurrentDisplayMode(i, &currentDisplay);

		if (should_be_zero != 0)
			SDL_Log("Could not get display mode for video display #%d: %s", i, SDL_GetError());

		else
			SDL_Log("Display #%d: current display mode is %dx%dpx @ %dhz.", i, currentDisplay.w, currentDisplay.h, currentDisplay.refresh_rate);
		break;
	}
	WINDOW_HEIGHT = currentDisplay.h;
	WINDOW_WIDTH = currentDisplay.w;

}

void GameSettings::CalculateFramesPerSecond()
{
	
	avgFPS = countedFrames / (fpsTimer.getTicks() / 1000.f);
	if (avgFPS > 2000000)
	{
		avgFPS = 0;
	}
	std::cout << avgFPS << std::endl;
	countedFrames++;

}


//TODO: Create a mapdata json file for singleplayer
void GameSettings::savePlayerSettings(Player& playerOne)
{
	
	json playerData = playerOne.getPlayerJson();

	playerSave.open(playerSavePath);
	playerSave << playerData.dump();
	std::cout << "Saved Player settings." << std::endl;
	playerSave.close();
}

void GameSettings::saveLevelData(Level& level)
{
	json levelData;
	json mainLevel;
	json buildings;
	
	std::cout << "Level Saving.." << std::endl;
	// Save the main level
	for (int x = 0; x < level.tiles.size() - 1; x++)
	{
		for (int y = 0; y < level.tiles[0].size() - 1; y++)
		{
			mainLevel.push_back(level.tiles[x][y]->getCellData());
		}
	}
	// Save the buildings data
	for (int i = 0; i < level.buildings.size(); i++)
	{
		// Create the building
		json building;
		json tiles;
		building["X"] = level.buildings[i]->getX();
		building["Y"] = level.buildings[i]->getY();
		building["Width"] = level.buildings[i]->getWidth();
		building["Height"] = level.buildings[i]->getHeight();
		building["EntranceX"] = level.buildings[i]->getEntrancePoint().getX();
		building["EntranceY"] = level.buildings[i]->getEntrancePoint().getY();
		building["Visable"] = level.buildings[i]->isVisable;
		building["BuildingType"] = level.buildings[i]->buildingType;
		// Save the tiles
		for (int x = 0; x < level.buildings[i]->tiles.size() - 1; x++)
		{
			for (int y = 0; y <  level.buildings[i]->tiles[0].size() - 1; y++)
			{
				tiles.push_back(level.buildings[i]->tiles[x][y]->getCellData());
			}
		}
		building["Tiles"] = tiles;
		// Add that to list
		buildings.push_back(building);
	}
	levelData["Level"] = mainLevel;
	levelData["Buildings"] = buildings;
	levelSave.open(levelSavePath);
	levelSave << levelData.dump();
	std::cout << "Level Saved." << std::endl;
	levelSave.close();
}

//TODO: Load game from save
void GameSettings::loadGameFromSave(Level& level)
{
	Level levelToReturn;
	std::string line;
	std::ifstream readGameSave(levelSavePath);
	if (readGameSave.is_open())
	{
		while (std::getline(readGameSave, line))
		{
			json jsonData = json::parse(line.begin(), line.end());;

			json mapData = jsonData.at("Level");
			json buildingsData = jsonData.at("Buildings");
			// Range-based for loop to iterate through the map data
			for (auto& element : mapData)
			{
				Cell newCell;
				newCell = Cell(element);
				level.tiles[newCell.getX()][newCell.getY()] = std::make_shared<Cell>(newCell);
			}
			
			
			for (auto& building : buildingsData)
			{
				// Construct buildings from json
				Building newBuilding;
				newBuilding = Building(building);
				level.buildings.push_back(std::make_shared<Building>(newBuilding));
			}
		}
	}
	
}


Player GameSettings::getPlayerFromSave()
{
	Player existingPlayer;
	std::string line;
	std::ifstream readPlayerSave(playerSavePath);
	try
	{


		if (readPlayerSave.is_open())
		{
			while (std::getline(readPlayerSave, line))
			{
				//saveData = line;
				json jsonData = json::parse(line.begin(), line.end());;
				json playerData = jsonData.at("PlayerData");

				// Player movement
				int x = playerData.at("X").get<int>();
				int y = playerData.at("Y").get<int>();
				int rotation = playerData.at("rotation").get<int>();
				std::string name = playerData.at("name").get<std::string>();
				bool isMoving = playerData.at("isMoving").get<bool>();

				// Player clothes

				// ints for converting the json enums
				int headWear;
				int bodyWear;
				int legWear;
				int EarType;
				int EyeType;
				int gender;

				// Check to see if the data is there
				if (playerData.count("headWear") > 0)
				{
					headWear = playerData.at("headWear").get<int>();
				}
				if (playerData.count("bodyWear") > 0)
				{
					bodyWear = playerData.at("bodyWear").get<int>();
				}
				if (playerData.count("bodyWear") > 0)
				{
					legWear = playerData.at("legWear").get<int>();
				}
				if (playerData.count("eyeType") > 0)
				{
					EyeType = playerData.at("eyeType").get<int>();
				}
				if (playerData.count("earType") > 0)
				{
					EarType = playerData.at("earType").get<int>();
				}
				if (playerData.count("gender") > 0)
				{
					gender = playerData.at("gender").get<int>();
				}
				json hairColour = playerData.at("hairColour");
				int hr = hairColour.at("r").get<int>();
				int hg = hairColour.at("g").get<int>();
				int hb = hairColour.at("b").get<int>();
				json eyeColour = playerData.at("eyeColour");
				int er = eyeColour.at("r").get<int>();
				int eg = eyeColour.at("g").get<int>();
				int eb = eyeColour.at("b").get<int>();
				json upperClothesColour = playerData.at("upperClothesColour");
				int jr = upperClothesColour.at("r").get<int>();
				int jg = upperClothesColour.at("g").get<int>();
				int jb = upperClothesColour.at("b").get<int>();
				json legsColour = playerData.at("legColour");
				int lr = legsColour.at("r").get<int>();
				int lg = legsColour.at("g").get<int>();
				int lb = legsColour.at("b").get<int>();
				json bodyColour = playerData.at("bodyColour");
				int br = bodyColour.at("r").get<int>();
				int bg = bodyColour.at("g").get<int>();
				int bb = bodyColour.at("b").get<int>();
				existingPlayer.setEyeColour(er, eg, eb);
				existingPlayer.setHairColour(hr, hg, hb);
				existingPlayer.setJacketColour(br, bg, bb);
				existingPlayer.setJeansColour(lr, lg, lb);
				existingPlayer.setBodyColour(br, bg, bb);

				existingPlayer.body.gender = (Player::Body::Gender)gender;
				existingPlayer.body.earType = (Player::Body::EarType)EarType;
				existingPlayer.body.eyeType = (Player::Body::EyeType)EyeType;
				existingPlayer.PlayerClothes.hat = (Player::Clothing::HeadWear)headWear;
				existingPlayer.PlayerClothes.body = (Player::Clothing::BodyWear)bodyWear;
				existingPlayer.PlayerClothes.leg = (Player::Clothing::LegWear)legWear;
				existingPlayer.setPlayerMoving(isMoving);

			}

			readPlayerSave.close();
		}
	}
	catch (std::exception e)
	{
		printf("Error getting saved player %s", e.what());
	}
	return existingPlayer;
}
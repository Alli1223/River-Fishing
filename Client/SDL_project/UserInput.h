#pragma once
#include "Level.h"
#include "Camera.h"
#include "Player.h"
#include "ToolBar.h"
#include "InventoryUI.h"
#include "Timer.h"
#include "GameUI.h"
class UserInput
{
public:
	//! Constructor
	UserInput();
	//! Destructor
	~UserInput();

	//! Handle the users input
	void HandleUserInput(SDL_Renderer* renderer, Level& level, Player& player, Camera& camera, GameSettings& gameSettings, ToolBar& toolbar, GameUI& UI);
	
	//! Used to change cells around a cell
	void ChangeCellsAroundPoint(Level& level, glm::vec2 point, int dist, std::string type);

private:
	//! Use item that is selected in the toolbar
	void UseItemFromToolbar(SDL_Renderer* renderer, ToolBar& toolbar, Player& player, GameSettings& gameSettings);

	//! Timers for UIs to have a timeout when opened or closed
	Timer inventoryTimer;
	Timer craftingTimer;

	//! Timeout in milliseconds
	float inventoryTimeout = 500;
	float craftingTimeout = 500;
	glm::vec2 playerChunkPos;
	glm::vec2 playercellPos;
	glm::vec2 InterDir;

	SDL_Joystick *joystick;
};


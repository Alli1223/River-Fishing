#include "stdafx.h"
#include "UserInput.h"


UserInput::UserInput()
{
	
}


UserInput::~UserInput()
{
}



void UserInput::HandleUserInput(SDL_Renderer* renderer, Level& level, Player& player, Camera& camera, GameSettings& gameSettings, ToolBar& toolbar, GameUI& UI)
{
	int cellSize = level.getCellSize();
	//SDL_JoystickEventState(SDL_ENABLE);
	SDL_Event ev;
	while (SDL_PollEvent(&ev))
	{
		if (ev.type == SDL_QUIT)
		{
			gameSettings.running = false;
		}
		//Mouse wheel
		switch (ev.type)
		{
		case SDL_MOUSEWHEEL:  /* Handle Mousewheel Motion */
			if (ev.wheel.x < 0)
			{
				std::cout << "MOUSE : WHEEL LEFT" << std::endl;
			}
			else if (ev.wheel.x > 0)
			{
				std::cout << "MOUSE : WHEEL RIGHT" << std::endl;
			}
			if (ev.wheel.y < 0)
			{
				toolbar.setToolbarSelection(toolbar.getToolbarSelection() + 1);
			}
			else if (ev.wheel.y > 0)
			{
				toolbar.setToolbarSelection(toolbar.getToolbarSelection() - 1);
			}
			break;

		case SDL_JOYAXISMOTION:  /* Handle Joystick Motion */
			//std::cout << ev.jaxis.which << std::endl;
			if (ev.jaxis.axis == 0)
			{
				if (ev.jaxis.value < 0)
					player.setX(player.getX() - player.getSpeed());
				else if (ev.jaxis.value > 0)
					player.setX(player.getX() + player.getSpeed());
			}

			else if (ev.jaxis.axis == 1)
			{
				if (ev.jaxis.value < 0)
					player.setY(player.getY() - player.getSpeed());
				else if (ev.jaxis.value > 0)
					player.setY(player.getY() + player.getSpeed());
			}
			break;
		}
	}

	const Uint8 *state = SDL_GetKeyboardState(NULL);
	if (state[SDL_SCANCODE_ESCAPE])
	{
		if (UI.gameMenu.timeout.getTicks() > 500)
		{
			if (gameSettings.inGameMenu)
				gameSettings.inGameMenu = false;
			else
				gameSettings.inGameMenu = true;
			UI.gameMenu.timeout.restart();
		}
	}
		
	// Set the players speed
	float deltaTime = gameSettings.deltaTime;
	player.setVelocity(player.getSpeed() * deltaTime);

	playerChunkPos = player.chunkPos;
	playercellPos = player.cellPos;
	/////////// PLAYER MOVEMENT ////////////
	//Diagonal movement
	if (state[SDL_SCANCODE_W] && state[SDL_SCANCODE_D])
	{
		//player.setTargetRotation(225);
		player.setTargetRotation(270);
		player.setPlayerMoving(true);

		player.Move(level, Player::movementDirection::right_up);
	}
	else if (state[SDL_SCANCODE_W] && state[SDL_SCANCODE_A])
	{
		//player.setTargetRotation(135);
		player.setTargetRotation(90);
		player.setPlayerMoving(true);

		player.Move(level, Player::movementDirection::left_up);
		
	}
	else if (state[SDL_SCANCODE_S] && state[SDL_SCANCODE_D])
	{
		player.setPlayerMoving(true);
		//player.setTargetRotation(-45);
		player.setTargetRotation(270);

		player.Move(level, Player::movementDirection::right_down);
	}
	else if (state[SDL_SCANCODE_S] && state[SDL_SCANCODE_A])
	{
		player.setPlayerMoving(true);
		//player.setTargetRotation(45);
		player.setTargetRotation(90);

		player.Move(level, Player::movementDirection::left_down);
	}
	// Player Movement
	else if (state[SDL_SCANCODE_S])
	{
		player.setPlayerMoving(true);
		player.setTargetRotation(0);

		player.Move(level, Player::movementDirection::down);
	}
	else if (state[SDL_SCANCODE_A])
	{
		player.setPlayerMoving(true);
		player.setTargetRotation(90);

		player.Move(level, Player::movementDirection::left);

	}
	else if (state[SDL_SCANCODE_D])
	{
		player.setPlayerMoving(true);
		player.setTargetRotation(270);
		player.Move(level, Player::movementDirection::right);
	}
	else if (state[SDL_SCANCODE_W])
	{
		player.setPlayerMoving(true);
		player.setTargetRotation(180);

		player.Move(level, Player::movementDirection::up);
	}
	else
	{
		//player.setSpeed(0);
		player.setPlayerMoving(false);
		//player.setTargetRotation(0);
	}




	/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	// ACTION BAR
	if (state[SDL_SCANCODE_0])
		toolbar.setToolbarSelection(10);
	else if (state[SDL_SCANCODE_1])
		toolbar.setToolbarSelection(0);
	else if (state[SDL_SCANCODE_2])
		toolbar.setToolbarSelection(1);
	else if (state[SDL_SCANCODE_3])
		toolbar.setToolbarSelection(2);
	else if (state[SDL_SCANCODE_4])
		toolbar.setToolbarSelection(3);
	else if (state[SDL_SCANCODE_5])
		toolbar.setToolbarSelection(4);
	else if (state[SDL_SCANCODE_6])
		toolbar.setToolbarSelection(5);
	else if (state[SDL_SCANCODE_7])
		toolbar.setToolbarSelection(6);
	else if (state[SDL_SCANCODE_8])
		toolbar.setToolbarSelection(7);

	
	if (state[SDL_SCANCODE_RIGHT])
	{ 
		toolbar.setToolbarSelection(toolbar.getToolbarSelection() + 1);
	}
	if (state[SDL_SCANCODE_DOWN])
	{
		Item fence;
		fence.type.Resource = Item::ItemType::isWOODFENCE;
		player.inventory.add(fence);
		
	}
	
	if (state[SDL_SCANCODE_LEFT])
	{
		toolbar.setToolbarSelection(toolbar.getToolbarSelection() - 1);
	}
	if (state[SDL_SCANCODE_UP])
	{
		player.setSpeed(player.getSpeed() + 1.0);
	}

	// Set cell size
	if (state[SDL_SCANCODE_PAGEUP])
	{
		level.setCellSize(level.getCellSize() + 1);
	}
		
	if (state[SDL_SCANCODE_PAGEDOWN] && level.getCellSize() > 1)
	{
		level.setCellSize(level.getCellSize() - 1);
		
	}
		

	if (state[SDL_SCANCODE_F])
	{

	}
	// Use Action
	int mouseX, mouseY = 0;
	if (toolbar.getSelectedItem().type.Resource != Item::ItemType::noResource)
	{
		gameSettings.displayMouse = true;
	}

	// Update rod
	player.fishingRod.setPlayerRotation(player.getTargetRotation());




	//LEFT CLICK
	if (SDL_GetMouseState(&mouseX, &mouseY) & SDL_BUTTON(SDL_BUTTON_LEFT))
	{
		UseItemFromToolbar(renderer, toolbar, player, gameSettings);
	}

	// RIGHT CLICK
	if (SDL_GetMouseState(&mouseX, &mouseY) & SDL_BUTTON(SDL_BUTTON_RIGHT))
	{
		//Point startPoint(player.getCellX(), player.getCellY());
		//Point endPoint(gameSettings.mouseCellPos.x, gameSettings.mouseCellPos.y);
		// add negative offset
		//player.pathFinder.findPath(level, startPoint, endPoint);
		if (level.buildings.size() < 1)
		{
			PlayerShop shop;
			level.buildings.push_back(std::make_shared<PlayerShop>(shop));
			
		}
		level.buildings[0]->setPosition(gameSettings.mouseCellPos.x * cellSize, gameSettings.mouseCellPos.y * cellSize);
		level.buildings[0]->setEntrancePoint(level.buildings[0]->getX() - 80, level.buildings[0]->getY() + 100);
		level.buildings[0]->isVisable = true;
	}


	if (state[SDL_SCANCODE_M])
	{
		
	}
	if (state[SDL_SCANCODE_I])
	{
		if (!inventoryTimer.isStarted())
			inventoryTimer.start();
		else
		{
			if (inventoryTimer.getTicks() > inventoryTimeout)
			{
				// Close panel
				if (player.InventoryPanel.getDispalayInventory())
				{
					gameSettings.displayMouse = false;
					player.InventoryPanel.setDisplayInventory(false);
					player.InventoryPanel.getInventoryIcons().erase(player.InventoryPanel.getInventoryIcons().begin(), player.InventoryPanel.getInventoryIcons().end());
				}
				//Open Panel
				else
				{
					gameSettings.displayMouse = true;
					player.InventoryPanel.CreateInventory(renderer, player.inventory);
					player.InventoryPanel.setDisplayInventory(true);
				}
		
			}
			inventoryTimer.restart();
		}
	}
	if (state[SDL_SCANCODE_C])
	{
		if (!craftingTimer.isStarted())
			craftingTimer.start();
		else
		{
			if (craftingTimer.getTicks() > craftingTimeout)
			{
				if (player.craftingUI.getDispalayCrafting())
				{
					gameSettings.displayMouse = false;
					player.craftingUI.setDisplayCrafting(false);
				}
				else
				{
					gameSettings.displayMouse = true;
					player.craftingUI.setDisplayCrafting(true);
				}
			}
			
		}
	}

	player.fishingRod.renderFishingRod = false;
	//Toolbar hover
	if (toolbar.getSelectedItem().type.Resource == Item::ItemType::isFISHINGROD)
	{
		player.fishingRod.renderFishingRod = true;
	}
	
}


//TODO: Re Implement This.
void UserInput::ChangeCellsAroundPoint(Level& level, glm::vec2 point, int dist, std::string type)
{
	//Check if cell is in bounds
	glm::vec2 chunkPos;
	glm::vec2 actionPos;

	/*
	for (int playerPosX = playerX - cellSize * 2; playerPosX < playerX + cellSize * 2; playerPosX += cellSize)
	{
		for (int playerPosY = playerY - cellSize * 2; playerPosY < playerY + cellSize * 2; playerPosY += cellSize)
		{
			// Calculate the positions around the player to account for changeing of chunks
			int x = playerX / cellSize;
			int y = playerY / cellSize;
			chunkPos.x = (playerPosX / cellSize) / level.getChunkSize();
			chunkPos.y = (playerPosY / cellSize) / level.getChunkSize();


			if (level.World[chunkPos.x][chunkPos.y].tiles[actionPos.x][actionPos.y]->isTree)
			{
				Item item;
				item.isWOOD;
				level.World[chunkPos.x][chunkPos.y].tiles[actionPos.x][actionPos.y]->isTree = false;
				level.World[chunkPos.x][chunkPos.y].tiles[actionPos.x][actionPos.y]->isStoneWall = true;
				level.World[chunkPos.x][chunkPos.y].tiles[actionPos.x][actionPos.y]->isWalkable = true;
				agentManager.allAgents[agentManager.GetAgentNumberFomID(playerName)].inventory.add(item);
			}
		}
	}
	*/
}


void UserInput::UseItemFromToolbar(SDL_Renderer* renderer, ToolBar& toolbar, Player& player, GameSettings& gameSettings)
{
	
	// FISHING ROD
	if (toolbar.getSelectedItem().type.Resource == Item::ItemType::isFISHINGROD)
	{
		player.fishingRod.CastLine();
		
	}



}
	
	

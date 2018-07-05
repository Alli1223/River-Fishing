#include "stdafx.h"
#include "River-Fishing.h"
#include "InitialisationError.h"
void showErrorMessage(const char* message, const char* title)
{
	// Note: this is specific to Windows, and would need redefining to work on Mac or Linux
	MessageBoxA(nullptr, message, title, MB_OK | MB_ICONERROR);
}



RiverFishing::RiverFishing() : backgroundTexture("Resources\\background5.jpg"), mousePointer("Resources\\Sprites\\Cursor\\cursor.png")
{
	if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO) < 0 || SDL_Init(SDL_INIT_TIMER | SDL_INIT_JOYSTICK) < 0)
	{
		std::cout << (stderr, "Couldn't initialize SDL: %s\n", SDL_GetError()) << std::endl;
		throw InitialisationError("SDL_Init failed");
	}
	
	//Initialize SDL_mixer
	if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0)
	{
		printf("SDL_mixer could not initialize! SDL_mixer Error: %s\n", Mix_GetError());
	}

	SDL_ShowCursor(SDL_DISABLE);

	// Set Window Size
	gameSettings.getScreenResolution();

	gameSettings.WINDOW_HEIGHT;
	gameSettings.WINDOW_WIDTH;
	if (!gameSettings.fullscreen)
	{
		gameSettings.WINDOW_HEIGHT /=2;
		gameSettings.WINDOW_WIDTH /= 2;
	}
	gameSettings.deltaTime = SDL_GetTicks();
	

	Camera::camera.WindowHeight = gameSettings.WINDOW_HEIGHT;
	Camera::camera.WindowWidth = gameSettings.WINDOW_WIDTH;
	Camera::camera.SetPos(0, 0);
	


	// Create the window
	if (gameSettings.fullscreen)
		window = SDL_CreateWindow("Magic Cafe", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, gameSettings.WINDOW_WIDTH, gameSettings.WINDOW_HEIGHT, SDL_WINDOW_FULLSCREEN_DESKTOP | SDL_WINDOW_OPENGL);
	else
		window = SDL_CreateWindow("Magic Cafe", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, gameSettings.WINDOW_WIDTH, gameSettings.WINDOW_HEIGHT, SDL_WINDOW_RESIZABLE | SDL_WINDOW_OPENGL);

	glContext = SDL_GL_CreateContext(window);
	if (window == nullptr)
		throw InitialisationError("SDL_CreateWindow failed");

	// Create Renderer
	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_PRESENTVSYNC | SDL_TEXTUREACCESS_TARGET | SDL_RENDERER_TARGETTEXTURE);
	if (renderer == nullptr)
		throw InitialisationError("SDL_CreateRenderer failed");
	SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_BLEND);
	// IF TTF Init error
	if (!TTF_WasInit() && TTF_Init() == -1) {
		printf("TTF_Init: %s\n", TTF_GetError());
		exit(1);
	}
}

RiverFishing::~RiverFishing()
{
	//Free the music
	Mix_FreeMusic(gMusic);
	gMusic = NULL;

	// Destroy window
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);

	// Quit SDL subsystems
	Mix_Quit();
	IMG_Quit();
	SDL_Quit();
}


void RiverFishing::run()
{
	terrainGen.setSeed(312);
	Level::level.setCellsInWindowSize(gameSettings.WINDOW_WIDTH / Level::level.getCellSize(), gameSettings.WINDOW_HEIGHT / Level::level.getCellSize());
	Level::level.CreateLevel(0, 0);
	terrainGen.populateTerrain(Level::level.tiles);
	// Run the main menu
Menu:
	if (gameSettings.mainMenu)
	{
		Menu menu;
		menu.MainMenu(gameSettings, Level::level, Camera::camera, player, renderer);
		menu.~menu();
	}

	int cellSize = Level::level.getCellSize();
	
	gMusic = Mix_LoadMUS("Resources\\Sounds\\Music\\Fantasy_Game_Loop.wav");
	if (gMusic == NULL)
	{
		printf("Failed to load beat music! SDL_mixer Error: %s\n", Mix_GetError());
	}

	// Create a unique playername
	std::string playerName = std::to_string(SDL_GetTicks());

	player.characterType = "Player";
	player.setID(playerName);
	player.setSize(Level::level.getCellSize() * 2);
	player.setPosition(1000, 1000);

	UI.toolbar.createToolbar(player, gameSettings);

	player.inventory.setCapacity(56);

	// Add starting items
	Item fishingPole;
	fishingPole.type.Resource = Item::ItemType::isFISHINGROD;
	player.inventory.add(fishingPole);


	player.InventoryPanel.setX(gameSettings.WINDOW_WIDTH / 2 + gameSettings.WINDOW_WIDTH / 4);
	player.InventoryPanel.setY(gameSettings.WINDOW_HEIGHT / 2);
	player.InventoryPanel.setHeight(gameSettings.WINDOW_HEIGHT - gameSettings.WINDOW_HEIGHT / 4);
	player.InventoryPanel.setWidth(gameSettings.WINDOW_WIDTH / 3);
	player.InventoryPanel.setIconSize(gameSettings.WINDOW_WIDTH / 50);
	player.InventoryPanel.CreateInventory(renderer, player.inventory);
	player.InventoryPanel.setDisplayInventory(false);

	player.craftingUI.setX(gameSettings.WINDOW_WIDTH / 4);
	player.craftingUI.setY(gameSettings.WINDOW_HEIGHT / 2);
	player.craftingUI.setHeight(gameSettings.WINDOW_HEIGHT - gameSettings.WINDOW_HEIGHT / 4);
	player.craftingUI.setWidth(gameSettings.WINDOW_WIDTH / 3);
	player.craftingUI.setIconSize(gameSettings.WINDOW_WIDTH / 25);
	gameSettings.fpsTimer.start();

	Mix_PlayMusic(gMusic, -1);
	/////////////////////////////////////////////// MAIN LOOP ///////////////////////////////////////
	while (gameSettings.running)
	{
		
		player.setSize(Level::level.getCellSize());
		Level::level.setCellsInWindowSize(gameSettings.WINDOW_WIDTH / Level::level.getCellSize(), gameSettings.WINDOW_HEIGHT / Level::level.getCellSize());
		// Get mouse Position
		SDL_GetMouseState(&mouseX, &mouseY);
		//gameSettings.getScreenResolution();

		
		if (gameSettings.displayFPS)
			gameSettings.CalculateFramesPerSecond();
		gameSettings.elapsedTime = SDL_GetTicks();

		
		gameSettings.mouseCellPos.x = mouseX / Level::level.getCellSize() + Camera::camera.getX() / Level::level.getCellSize();
		gameSettings.mouseCellPos.y = mouseY / Level::level.getCellSize() + Camera::camera.getY() / Level::level.getCellSize();


		if (SDL_GetMouseState(&mouseX, &mouseY) & SDL_BUTTON(SDL_BUTTON_RIGHT))
		{
			
			
		}

		// Handle the input
		input.HandleUserInput(renderer, Level::level, player, Camera::camera, gameSettings, UI.toolbar, UI);
		
		
		//Player pos for camera lerp
		glm::vec2 playerPos;
		playerPos.x = player.getX() - Camera::camera.WindowWidth / 2;
		playerPos.y = player.getY() - Camera::camera.WindowHeight / 2;


		Camera::camera.Lerp_To(playerPos, Camera::camera.getCameraSpeed());
		
		// Clear Rendering process:
		SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
		SDL_RenderClear(renderer);

		
		

		// Renders all the cells and players
		rendering.RenderObjects(Level::level, renderer, Camera::camera, player, gameSettings, allPlayers);

		AImanager.Update(renderer, camera);

		// Render all the UI
		UI.Render(renderer, player, gameSettings);

		player.Update(Level::level);


		if(player.pathFinder.Path.size() > 0)
			player.pathFinder.drawPath(player.pathFinder.Path, renderer, Camera::camera, Level::level);

		
		if (gameSettings.displayMouse)
			mousePointer.render(renderer, mouseX + (gameSettings.mousePointerSize / 2), mouseY + (gameSettings.mousePointerSize / 2), gameSettings.mousePointerSize, gameSettings.mousePointerSize * 1.5);
		SDL_RenderPresent(renderer);

		gameSettings.deltaTime = gameSettings.elapsedTime - gameSettings.lastFrameTimeElapsed;
		gameSettings.lastFrameTimeElapsed = gameSettings.elapsedTime;
		// Update the position of the player
		
		// End while running
	}

	if (gameSettings.gotoMainMenu)
		goto Menu;
	///// END GAME LOOP //////


	// Save player settings when the game ends the game loop
	if (gameSettings.saveLevelOnExit && !gameSettings.useNetworking)
		gameSettings.saveLevelData(Level::level);
	if (gameSettings.savePlayerOnExit)
		gameSettings.savePlayerSettings(player);
	if (gameSettings.restartGame)
		needsRestart = true;
}
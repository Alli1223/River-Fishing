#include "stdafx.h"
#include "GameUI.h"


GameUI::GameUI()
{
	
}


GameUI::~GameUI()
{
}


void GameUI::Render(SDL_Renderer* renderer, Player& playerOne, GameSettings& gameSettings)
{
	// Renders inventory
	playerOne.InventoryPanel.RenderInventory(renderer, playerOne.inventory);

	// Render toolbar
	toolbar.UpdateAndRenderToolbar(renderer, playerOne, gameSettings);

	// Render Crafting
	playerOne.craftingUI.renderCraftingMenu(renderer, playerOne.inventory);

	// Render game menu
	if (gameSettings.inGameMenu)
	{
		gameMenu.render(renderer, gameSettings);
	}
}
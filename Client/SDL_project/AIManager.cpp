#include "stdafx.h"
#include "AIManager.h"


AIManager::AIManager()
{
	// Start the timer and create the fish pool
	fishSpawnTimer.start();
	for (int i = 0; i < 30; i++)
	{
		CreateFish();
	}
}


AIManager::~AIManager()
{
}


void AIManager::Update(SDL_Renderer* renderer, Camera& camera, Player& player)
{
	// Spawn fish
	if (fishSpawnTimer.getTicks() > fishSpawnRate && fishCounter < allFish.size())
	{
		fishSpawnTimer.restart();
		allFish[fishCounter].setPosition(((Level::level.cellsInWindow.x - 5) / 2) * Level::level.getCellSize() + rand() % 300, -10);
		allFish[fishCounter].isSwimming = true;
		fishCounter++;
	}


	int i = 0;

	// Loop through all the fish
	for (auto &fish : allFish)
	{
		// Reset the fish to top of stream
		if (fish.getY() > Level::level.tiles[0].size() * Level::level.getCellSize())
		{
			fish.setY(-10);
		}

		// If fish collides with bobber
		if (fish.collidesWith(player.fishingRod.bobber) && player.fishingRod.bobber.isBobbing)
		{
			// Move the fish towards the bobber
			fish.MoveTowards(player.fishingRod.bobber.getPosition());
			fish.isHooked = true;
			player.fishingRod.bobber.fishHooked = true;

			// Add to inventory if collided with fishingpole
			if (fish.collidesWith(player.fishingRod))
			{
				if (fish.fishType == Fish::FishType::one)
				{
					Item fishItem;
					fishItem.type.Resource = Item::ItemType::isFishOne;
					player.inventory.add(fishItem);
				}
				else if (fish.fishType == Fish::FishType::two)
				{
					Item fishItem;
					fishItem.type.Resource = Item::ItemType::isFishTwo;
					player.inventory.add(fishItem);
				}
				else if (fish.fishType == Fish::FishType::three)
				{
					Item fishItem;
					fishItem.type.Resource = Item::ItemType::isFishThree;
					player.inventory.add(fishItem);
				}
				// Erase that fish
				allFish.erase(allFish.begin() + i);
			}
			std::cout << "Collision with fish" << std::endl;
		}
		else
			fish.isHooked = false;

		// Move the fish downstream if they have nowhere to go
		if (fish.pathfinder.path.size() <= 0 && !fish.isHooked)
		{
			fish.setY(fish.getY() + fish.getSpeed());
			fish.setRotation(0);
		}



		// Render the fish
		fish.render(renderer);
		i++;
	}
}

void AIManager::CreateFish()
{
	Fish fish;
	fish.setSize((rand() % 25) + 10);
	//fish.setPosition(((Level::level.cellsInWindow.x - 5) / 2) * Level::level.getCellSize(), -10);
	allFish.push_back(fish);
	
}
void AIManager::CreateNPC()
{
	NPC newNPC;
	newNPC.setBodyColour(std::rand() % 255, std::rand() % 255, std::rand() % 255);
	newNPC.body.earType = NPC::Body::EarType(rand() % 8);
	newNPC.body.hairType = NPC::Body::HairType(rand() % 13);
	newNPC.body.gender = NPC::Body::Gender(rand() % 2);
	newNPC.body.eyeType = NPC::Body::EyeType(rand() % 13);

	newNPC.PlayerClothes.body = NPC::Clothing::BodyWear(rand() % 3);
	newNPC.PlayerClothes.leg = NPC::Clothing::LegWear(rand() % 3);

	newNPC.setPosition(rand() % 100, rand() % 200);
	//newNPC.Move(Point(rand() % 100, rand() % 100));
	//NPCs.push_back(newNPC);

}
#include "stdafx.h"
#include "AIManager.h"


AIManager::AIManager()
{
	// Start the timer and create the fish pool
	fishSpawnTimer.start();
	for (int i = 0; i < 3; i++)
	{
		CreateFish();
	}
}


AIManager::~AIManager()
{
}


void AIManager::Update(SDL_Renderer* renderer, Camera& camera)
{
	// Spawn fish
	if (fishSpawnTimer.getTicks() > 500 && fishCounter < AllGameObjects.size())
	{
		fishSpawnTimer.restart();
		AllGameObjects[fishCounter].setPosition(((Level::level.cellsInWindow.x - 5) / 2) * Level::level.getCellSize() + rand() % 300, -10);
		fishCounter++;
	}
	for (auto &fish : AllGameObjects)
	{
		if (fish.getY() > Level::level.tiles[0].size() * Level::level.getCellSize())
		{
			fish.setY(-10);
		}
		fish.setY(fish.getY() + fish.getSpeed());
		fish.render(renderer);
	}
	



}

void AIManager::CreateFish()
{
	Fish fish;
	int size = rand() % 50;
	size += 25;
	fish.setSize(size, size);
	//fish.setPosition(((Level::level.cellsInWindow.x - 5) / 2) * Level::level.getCellSize(), -10);
	AllGameObjects.push_back(fish);
	
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
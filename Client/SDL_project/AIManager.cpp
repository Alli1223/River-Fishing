#include "stdafx.h"
#include "AIManager.h"


AIManager::AIManager()
{
	fishSpawnTimer.start();
}


AIManager::~AIManager()
{
}


void AIManager::Update(SDL_Renderer* renderer, Camera& camera)
{
	if (fishSpawnTimer.getTicks() > 50)
	{
		
			fishSpawnTimer.restart();
			CreateFish();
		
	}

	for (int i = 0; i < NPCs.size(); i++)
	{
		NPCs[i].render(renderer);
		NPCs[i].setY(NPCs[i].getY() + 1); 
	}
}

void AIManager::CreateFish()
{
	Fish fish;
	fish.setSize(50, 50);
	fish.setPosition(((Level::level.cellsInWindow.x - 5) / 2) * Level::level.getCellSize() + rand() % 300, -10);
	fish.index = rand() % 500;
	NPCs.push_back(fish);
	
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
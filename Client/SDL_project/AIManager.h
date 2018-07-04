#pragma once
#include "NPC.h"
#include "Fish.h"
#include "GameObject.h"
class AIManager
{
public:
	//! Constructor
	AIManager();
	//! Destructor
	~AIManager();

	//! Update the games AI
	void Update(SDL_Renderer* renderer, Camera& camera);

	//! Timer start
	Timer fishSpawnTimer;

private:
	//! Void Create NPC
	void CreateNPC();
	void CreateFish();
	int fishCounter = 0;

	//! Fish spawn rate in ms
	int fishSpawnRate = 1500;

	std::vector<GameObject> AllGameObjects;
};


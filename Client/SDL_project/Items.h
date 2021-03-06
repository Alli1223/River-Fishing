#pragma once
#include "Texture.h"
#include "Level.h"
#include "GameObject.h"
class Item : public GameObject
{
public:
	//! Constructor
	Item();
	
	//! Overloaded Constructor
	
	//! Destructor
	~Item();
	int getItemHealth() { return itemHealth; }
	int setItemHealth(int newHealth) { return itemHealth = newHealth; }
	int increaseStack(int amount) { return stack += amount; }
	int decreaseStack(int amount) { if (stack >= 0){ return stack -= amount; } }

	typedef struct
	{
		enum Resource
		{
			noResource,
			isWOOD,
			isSTONE,
			isSTONEWALL,
			isWOODFENCE,
			noFood,
			isBERRY,
			isFishOne,
			isFishTwo,
			isFishThree,
			isSEEDS,
			isWHEAT,
			noTool,
			isWOODAXE,
			isPICKAXE,
			isHOE,
			isSCYTHE,
			isWATERINGCAN,
			isFISHINGROD
		} Resource;
	} ItemType;
	
	ItemType type; 
	bool isInInventory = false;
	bool isPlaceable = false;

	Item::Item(Item::ItemType type);
private:
	int itemHealth = 100;
	int stack = 0;
};


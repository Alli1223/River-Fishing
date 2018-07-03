#pragma once
#include "Player.h"
class NPC :
	public Player
{
public:
	//! Constructor
	NPC();
	//! Destructor
	~NPC();

	//! Move the npc to a cell position
	void Move(Level& level, Point point);


};


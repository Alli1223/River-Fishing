#include "stdafx.h"
#include "NPC.h"


NPC::NPC()
{
}


NPC::~NPC()
{
}

void NPC::Move(Level& level, Point point)
{
	pathFinder.findPath(level, this->getCharacterPointLocation(), point);
	this->
}

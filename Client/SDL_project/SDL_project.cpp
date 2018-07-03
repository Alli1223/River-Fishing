// SDL_project.cpp : Defines the entry point for the application.
//

#include "stdafx.h"
#include "SDL_project.h"
#include "River-Fishing.h"

int main(int argc, char* args[])

{
	
	RiverFishing game;
	game.run();
	while (game.needsRestart)
	{
		RiverFishing game;
		game.run();
	}
	return 0;

}


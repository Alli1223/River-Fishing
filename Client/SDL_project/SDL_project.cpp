// SDL_project.cpp : Defines the entry point for the application.
//

#include "stdafx.h"
#include "SDL_project.h"
#include "MagicCafe.h"

int main(int argc, char* args[])

{
	
	MagicCafe game;
	game.run();
	while (game.needsRestart)
	{
		MagicCafe game;
		game.run();
	}
	return 0;

}


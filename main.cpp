// Using SDL and standard IO
#include <SDL2/SDL.h>
#include <SDL2/SDL_keycode.h>
#include <SDL2/SDL_surface.h>
#include <SDL2/SDL_mixer.h>
#include <stdio.h>
#include "media_funcs.hpp"
#include "window_logic.hpp"
#include "key_presses.hpp"

int main(int argc, char *args[])
{
	// Start up SDL and create window
	// Internal linkeage but not defined warning.. figure this out
	if(!init_my_window())
	{
		printf("Failed to initialize!\n");
	}
	else
	{
		// Load media
		if(!loadMedia())
		{
			printf("Failed to load media!\n");
		}
		else
		{
			// Main loop flag
			bool quit = false;

			// My color struct
			TestColorSet myColorSet = {255, 255, 255};

			// While the application hasnt quit
			while(!quit)
			{
				quit = main_loop(quit, myColorSet);
			}
		}
	}

	// Free resources and close SDL
	close_my_window();

	return 0;
}


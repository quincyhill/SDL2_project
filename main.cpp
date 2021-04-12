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
	if(!init_my_window())
	{
		printf("Failed to initialize!\n");
	}
	else
	{
		// Load media
		if(!load_media())
		{
			printf("Failed to load media!\n");
		}
		else
		{
			// Main window logic here
			bool quit = false;
			SDL_Event e;

			while(!quit)
			{
				quit = main_loop(quit, e);
			}
		}
	}

	// Free resources and close SDL
	close_my_window();
	return 0;
}

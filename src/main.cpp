// Using SDL and standard IO
#include <SDL2/SDL.h>
#include <SDL2/SDL_keycode.h>
#include <SDL2/SDL_surface.h>
#include <SDL2/SDL_mixer.h>
#include <SDL2/SDL_image.h>
#include "../include/window_logic.hpp"
#include "../include/media_funcs.hpp"
#include "../include/perlin_noise.hpp"
#include <stdio.h>
#include <cstdlib>
#include <string.h>

void game()
{
	// Start up SDL and create window
	if(!init_my_window())
	{
		std::printf("Failed to initialize!\n");
	}
	else
	{
		std::printf("window init\n");
		// Loads assets
		bool load_media_success = load_media();

		if(!load_media_success)
		{
			std::printf("Failed to load media!\n");
		}
		else
		{	
			std::printf("Loaded media!\n");

			// Main loop flag
			bool quit = false;
			// Event handler
			SDL_Event e;

			// While application is running
			while(!quit)
			{
				quit = main_loop(quit, e);
			}
		}
	}
	// Free resources and close SDL
	close_my_window();
}



int main(int argc, char *args[])
{
	game();
	std::printf("Perlin Value is: %f\n", perlin(0.342f, 0.123f));
	return 0;
}

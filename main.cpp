// Using SDL and standard IO
#include <SDL2/SDL.h>
#include <stdio.h>
#include "my_image_funcs.hpp"
#include "window_logic.hpp"


int main(int argc, char* args[])
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
			// Apply the image
			SDL_BlitSurface(gHelloWorld, nullptr, gScreenSurface, nullptr);

			// Update the surface
			SDL_UpdateWindowSurface(gWindow);

			// Wait two seconds
			SDL_Delay(2000);
		}
	}

	// Free resources and close SDL
	close_my_window();

	return 0;
}


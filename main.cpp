// Using SDL and standard IO
#include <SDL2/SDL.h>
#include <SDL2/SDL_keycode.h>
#include <SDL2/SDL_surface.h>
#include <stdio.h>
#include "image_funcs.hpp"
#include "window_logic.hpp"
#include "key_presses.hpp"


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
			// Main loop flag
			bool quit = false;

			// Event handler
			SDL_Event e;

			// Set default current surface
			gCurrentSurface = gKeyPressSurfaces[KEY_PRESS_SURFACE_DEFAULT];

			// While the application is running
			while(!quit)
			{
				// Handle events on queue
				while(SDL_PollEvent(&e) != 0)
				{
					// User requests quit
					if(e.type == SDL_QUIT)
					{
						quit = true;
					}
					// User presses a key
					else if(e.type == SDL_KEYDOWN)
					{
						// Select surfaces based on key press
						switch(e.key.keysym.sym)
						{
							case SDLK_UP:
								gCurrentSurface = gKeyPressSurfaces[KEY_PRESS_SURFACE_UP];
								break;

							case SDLK_DOWN:
								gCurrentSurface = gKeyPressSurfaces[KEY_PRESS_SURFACE_DOWN];
								break;

							case SDLK_LEFT:
								gCurrentSurface = gKeyPressSurfaces[KEY_PRESS_SURFACE_LEFT];
								break;

							case SDLK_RIGHT:
								gCurrentSurface = gKeyPressSurfaces[KEY_PRESS_SURFACE_RIGHT];
								break;

							default:
								gCurrentSurface = gKeyPressSurfaces[KEY_PRESS_SURFACE_DEFAULT];
								break;
						}
					}

					// Check for other key
					if(e.type == SDLK_q)
					{
						printf("The user pressed letter Q!");
					}

					// Apply the image
					SDL_BlitSurface(gCurrentSurface, nullptr, gScreenSurface, nullptr);

					// Update the surface
					SDL_UpdateWindowSurface(gWindow);
				}
			}
		}
	}

	// Free resources and close SDL
	close_my_window();


	return 0;
}


#include "window_logic.hpp"
#include "key_presses.hpp"
#include "media_funcs.hpp"

// CONSTANTS
// 1280 x 720 for testing purposes for window size then eventual 1080p
const int SCREEN_WIDTH = 1280;
const int SCREEN_HEIGHT = 720;

SDL_Window *gWindow = nullptr;

SDL_Surface *gScreenSurface = nullptr;

SDL_Surface *gHelloWorld = nullptr;


bool init_my_window()
{
	bool success = true;

	// Initialize SDL
	if(SDL_Init(SDL_INIT_VIDEO) < 0)
	{
		printf("SDL could not initialize! SDL_Error: %s\n", SDL_GetError());
		success = false;
	}
	else
	{
		// Create window
		gWindow = SDL_CreateWindow("Quincy's SDL Example", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);

		if(gWindow == nullptr)
		{
			printf("Window could not be created! SDL_Error: %s\n", SDL_GetError());
			success = false;
		}
		else
		{
			// Create renderer for window
			gRenderer = SDL_CreateRenderer(gWindow, -1, SDL_RENDERER_ACCELERATED);

			if(gRenderer == nullptr)
			{
				printf("Renderer could not be created! SDL_Error: %s\n",SDL_GetError());
				success = false;
			}
			else
			{
				// Initialize renderer color
				// 0xff is simply 255 in hexadecimal
				SDL_SetRenderDrawColor(gRenderer, 0xff, 0xff, 0xff, 0xff);

				// Initialize PNG loading
				int imgFlags = IMG_INIT_PNG;

				if(!(IMG_Init(imgFlags) & imgFlags))
				{
					printf("SDL_image could not initialize! SDL_image Error: %s\n", IMG_GetError());
					success = false;
				}
			}

			// Get window surface
			gScreenSurface = SDL_GetWindowSurface(gWindow);

			// // Fill the surface white
			// SDL_FillRect(screenSurface, nullptr, SDL_MapRGB(screenSurface->format, 0xFF, 0xFF, 0xFF));

			// Delay so that the color comes in, still some issue that it doesnt always colors in white temp "fix"
			// I saw someone do this youtube and ngl it seems kinda smart to do num/60 SDL_Delay(1000/60);

			// // Update the surface
			// SDL_UpdateWindowSurface(window);

			// // Wait two seconds
			// SDL_Delay(2000);
		}
	}

	return success;
}

void close_my_window()
{
	// Not using hello world no need to deallocate
	// // Deallocate surface
	// SDL_FreeSurface(gHelloWorld);
	// gHelloWorld = nullptr;
	// delete gHelloWorld;

	// Deallocate screenSurface
	SDL_FreeSurface(gScreenSurface);
	gScreenSurface = nullptr;

	// Free loaded image
	SDL_DestroyTexture(gTexture);
	gTexture = nullptr;

	// Destroy window 
	SDL_DestroyWindow(gWindow);
	// Destroy renderer
	SDL_DestroyRenderer(gRenderer);
	gRenderer = nullptr;
	gWindow = nullptr;

	// Quit SDL subsystems
	SDL_Quit();
	// Quit IMG subsystems
	IMG_Quit();
}

void main_loop(SDL_Event e, bool *quit_ptr)
{
	// Handle events on queue
	while(SDL_PollEvent(&e) != 0)
	{
		// User requests quit
		if(e.type == SDL_QUIT)
		{
			// Changes the quit in main to true and exits via the pointer
			*quit_ptr = true;
		}
		// Temp pausing action on selected surface from key selected
		// // User presses a key
		// else if(e.type == SDL_KEYDOWN)
		// {
		// 	// Select surfaces based on key press
		// 	switch(e.key.keysym.sym)
		// 	{
		// 		case SDLK_UP:
		// 			gCurrentSurface = gKeyPressSurfaces[KEY_PRESS_SURFACE_UP];
		// 			break;

		// 		case SDLK_DOWN:
		// 			gCurrentSurface = gKeyPressSurfaces[KEY_PRESS_SURFACE_DOWN];
		// 			break;

		// 		case SDLK_LEFT:
		// 			gCurrentSurface = gKeyPressSurfaces[KEY_PRESS_SURFACE_LEFT];
		// 			break;

		// 		case SDLK_RIGHT:
		// 			gCurrentSurface = gKeyPressSurfaces[KEY_PRESS_SURFACE_RIGHT];
		// 			break;

		// 		default:
		// 			gCurrentSurface = gKeyPressSurfaces[KEY_PRESS_SURFACE_DEFAULT];
		// 			break;
		// 	}
		// }

		// Also not need atm, might make these both functions to compartmentalize
		// // Check for other key
		// if(e.type == SDLK_q)
		// {
		// 	printf("The user pressed letter Q! ;)\n");
		// }

		// This is the non stretched version which maintained the default dimensions
		// // Apply the image
		// SDL_BlitSurface(gCurrentSurface, nullptr, gScreenSurface, nullptr);

		/* not currently displaying the streched screen */
		// // Apply the stretched image
		// SDL_Rect stretchRect;
		// stretchRect.x = 0;
		// stretchRect.y = 0;
		// stretchRect.w = SCREEN_WIDTH;
		// stretchRect.h = SCREEN_HEIGHT;
		// SDL_BlitScaled(gCurrentSurface, nullptr, gScreenSurface, &stretchRect);

		/*
		// Update the surface
		SDL_UpdateWindowSurface(gWindow);
		*/
		// Clear Screen
		SDL_RenderClear(gRenderer);

		// Render texture to screen
		SDL_RenderCopy(gRenderer, gTexture, nullptr, nullptr);

		// Update screen
		SDL_RenderPresent(gRenderer);
	}
}


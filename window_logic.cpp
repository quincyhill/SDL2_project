#include "window_logic.hpp"

// CONSTANTS
const int SCREEN_WIDTH = 800;
const int SCREEN_HEIGHT = 600;

// The window we'll be rendering to
SDL_Window* gWindow = nullptr;

// The surface contained by the window
SDL_Surface* gScreenSurface = nullptr;

// The image we will load and show on the screen
SDL_Surface* gHelloWorld = nullptr;

// Ininitialization flag
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
			// Get window surface
			gScreenSurface = SDL_GetWindowSurface(gWindow);

			// // Fill the surface white
			// SDL_FillRect(screenSurface, nullptr, SDL_MapRGB(screenSurface->format, 0xFF, 0xFF, 0xFF));

			// Delay so that the color comes in, still some issue that it doesnt always colors in white temp "fix"
			SDL_Delay(100);

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
	// Deallocate surface
	SDL_FreeSurface(gHelloWorld);
	gHelloWorld = nullptr;

	// Deallocate screenSurface
	SDL_FreeSurface(gScreenSurface);
	gScreenSurface = nullptr;

	// Destroy window
	SDL_DestroyWindow(gWindow);
	gWindow = nullptr;

	// Quit SDL subsystems
	SDL_Quit();
}


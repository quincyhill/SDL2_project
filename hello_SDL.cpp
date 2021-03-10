// Using SDL and standard IO
#include <SDL2/SDL.h>
#include <stdio.h>

// Screen dimension constants
const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;

int main(int argc, char* args[])
{
	// These two objects are being created and thus need to BOTH be destoyed? not just window

	// The window we'll be rendering to
	SDL_Window* window = nullptr;

	// The surface contained by the window
	SDL_Surface* screenSurface = nullptr;

	// After first initialization
	printf("This is the mem address of the window after being first initialized: %p\n", window);
	printf("This is the mem address of the screensurface after being first initialized: %p\n", screenSurface);


	// Initialize SDL
	if(SDL_Init(SDL_INIT_VIDEO) < 0)
	{
		printf("SDL could not initialize! SDL_Error: %s\n", SDL_GetError());
	}
	else
	{
		// Create window
		window = SDL_CreateWindow("SDL Example", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);

		if(window == nullptr)
		{
			printf("Window could not be created! SDL_Error: %s\n", SDL_GetError());
		}
		else
		{
			// Get window surface
			screenSurface = SDL_GetWindowSurface(window);

			// Fill the surface white
			SDL_FillRect(screenSurface, nullptr, SDL_MapRGB(screenSurface->format, 0xFF, 0xFF, 0xFF));

			// Delay so that the color comes in, still some issue that it doesnt always colors in white temp "fix"
			SDL_Delay(100);

			// Update the surface
			SDL_UpdateWindowSurface(window);

			// Wait two seconds
			SDL_Delay(2000);
		}
	}

	// Before unallocating mem
	printf("This is the mem address of the window before being destroyed: %p\n", window);
	printf("This is the mem address of the screensurface before being destroyed: %p\n", screenSurface);

	// Delete the screenSurface object, I have no idea if this is right lol
	screenSurface = nullptr;
	delete screenSurface;

	// Destroy window
	SDL_DestroyWindow(window);


	// Set the window to null pointer after it is done?
	window = nullptr;

	// After unallocating mem
	printf("This is the mem address of the window after being destroyed: %p\n", window);
	printf("This is the mem address of the screensurface after being destroyed: %p\n", screenSurface);

	// Quit SDL subsystems
	SDL_Quit();

	return 0;
}

#include "media_funcs.hpp" 
#include "window_logic.hpp"
#include "key_presses.hpp"

SDL_Texture *gTexture = nullptr;

SDL_Renderer *gRenderer = nullptr;

bool loadMedia()
{
	// Loading success flag
	bool success = true;


	// // This would be for keypresses
	// success = display_from_keypress(success);

	// Load PNG texture
	gTexture = loadTexture("./assets/img/texture.png");
	if(gTexture == nullptr)
	{
		printf("Failed to load texture image!\n");
		success = false;
	}
	return success;
}

SDL_Texture *loadTexture(std::string path)
{
	// The final texture
	SDL_Texture *newTexture = nullptr;

	// Load image at specified path
	SDL_Surface *loadedSurface = IMG_Load(path.c_str());

	if(loadedSurface == nullptr)
	{
		printf("Unable to load image %s! SDL_image Error: %s\n", path.c_str(), IMG_GetError());
	}
	else
	{
		// Create texture from surface pixels
		newTexture = SDL_CreateTextureFromSurface(gRenderer, loadedSurface);

		if(newTexture == nullptr)
		{
			printf("Unable to create texture from %s! SDL_Error: %s\n", path.c_str(), SDL_GetError());
		}

		// Get rid of old loaded surface
		SDL_FreeSurface(loadedSurface);
	}

	return newTexture;
}



SDL_Surface *loadSurface(std::string path)
{
	// the final optimized image
	SDL_Surface *optimizedSuface = nullptr;

	// The final texture
	SDL_Texture *newTexture = nullptr;

	// // Load image at specified path for bmp
	// sDL_Surface *loadedSurface = SDL_LoadBMP(path.c_str());

	// Load image at specified path for texture
	SDL_Surface *loadedSurface = IMG_Load(path.c_str());

	if(loadedSurface == nullptr)
	{
		printf("Unable to load image %s! SDL Error: %s\n", path.c_str(), SDL_GetError());
	}
	else
	{
		// // Convert surface to screen format
		// optimizedSuface = SDL_ConvertSurface(loadedSurface, gScreenSurface->format, 0);

		// Creae texture from surface pixels
		newTexture = SDL_CreateTextureFromSurface(gRenderer, loadedSurface);
		// if(optimizedSuface == nullptr)
		// {
		// 	printf("Unable to optimize image %s! SDL Error: %s\n", path.c_str(), SDL_GetError());
		// }

		if (newTexture == nullptr)
		{
			printf("Unable to create texture from %s! SDL_Error: %s\n", path.c_str(), SDL_GetError());
		}

		// Get rid of old loaded surface
		SDL_FreeSurface(loadedSurface);
	}
	return optimizedSuface;
}

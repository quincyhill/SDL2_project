#include "media_funcs.hpp" 
#include "window_logic.hpp"
#include "key_presses.hpp"
#include "LTexture.hpp"

SDL_Texture *gTexture = nullptr;

SDL_Renderer *gRenderer = nullptr;

bool loadSpriteData(bool success)
{
	// Load sprite sheet texture
	if(!gSpriteSheetTexture.loadFromFile("./assets/img/spritesheet.png"))
	{
		printf("Failed to load sprite sheet texture!\n");
		success = false;
	}
	else
	{
		// Set top left sprite
		gSpriteClips[0].x = 0;
		gSpriteClips[0].y = 0;
		gSpriteClips[0].w = 180;
		gSpriteClips[0].h = 180;

		// Set top right sprite
		gSpriteClips[1].x = 180;
		gSpriteClips[1].y = 0;
		gSpriteClips[1].w = 180;
		gSpriteClips[1].h = 180;

		// Set bottom left sprite
		gSpriteClips[2].x = 0;
		gSpriteClips[2].y = 180;
		gSpriteClips[2].w = 180;
		gSpriteClips[2].h = 180;

		// Set bottom right sprite
		gSpriteClips[3].x = 180;
		gSpriteClips[3].y = 180;
		gSpriteClips[3].w = 180;
		gSpriteClips[3].h = 180;
	}
	return success;
}

bool loadCharacterAndBackground(bool success)
{
	// Load Foo' texture
	if(!gCharacterTexture.loadFromFile("./assets/img/basiccharacter.png"))
	{
		printf("Failed to load Basic Character texture image!\n");
		success = false;
	}
	else
	{
		printf("Chracter is loaded\n");
	}

	// Load Background texture
	if(!gBackgroundTexture.loadFromFile("./assets/img/sunnybackground.png"))
	{
		printf("Failed to load Background texture image!\n");
		success = false;
	}
	else
	{
		printf("Background is loaded\n");
	}
	return success;
}

bool loadViewportData(bool success)
{
	// viewport texture
	gTexture = loadTexture("./assets/img/viewport.png");
	if(gTexture == nullptr)
	{
		printf("Failed to load png image!\n");
		success = false;
	}
	return success;
}

bool loadMedia()
{
	// Loading success flag
	bool success = true;
	// nothing just white background
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

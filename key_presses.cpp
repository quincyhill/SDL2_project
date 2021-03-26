#include "key_presses.hpp"
#include "media_funcs.hpp"


SDL_Surface *gKeyPressSurfaces[KEY_PRESS_SURFACE_TOTAL];

SDL_Surface *gCurrentSurface = nullptr;

bool display_from_keypress(bool success)
{
	// Load default image
	gKeyPressSurfaces[KEY_PRESS_SURFACE_DEFAULT] = loadSurface("assets/img/key_presses/press.bmp");
	if(gKeyPressSurfaces[KEY_PRESS_SURFACE_DEFAULT] == NULL)
	{
		printf("Failed to load default image!\n");
		success = false;
	}

	// Load up surface
	gKeyPressSurfaces[KEY_PRESS_SURFACE_UP] = loadSurface("assets/img/key_presses/up.bmp");
	if(gKeyPressSurfaces[KEY_PRESS_SURFACE_UP] == NULL)
	{
		printf("Failed to load up image!\n");
		success = false;
	}

	// Load down surface
	gKeyPressSurfaces[KEY_PRESS_SURFACE_DOWN] = loadSurface("assets/img/key_presses/down.bmp");
	if(gKeyPressSurfaces[KEY_PRESS_SURFACE_DOWN] == NULL)
	{
		printf("Failed to load down image!\n");
		success = false;
	}

	// Load left surface
	gKeyPressSurfaces[KEY_PRESS_SURFACE_LEFT] = loadSurface("assets/img/key_presses/left.bmp");
	if(gKeyPressSurfaces[KEY_PRESS_SURFACE_LEFT] == NULL)
	{
		printf("Failed to load left image!\n");
		success = false;
	}

	// Load right surface
	gKeyPressSurfaces[KEY_PRESS_SURFACE_RIGHT] = loadSurface("assets/img/key_presses/right.bmp");
	if(gKeyPressSurfaces[KEY_PRESS_SURFACE_RIGHT] == NULL)
	{
		printf("Failed to load right image!\n");
		success = false;
	}
	return success;
}

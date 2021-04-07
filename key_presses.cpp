#include "key_presses.hpp"
#include "media_funcs.hpp"

SDL_Surface *g_key_press_surfaces[KEY_PRESS_SURFACE_TOTAL];

SDL_Surface *g_current_surface = nullptr;

bool display_from_keypress(bool success)
{
	// Load default image
	g_key_press_surfaces[KEY_PRESS_SURFACE_DEFAULT] = load_surface("assets/img/key_presses/press.bmp");
	if(g_key_press_surfaces[KEY_PRESS_SURFACE_DEFAULT] == NULL)
	{
		printf("Failed to load default image!\n");
		success = false;
	}

	// Load up surface
	g_key_press_surfaces[KEY_PRESS_SURFACE_UP] = load_surface("assets/img/key_presses/up.bmp");
	if(g_key_press_surfaces[KEY_PRESS_SURFACE_UP] == NULL)
	{
		printf("Failed to load up image!\n");
		success = false;
	}

	// Load down surface
	g_key_press_surfaces[KEY_PRESS_SURFACE_DOWN] = load_surface("assets/img/key_presses/down.bmp");
	if(g_key_press_surfaces[KEY_PRESS_SURFACE_DOWN] == NULL)
	{
		printf("Failed to load down image!\n");
		success = false;
	}

	// Load left surface
	g_key_press_surfaces[KEY_PRESS_SURFACE_LEFT] = load_surface("assets/img/key_presses/left.bmp");
	if(g_key_press_surfaces[KEY_PRESS_SURFACE_LEFT] == NULL)
	{
		printf("Failed to load left image!\n");
		success = false;
	}

	// Load right surface
	g_key_press_surfaces[KEY_PRESS_SURFACE_RIGHT] = load_surface("assets/img/key_presses/right.bmp");
	if(g_key_press_surfaces[KEY_PRESS_SURFACE_RIGHT] == NULL)
	{
		printf("Failed to load right image!\n");
		success = false;
	}
	return success;
}

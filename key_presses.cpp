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

void handle_key_press_color_modulation(SDL_Event &r_e, Test_Color_Set &r_test_color_set)
{
	SDL_Event &e = r_e;

	Test_Color_Set &test_color_set = r_test_color_set;
	switch(e.key.keysym.sym)
	{
		// Increase red
		case SDLK_q:
			test_color_set.red += 32;
			break;

		// Increase green
		case SDLK_w:
			test_color_set.green += 32;
			break;

		// Increase blue
		case SDLK_e:
			test_color_set.blue += 32;
			break;

		// Decrease red
		case SDLK_a:
			test_color_set.red -= 32;
			break;

		// Decrease green
		case SDLK_s:
			test_color_set.green -= 32;
			break;

		// Decrease blue
		case SDLK_d:
			test_color_set.blue -= 32;
			break;
	}
	return;
}

void handle_key_press_output_q(SDL_Event &r_e)
{
	SDL_Event &e = r_e;

	switch(e.key.keysym.sym)
	{
		case SDLK_q:
			printf("The user pressed letter Q!\n");
			break;
		default:
			break;
	}
	return;
}

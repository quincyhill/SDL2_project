#include "../include/key_presses.hpp"
#include "../include/window_logic.hpp"
#include "../include/media_funcs.hpp"

SDL_Surface *g_p_key_press_surfaces[KEY_PRESS_SURFACE_TOTAL];

SDL_Surface *g_p_current_surface = nullptr;

void handle_key_press_color_modulation(SDL_Event &r_e)
{
	switch(r_e.key.keysym.sym)
	{
		// Increase red
		case SDLK_q:
			g_main_color_set.red += 32;
			break;

		// Increase green
		case SDLK_w:
			g_main_color_set.green += 32;
			break;

		// Increase blue
		case SDLK_e:
			g_main_color_set.blue += 32;
			break;

		// Decrease red
		case SDLK_a:
			g_main_color_set.red -= 32;
			break;

		// Decrease green
		case SDLK_s:
			g_main_color_set.green -= 32;
			break;

		// Decrease blue
		case SDLK_d:
			g_main_color_set.blue -= 32;
			break;
	}
}

void handle_key_press_output_q(SDL_Event &r_e)
{
	switch(r_e.key.keysym.sym)
	{
		case SDLK_q:
			std::printf("The user pressed letter Q!\n");
			break;
		default:
			break;
	}
}

void handle_key_press_alpha_value(SDL_Event &r_e)
{
	Uint8 max_val = 0xff;
	Uint8 min_val = 0x00;
	Uint8 delta_val = 0x20;

	// Change alpha on key press
	switch(r_e.key.keysym.sym)
	{
		case SDLK_w:
			if(g_alpha_value + delta_val > max_val)
			{
				// max is 255
				g_alpha_value = max_val;
			}
			else
			{
				// inc by 32
				g_alpha_value += delta_val;
			}
			break;
		case SDLK_s:
			if(g_alpha_value - delta_val < min_val)
			{
				// min is 0
				g_alpha_value = min_val;
			}
			else
			{
				// dec by 32
				g_alpha_value -= delta_val;
			}
			break;
		default:
			break;
	}
}

void handle_key_press_rotation_and_flipping(SDL_Event &r_e)
{
	double delta_val = 60;
	switch(r_e.key.keysym.sym)
	{
		case SDLK_a:
			g_degrees -= delta_val;
			break;
		case SDLK_d:
			g_degrees += delta_val;
			break;
		case SDLK_q:
			g_flip_type = SDL_FLIP_HORIZONTAL;
			break;
		case SDLK_w:
			g_flip_type = SDL_FLIP_NONE;
			break;
		case SDLK_e:
			g_flip_type = SDL_FLIP_VERTICAL;
			break;
	}
}

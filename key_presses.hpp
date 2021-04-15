#ifndef KEY_PRESSES_HPP
#define KEY_PRESSES_HPP

#include <SDL2/SDL.h>

// Can just put enums in the header rather than the cpp file just make sure to not redeclare in cpp file
enum Key_Press_Surfaces
{
	KEY_PRESS_SURFACE_DEFAULT,
	KEY_PRESS_SURFACE_UP,
	KEY_PRESS_SURFACE_DOWN,
	KEY_PRESS_SURFACE_LEFT,
	KEY_PRESS_SURFACE_RIGHT,
	KEY_PRESS_SURFACE_TOTAL
};

// Array of key press surfaces
extern SDL_Surface *g_key_press_surfaces[];

// Currently displayed image
extern SDL_Surface *g_current_surface;

/*
 * Functions
 */

// Handle keypress for color moduation
void handle_key_press_color_modulation(SDL_Event &r_e);

// Handle keypress for outputting the letter q, for testing purposes
void handle_key_press_output_q(SDL_Event &r_e);

// Handle keypress for changing alpha values
void handle_key_press_alpha_value(SDL_Event &r_e);

// Handle keypress for flipping and rotation
void handle_key_press_rotation_and_flipping(SDL_Event &r_e);
#endif

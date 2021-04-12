#ifndef WINDOW_LOGIC_HPP
#define WINDOW_LOGIC_HPP

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <string>
#include <stdio.h>

/*
 * extern is used for variables and pointers functions are just the way they are
 */

struct Test_Color_Set
{
	Uint8 red;
	Uint8 green;
	Uint8 blue;
};

// These are the constants for screen sizes
extern const int SCREEN_WIDTH;
extern const int SCREEN_HEIGHT;

// Might prepend p_ to all pointers in the future...

// The window we'll be rendering to
extern SDL_Window *g_window;

// The surface contained by the window
extern SDL_Surface *g_screen_surface;

// The stretched surface
extern SDL_Surface *g_stretched_surface;

/*
 * Functions go here
 */

// Basic Window creation 
bool create_basic_window(bool success, std::string title);

// Advanced Window creation 
bool create_advanced_window(bool success);

// Set texture filtering
void set_texture_filtering();

// Main initialization function
bool init_my_window();

// Close window for simple png image
void close_basic_window();

// Clears the window along with freeing memeory
void close_my_window();

// Main window loop, logic for every iteration goes here
bool main_loop(bool quit, SDL_Event &e_ref);

// Handle keypress switching, used if I have other things maps to different keys
void handle_key_press_switching(SDL_Event e);

// Hanle keypress for color moduation
void handle_key_press_color_modulation(SDL_Event e, Test_Color_Set &test_color_ref);

// Display simple white screen
void display_single_color_screen();

// Here is for displaying viewports
void display_viewports_to_screen();

// display some basic image
void display_basic_non_scaled_image();

// display scaled image
void display_basic_scaled_image();

// display screen with colors and lines
void display_quads_and_lines();

// display sprite clips, this one needs some fixing
void display_sprite_clips();

// display character and background to screen, this one needs some fixing
void display_character_and_background();

// display sectioned screen with color moduation
void display_color_modulation(SDL_Event e, Test_Color_Set &test_color_ref);

#endif

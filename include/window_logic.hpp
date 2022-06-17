#ifndef WINDOW_LOGIC_HPP
#define WINDOW_LOGIC_HPP
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <string>
#include <cstdio>

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

// Global color set
extern Test_Color_Set g_main_color_set;
extern Uint8 g_alpha_value;

// Global animation frame
extern int g_animation_frame;

// Global window we'll be rendering to
extern SDL_Window *g_p_window;

// Global surface contained by the window
extern SDL_Surface *g_p_screen_surface;

// Gloabl stretched surface
extern SDL_Surface *g_p_stretched_surface;

// Global flip type
extern SDL_RendererFlip g_flip_type;

// Global degrees value
extern double g_degrees;

/*
 * Functions go here
 */

// Create basic window with texture rendering 
bool create_basic_window_via_surface(bool success, std::string title);

// Create basic window with surface rendering
bool create_basic_window_via_texture(bool success, std::string title);

// Create basic window with surface rendering with ttf library
bool create_basic_window_via_texture_with_ttf(bool success, std::string title);

// Create vsynced window with texture rendering
bool create_vsynced_window_via_texture(bool success, std::string title);

// Set texture filtering setting
void set_texture_filtering();

// Main initialization function
bool init_my_window();

// Close window for surface loaded png 
void close_basic_window_surface();

// Close window for texture loaded image
void close_basic_window_texture();

// Closes window for sprite sheets
void close_sprite_sheets();

// Close arrow
void close_arrow();

#if defined(SDL_TTF_MAJOR_VERSION)
// Closes window for fonts
void close_fonts();
#endif

// Clears the window along with freeing memeory
void close_my_window();

// Main window loop, logic for every iteration goes here
bool main_loop(bool quit, SDL_Event &r_e);

// Handle keypress switching, used if I have other things maps to different keys
void handle_key_press_switching(SDL_Event e);

// Display simple white screen
void display_single_color_screen();

// Here is for displaying viewports
void display_viewports_to_screen();

// Display some basic surface image
void display_basic_non_scaled_surface_image();

// Display some basic texture image
void display_basic_scaled_texture_image();

// Display scaled image
void display_basic_scaled_image();

// Display screen with colors and lines
void display_quads_and_lines();

// Display sprite clips, this one needs some fixing
void display_sprite_clips();

// Display character and background to screen, this one needs some fixing
void display_character_and_background();

// Display sectioned screen with color moduation
void display_color_modulation();

// Display alpha blending
void display_alpha_blending();

// Display animated sprites
void display_animated_sprites();

// Display rotation and flipping
void display_rotation_and_flipping();

#if defined(SDL_TTF_MAJOR_VERSION)
// Display true tone fonts
void display_font();
#endif

// Display Buttons
void display_buttons();

#endif

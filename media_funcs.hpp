#ifndef MEDIA_FUNCS_HPP
#define MEDIA_FUNCS_HPP

// This loads the png that I have put
#include "window_logic.hpp"

// Image sizes are 640 x 480 unless otherwise stated, including both png and bmp, this is used for stretching testing and wrapping

// Current displayed texture
extern SDL_Texture *g_texture;

// The Window we'll be rendering to
extern SDL_Renderer *g_renderer;

/*
 * Functions
 */

// Load sprite sheet, is ran in loadMedia func
bool load_sprite_data(bool success);

// Load background and character test
bool load_character_and_background(bool success);

// Load images for the viewport
bool load_viewport_data(bool success);

// Load bitmap image, remeber to use .c_str at the end of the std::string so everything `fits`
bool load_bitmap_image(bool success, std::string img_path);

// Loads the final assets into mem
bool load_media();

// Loads individual image
SDL_Surface *load_surface(std::string img_path);

// Loads individual image as texture
SDL_Texture *load_texture(std::string img_path);

#endif

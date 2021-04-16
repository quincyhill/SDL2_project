#ifndef MEDIA_FUNCS_HPP
#define MEDIA_FUNCS_HPP

// This loads the png that I have put
#include <SDL2/SDL.h>
#include <string>

// Image sizes are 640 x 480 unless otherwise stated, this is used for stretching testing and wrapping

// Current displayed texture
extern SDL_Texture *g_texture;

// The Window we'll be rendering to
extern SDL_Renderer *g_renderer;

// The current png surface
extern SDL_Surface *g_png_surface;

/*
 * Functions
 */

// Load sprite sheet, is ran in loadMedia func
bool load_sprite_data(bool success);

// Load background and character test
bool load_character_and_background(bool success);

// Load images for the viewport
bool load_viewport_data(bool success);

// Load png image, remeber to use .c_str at the end of the std::string so everything `fits`
bool load_png_image(bool success, std::string img_path);

// Load alpha blending textures
bool load_alpha_blending_textures(bool success);

// Load font texture
bool load_font_texture(bool success);

// Loads the final assets into mem, should eventually allow arrays of paths to load ALL the media sources
bool load_media();

// Loads png surface *** Needs Implementation ***
SDL_Surface *load_png_surface(std::string img_path, SDL_Surface &optimized_surface);

// Loads individual surface
SDL_Surface *load_surface(std::string img_path);

// Loads individual image as texture
SDL_Texture *load_texture(std::string img_path);

#endif

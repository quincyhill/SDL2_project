#ifndef MEDIA_FUNCS_HPP
#define MEDIA_FUNCS_HPP

// This loads the png that I have put
#include "window_logic.hpp"

// Image sizes are 640 x 480 unless otherwise stated, including both png and bmp, this is used for stretching testing and wrapping

// Current displayed texture
extern SDL_Texture *gTexture;

// The Window we'll be rendering to
extern SDL_Renderer *gRenderer;

/*
 * Functions
 */

// Load sprite sheet, is ran in loadMedia func
bool loadSpriteData(bool success);

// Load background and character test
bool loadCharacterAndBackground(bool success);

// Load images for the viewport
bool loadViewportData(bool success);

// Loads the final assets into mem
bool loadMedia();

// Loads individual image
SDL_Surface *loadSurface(std::string path);

// Loads individual image as texture
SDL_Texture *loadTexture(std::string path);

#endif

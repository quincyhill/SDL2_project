#ifndef WINDOW_LOGIC_HPP
#define WINDOW_LOGIC_HPP

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <string>
#include <stdio.h>

/*
 * extern is used for variables and pointers functions are just the way they are
 */

// These are the constants for screen sizes
extern const int SCREEN_WIDTH;
extern const int SCREEN_HEIGHT;

// The window we'll be rendering to
extern SDL_Window *gWindow;

// The surface contained by the window
extern SDL_Surface *gScreenSurface;

// The image we will load and show on the screen
extern SDL_Surface *gHelloWorld;


/*
 * Functions go here
 */


// Ininitialization flag responsible for setting up the window
bool init_my_window();

// Clears the window along with freeing memeory
void close_my_window();

// Main window loop essentially the buik of activity
void main_loop(SDL_Event e, bool *quit_ptr);

#endif

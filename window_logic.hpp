#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <string>
/*
 * extern is used for variables and pointers functions are just the way they are
 */

// The window we'll be rendering to
extern SDL_Window* gWindow;

// The surface contained by the window
extern SDL_Surface* gScreenSurface;

// The image we will load and show on the screen
extern SDL_Surface* gHelloWorld;

// Loads individual image
extern SDL_Surface* loadSurface(std::string);

/*
 * Fucntions go here
 */

// Ininitialization flag responsible for setting up the window
bool init_my_window();

// Clears the window along with freeing memeory
void close_my_window();

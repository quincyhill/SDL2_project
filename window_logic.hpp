#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
// Apparently you use extern to declare variables in header files for c++
extern SDL_Window* gWindow;
extern SDL_Surface* gScreenSurface;
extern SDL_Surface* gHelloWorld;

// Functions here
bool init_my_window();
void close_my_window();

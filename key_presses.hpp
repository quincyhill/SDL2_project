#include <SDL2/SDL.h>

// Can just put enums in the header rather than the cpp file just make sure to not redeclare in cpp file
enum KeyPressSurfaces
{
	KEY_PRESS_SURFACE_DEFAULT,
	KEY_PRESS_SURFACE_UP,
	KEY_PRESS_SURFACE_DOWN,
	KEY_PRESS_SURFACE_LEFT,
	KEY_PRESS_SURFACE_RIGHT,
	KEY_PRESS_SURFACE_TOTAL
};

// This are the surfaces
extern SDL_Surface* gKeyPressSurfaces[];

// Current displayed image
extern SDL_Surface* gCurrentSurface;


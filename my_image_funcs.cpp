#include "my_image_funcs.hpp" 
#include "window_logic.hpp"
bool loadMedia()
{
	// Loading success flag
	bool success = true;

	// Load helloworld.jpg image
	SDL_RWops* rwop;
	rwop = SDL_RWFromFile("assets/img/helloworld.png", "rb");

	// Gotta figure out what anonymous namespace means 
	gHelloWorld = IMG_LoadPNG_RW(rwop);

	return success;
}

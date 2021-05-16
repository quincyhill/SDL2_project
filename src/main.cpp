// Using SDL and standard IO
#include <SDL2/SDL.h>
#include <SDL2/SDL_keycode.h>
#include <SDL2/SDL_surface.h>
#include <SDL2/SDL_mixer.h>
#include <SDL2/SDL_image.h>
#include "../include/window_logic.hpp"
#include "../include/media_funcs.hpp"
#include <stdio.h>
#include <cstdlib>
#include <string.h>

int main(int argc, char *args[])
{
	//Start up SDL and create window
	if(!init_my_window())
	{
		printf("Failed to initialize!\n");
	}
	else
	{
		//Load media
		if(!load_media())
		{
			printf( "Failed to load media!\n" );
		}
		else
		{	
			//Main loop flag
			bool quit = false;

			//Event handler
			SDL_Event e;

			//While application is running
			while(!quit)
			{
				quit = main_loop(quit, e);
			}
		}
	}
	//Free resources and close SDL
	close_my_window();
	return 0;
}

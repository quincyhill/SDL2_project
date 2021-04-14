// Using SDL and standard IO
#include <SDL2/SDL.h>
#include <SDL2/SDL_keycode.h>
#include <SDL2/SDL_surface.h>
#include <SDL2/SDL_mixer.h>
#include <stdio.h>
#include <string>
#include "media_funcs.hpp"
#include "window_logic.hpp"

/*This source code copyrighted by Lazy Foo' Productions (2004-2020)
and may not be redistributed without written permission.*/

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
			while( !quit )
			{
				quit = main_loop(quit, e);
			}
		}
	}
	//Free resources and close SDL
	close_my_window();

	return 0;
}

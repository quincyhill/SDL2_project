#include "window_logic.hpp"
#include "key_presses.hpp"
#include "media_funcs.hpp"
#include "L_Texture.hpp"

// CONSTANTS
// 1280 x 720 for testing purposes for window size then eventual 1080p
const int SCREEN_WIDTH = 1280;
const int SCREEN_HEIGHT = 720;

SDL_Window *g_window = nullptr;

SDL_Surface *g_screen_surface = nullptr;

SDL_Surface *g_hello_world = nullptr;

void set_texture_filtering()
{
	// Set texture filtering to linear, don't know if this is needed here
	if(!SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "1"))
	{
		printf("Warning: Linear texture filtering not enabled!");
	}
	return;
}
bool create_basic_window(bool success)
{
	g_window = SDL_CreateWindow("Quincy's SDL Example", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
	if(g_window == nullptr)
	{
		printf("Window could not be created! SDL_Error: %s\n", SDL_GetError());
		success = false;
	}
	else
	{
		// get window surface
		g_screen_surface = SDL_GetWindowSurface(g_window);
	}
	return success;
}

bool create_advanced_window(bool success)
{
	// Create window
	g_window = SDL_CreateWindow("Quincy's SDL Example", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);

	if(g_window == nullptr)
	{
		printf("Window could not be created! SDL_Error: %s\n", SDL_GetError());
		success = false;
	}
	else
	{
		// Create renderer for window
		g_renderer = SDL_CreateRenderer(g_window, -1, SDL_RENDERER_ACCELERATED);

		if(g_renderer == nullptr)
		{
			printf("Renderer could not be created! SDL_Error: %s\n",SDL_GetError());
			success = false;
		}
		else
		{
			// Initialize renderer color
			// 0xff is simply 255 in hexadecimal, so white in this case
			SDL_SetRenderDrawColor(g_renderer, 0xff, 0xff, 0xff, 0xff);

			// Initialize PNG loading
			int imgFlags = IMG_INIT_PNG;

			if(!(IMG_Init(imgFlags) & imgFlags))
			{
				printf("SDL_image could not initialize! SDL_image Error: %s\n", IMG_GetError());
				success = false;
			}
		}

		// // Get window surface
		// g_screen_surface = SDL_GetWindowSurface(g_window);

		// // Fill the surface white
		// SDL_FillRect(screenSurface, nullptr, SDL_MapRGB(screenSurface->format, 0xFF, 0xFF, 0xFF));

		// Delay so that the color comes in, still some issue that it doesnt always colors in white temp "fix"
		// I saw someone do this youtube and ngl it seems kinda smart to do num/60 SDL_Delay(1000/60);

		// // Update the surface
		// SDL_UpdateWindowSurface(window);

		// // Wait two seconds
		// SDL_Delay(2000);
	}
	return success;
}

bool init_my_window()
{
	// Ininitialization flag
	bool success = true;

	// Initialize SDL
	if(SDL_Init(SDL_INIT_VIDEO) < 0)
	{
		printf("SDL could not initialize! SDL_Error: %s\n", SDL_GetError());
		success = false;
	}
	else
	{
		// uncomment if texture filtering is needed
		// set_texture_filtering();

		// chose which window to use
		success = create_basic_window(success);

	}

	return success;
}

void close_hello_world_window()
{
	// Deallocate surface
	SDL_FreeSurface(g_hello_world);
	g_hello_world = nullptr;

	// Destroy Window
	SDL_DestroyWindow(g_window);
	g_window = nullptr;

	// Quit SDL Subsystems
	SDL_Quit();
}


void close_my_window()
{
	// Depends on how I set up the window and its actions
	close_hello_world_window();
}

void handle_key_press_switching(SDL_Event e)
{
	switch(e.key.keysym.sym)
	{
		case SDLK_UP:
			g_current_surface = g_key_press_surfaces[KEY_PRESS_SURFACE_UP];
			break;

		case SDLK_DOWN:
			g_current_surface = g_key_press_surfaces[KEY_PRESS_SURFACE_DOWN];
			break;

		case SDLK_LEFT:
			g_current_surface = g_key_press_surfaces[KEY_PRESS_SURFACE_LEFT];
			break;

		case SDLK_RIGHT:
			g_current_surface = g_key_press_surfaces[KEY_PRESS_SURFACE_RIGHT];
			break;

		default:
			g_current_surface = g_key_press_surfaces[KEY_PRESS_SURFACE_DEFAULT];
			break;
	}

}

void display_single_color_screen()
{
	// Dont forget to deallocate g_renderer when screen is closed
	SDL_SetRenderDrawColor(g_renderer, 0xdd, 0xff, 0xff, 0xff);
	SDL_RenderClear(g_renderer);
	
	// Update screen
	SDL_RenderPresent(g_renderer);

	return;
}

void display_bitmap_image()
{
	// Apply the image
	SDL_BlitSurface(g_hello_world, nullptr, g_screen_surface, nullptr);

	// Update the surface
	SDL_UpdateWindowSurface(g_window);

	// no need to wait since i've already programmed in the logic for looping the screen
}

void display_viewports_to_screen()
{
	// Top Left corner viewport
	SDL_Rect topLeftViewport;
	topLeftViewport.x = 0;
	topLeftViewport.y = 0;
	topLeftViewport.w = SCREEN_WIDTH / 2;
	topLeftViewport.h = SCREEN_HEIGHT / 2;
	SDL_RenderSetViewport(g_renderer, &topLeftViewport);

	// Render png texture to screen
	SDL_RenderCopy(g_renderer, g_texture, nullptr, nullptr);

	// Top right viewport
	SDL_Rect topRightViewport;
	topRightViewport.x = SCREEN_WIDTH / 2;
	topRightViewport.y = 0;
	topRightViewport.w = SCREEN_WIDTH / 2;
	topRightViewport.h = SCREEN_HEIGHT / 2;
	SDL_RenderSetViewport(g_renderer, &topRightViewport);

	// Render png texture to screen
	SDL_RenderCopy(g_renderer, g_texture, nullptr, nullptr);

	// bottom viewport
	SDL_Rect bottomViewport;
	bottomViewport.x = 0;
	bottomViewport.y = SCREEN_HEIGHT / 2;
	bottomViewport.w = SCREEN_WIDTH;
	bottomViewport.h = SCREEN_HEIGHT / 2;
	SDL_RenderSetViewport(g_renderer, &bottomViewport);

	// Render png texture to screen
	SDL_RenderCopy(g_renderer, g_texture, nullptr, nullptr);

	// Update the screen
	SDL_RenderPresent(g_renderer);
	return;
}

void display_basic_non_scaled_image()
{
	// Apply the image to screen
	// make sure the current surface pointer has valid information
	SDL_BlitSurface(g_current_surface, nullptr, g_screen_surface, nullptr);
	SDL_UpdateWindowSurface(g_window);
	return;
}

void display_basic_scaled_image()
{
	// Apply the stretched image
	SDL_Rect stretchRect;
	stretchRect.x = 0;
	stretchRect.y = 0;
	stretchRect.w = SCREEN_WIDTH;
	stretchRect.h = SCREEN_HEIGHT;
	SDL_BlitScaled(g_current_surface, nullptr, g_screen_surface, &stretchRect);

	// Update the surface
	SDL_UpdateWindowSurface(g_window);

	// Clear Screen
	SDL_RenderClear(g_renderer);

	// Render texture to screen
	SDL_RenderCopy(g_renderer, g_texture, nullptr, nullptr);

	// Update screen
	SDL_RenderPresent(g_renderer);
	return;
}

void display_quads_and_lines()
{
	// Render red filled quad
	SDL_Rect fillRect = {SCREEN_WIDTH / 4, SCREEN_HEIGHT / 4, SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2};
	// Red hex colors (r,g,b,a)
	SDL_SetRenderDrawColor(g_renderer, 0xff, 0x00, 0x00, 0xff);
	SDL_RenderFillRect(g_renderer, &fillRect);

	// Render green outlined quad
	SDL_Rect outlineRect = {SCREEN_WIDTH / 6, SCREEN_HEIGHT / 6, SCREEN_WIDTH * 2 / 3, SCREEN_HEIGHT * 2 / 3};
	// Green hex colors (r,g,b,a)
	SDL_SetRenderDrawColor(g_renderer, 0x00, 0xff, 0x00, 0xff);
	SDL_RenderDrawRect(g_renderer, &outlineRect);

	// Render blue horizontal line
	SDL_SetRenderDrawColor(g_renderer, 0x00, 0x00, 0xff, 0xff);
	SDL_RenderDrawLine(g_renderer, 0, SCREEN_HEIGHT / 2, SCREEN_WIDTH, SCREEN_HEIGHT / 2);

	// Draw vertical line of yellow dots
	SDL_SetRenderDrawColor(g_renderer, 0xff, 0xff, 0x00, 0xff);
	for(int i = 0; i < SCREEN_HEIGHT; i+=4)
	{
		SDL_RenderDrawPoint(g_renderer, SCREEN_WIDTH / 2, i);
	}
	return;
}

void display_character_and_background()
{
	// Render background texture to screen
	g_background_texture.render(0, 0);

	// Render Character to the screen
	g_character_texture.render((SCREEN_WIDTH / 2) - 50, (SCREEN_HEIGHT / 2) - 150);
	return;
}

void display_sprite_clips()
{
	// Clear Screen, whats going on with the g_renderer
	SDL_SetRenderDrawColor(g_renderer, 0xff, 0xff, 0xff, 0xff);
	SDL_RenderClear(g_renderer);

	// Logging data to console
	for(int i = 0; i < 4; i++)
	{
		printf("Value of g_sprite_clips[%i]'s x,y,w,h is: %i, %i, %i, %i\n", i, g_sprite_clips[i].x, g_sprite_clips[i].y, g_sprite_clips[i].w, g_sprite_clips[i].h);
		printf("Value of g_sprite_clips[%i]'s memory loc is: %p \n\n", i, &g_sprite_clips[i]);
	}

	// Render top left sprite
	g_sprite_sheet_texture.render(0, 0, &g_sprite_clips[0]);

	// Render top right sprite
	g_sprite_sheet_texture.render(SCREEN_WIDTH - g_sprite_clips[1].w, 0, &g_sprite_clips[1]);

	// Render bottom left sprite
	g_sprite_sheet_texture.render(0, SCREEN_HEIGHT - g_sprite_clips[2].h, &g_sprite_clips[2]);

	// Render bottom right sprite
	g_sprite_sheet_texture.render(SCREEN_WIDTH - g_sprite_clips[3].w, SCREEN_HEIGHT - g_sprite_clips[3].h, &g_sprite_clips[3]);

	// Update the screen
	SDL_RenderPresent(g_renderer);
	return;
}

void handle_key_press_color_modulation(SDL_Event e, Test_Color_Set &test_color_ref)
{
	Test_Color_Set &myTest_Color_Set = test_color_ref;
	switch(e.key.keysym.sym)
	{
		// Increase red
		case SDLK_q:
			myTest_Color_Set.red += 32;
			break;

		// Increase green
		case SDLK_w:
			myTest_Color_Set.green += 32;
			break;

		// Increase blue
		case SDLK_e:
			myTest_Color_Set.blue += 32;
			break;

		// Decrease red
		case SDLK_a:
			myTest_Color_Set.red -= 32;
			break;

		// Decrease green
		case SDLK_s:
			myTest_Color_Set.green -= 32;
			break;

		// Decrease blue
		case SDLK_d:
			myTest_Color_Set.blue -= 32;
			break;
	}
	return;
}

void display_color_modulation(SDL_Event e, Test_Color_Set &test_color_ref)
{
	Test_Color_Set &myTest_Color_Set = test_color_ref;
	// Clear screen, set it white
	SDL_SetRenderDrawColor(g_renderer, 0xcd, 0xff, 0xff, 0xff);
	SDL_RenderClear(g_renderer);

	// Modulate and render texture
	g_modulated_texture.set_color(myTest_Color_Set.red, myTest_Color_Set.green, myTest_Color_Set.blue);
	g_modulated_texture.render(0,0);

	// Update screen
	SDL_RenderPresent(g_renderer);
	return;
}

bool main_loop(bool quit, Test_Color_Set &test_color_ref)
{
	// Event handler
	SDL_Event e;
	// Create reference alias for quit_ref, no need to clear because all references have to point to a valid address aka NOT NULL

	// Create reference alias for test_color_ref, no need to clear because all references have to point to a valid address aka NOT NULL
	Test_Color_Set &myTest_Color_Set = test_color_ref;

	// Handle events on queue
	while(SDL_PollEvent(&e) != 0)
	{	
		// User requests quit
		if(e.type == SDL_QUIT)
		{
			// Changes the quit in main to true and exits via the pointer
			quit = true;
		}
		// Temp pausing action on selected surface from key selected
		else if(e.type == SDL_KEYDOWN)
		{
			// This would be for color modulation
			// handleKeyPressColorModulation(e,myTest_Color_Set);
			// in this case theres nothing to swith to atm so dont do anything
			// handleKeyPressSwitching(e);

			// This will print q if it is held down every loop
			switch(e.key.keysym.sym)
			{
				case SDLK_q:
					printf("The user pressed letter Q!\n");
					break;
				default:
					break;
			}
		}
		/* Here goes the screen related logic */
		display_bitmap_image();
	}
	return quit;
}


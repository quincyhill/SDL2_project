#include "window_logic.hpp"
#include "key_presses.hpp"
#include "media_funcs.hpp"
#include "L_Texture.hpp"

// CONSTANTS
// 1280 x 720 for testing purposes for window size then eventual 1080p
const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;

SDL_Window *g_window = nullptr;

SDL_Surface *g_screen_surface = nullptr;

SDL_Surface *g_stretched_surface = nullptr;

Test_Color_Set g_main_color_set = {255, 255, 255};

void set_texture_filtering()
{
	// Set texture filtering to linear, don't know if this is needed here
	if(!SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "1"))
	{
		printf("Warning: Linear texture filtering not enabled!\n");
	}
	return;
}
bool create_basic_window_surface(bool success, std::string title)
{
	// will not use title string for now... title.c_str();
	g_window = SDL_CreateWindow(title.c_str(), SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
	if(g_window == nullptr)
	{
		printf("Window could not be created! SDL_Error: %s\n", SDL_GetError());
		success = false;
	}
	else
	{
		// Initialize PNG loading
		int img_flags = IMG_INIT_PNG;
		if(!(IMG_Init(img_flags) & img_flags))
		{
			printf("SDL_image could not initialize! SDL_image_Error:%s\n", IMG_GetError());
			success = false;
		}
		else
		{
			// Get window surface
			g_screen_surface = SDL_GetWindowSurface(g_window);
		}
	}
	return success;
}

bool create_basic_window_texture(bool success, std::string title)
{
	// Create window
	g_window = SDL_CreateWindow(title.c_str(), SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
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
			printf("Renderer could not be created! SDL_Error: %s\n", SDL_GetError());
			success = false;
		}
		else
		{
			// Initialize render color
			SDL_SetRenderDrawColor(g_renderer, 0xff, 0xff ,0xff, 0xff);

			// Initialize PNG loading
			int img_flags = IMG_INIT_PNG;
			if(!(IMG_Init(img_flags) & img_flags))
			{
				printf("SDL_image could not initialize! SDL_image_Error: %s\n", IMG_GetError());
				success = false;
			}
		}
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
		// // Create window here
		// success = create_basic_window_surface(success, "Quincy's Basic Window");
		// Create window from texture here

		set_texture_filtering();
		success = create_basic_window_texture(success, "Quincy's Basic Window from Texture");
		printf("Basic window initialized here\n");
	}
	return success;
}

void close_basic_window_surface()
{
	// Free loaded image
	SDL_DestroyTexture(g_texture);
	g_texture = nullptr;

	// Destory Window
	SDL_DestroyRenderer(g_renderer);
	SDL_DestroyWindow(g_window);

	g_window = nullptr;
	g_renderer = nullptr;

	// Quit SDL subsystems
	IMG_Quit();
	SDL_Quit();
	return;
}

void close_basic_window_texture()
{
	// Free loaded images
	SDL_DestroyTexture(g_texture);
	g_texture = nullptr;

	// Destory window
	SDL_DestroyRenderer(g_renderer);
	SDL_DestroyWindow(g_window);
	g_renderer = nullptr;
	g_window = nullptr;

	// Quit SDL subsystems
	IMG_Quit();
	SDL_Quit();
	return;
}

void close_color_set()
{
	// Free texture
	g_modulated_texture.free_texture();

	// Destroy window
	SDL_DestroyRenderer(g_renderer);
	SDL_DestroyWindow(g_window);
	g_renderer = nullptr;
	g_window = nullptr;

	// Quit SDL subsystems
	IMG_Quit();
	SDL_Quit();
	return;
}


void close_my_window()
{
	// Depends on how I set up the window and its actions
	close_color_set();
	return;
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

void display_basic_non_scaled_surface_image()
{
	// Apply the PNG Image
	SDL_BlitSurface(g_png_surface, nullptr, g_screen_surface, nullptr);

	// Update the surface
	SDL_UpdateWindowSurface(g_window);
	return;
}

void display_basic_scaled_texture_image()
{
	// Clear screen
	SDL_RenderClear(g_renderer);

	// Render texture to screen
	SDL_RenderCopy(g_renderer, g_texture, nullptr, nullptr);

	// Update screen
	SDL_RenderPresent(g_renderer);
	return;
}


void display_basic_scaled_image()
{
	// Apply the stretched image
	SDL_Rect stretch_rect;
	stretch_rect.x = 0;
	stretch_rect.y = 0;
	stretch_rect.w = SCREEN_WIDTH;
	stretch_rect.h = SCREEN_HEIGHT;
	SDL_BlitScaled(g_current_surface, nullptr, g_screen_surface, &stretch_rect);

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
		printf("Value of g_sprite_clips[%i]'s memory loc is: %p \n", i, &g_sprite_clips[i]);
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


void display_color_modulation()
{
	// Clear screen, set it white
	SDL_SetRenderDrawColor(g_renderer, 0xff, 0xff, 0xff, 0xff);
	SDL_RenderClear(g_renderer);

	// Modulate and render texture
	g_modulated_texture.set_color(g_main_color_set.red, g_main_color_set.green, g_main_color_set.blue);
	g_modulated_texture.render(0,0);

	// Update screen
	SDL_RenderPresent(g_renderer);
	return;
}

bool main_loop(bool quit, SDL_Event &e_ref)
{
	// Event handler
	SDL_Event &e = e_ref;

	// *** KEYBOARD DRIVEN EVENTS *** //
	// Handle events on queue
	while(SDL_PollEvent(&e) != 0)
	{	
		// User requests quit
		if(e.type == SDL_QUIT)
		{
			// Changes the quit in main to true and exits via the pointer
			quit = true;
		}
		// Handles events for button press downs
		else if(e.type == SDL_KEYDOWN)
		{
			// This will print q if it is held down every loop, put this in key_presses.cpp
			handle_key_press_color_modulation(e,g_main_color_set);
		}
	}
	// *** DISPLAY RELATED CODE *** //
	display_color_modulation();
	return quit;
}


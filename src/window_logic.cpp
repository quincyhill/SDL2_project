#include "../include/window_logic.hpp"
#include "../include/key_presses.hpp"
#include "../include/media_funcs.hpp"
#include "../include/L_Texture.hpp"
#include "../include/L_Button.hpp"

// CONSTANTS
// 1280 x 720 for testing purposes for window size then eventual 1080p
const int SCREEN_WIDTH = 1280;
const int SCREEN_HEIGHT = 720;

SDL_Window *g_p_window = nullptr;

SDL_Surface *g_p_screen_surface = nullptr;

SDL_Surface *g_p_stretched_surface = nullptr;

Test_Color_Set g_main_color_set = {255, 255, 255};

Uint8 g_alpha_value = 255;

int g_animation_frame = 0;

double g_degrees = 0;

SDL_RendererFlip g_flip_type = SDL_FLIP_NONE;

void set_texture_filtering()
{
	// Set texture filtering to linear, don't know if this is needed here
	if(!SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "1"))
	{
		printf("Warning: Linear texture filtering not enabled!\n");
	}
	return;
}

bool create_vsynced_window_via_texture(bool success, std::string title)
{
	// Create window
	g_p_window = SDL_CreateWindow(title.c_str(), SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
	if(g_p_window == nullptr)
	{
		printf("Window could not be created! SDL_Error: %s\n", SDL_GetError());
		success = false;
	}
	else
	{
		// Create vsynced renderer for window
		g_p_renderer = SDL_CreateRenderer(g_p_window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
		if(g_p_renderer == nullptr)
		{
			printf("Renderer could not be created! SDL_Error: %s\n", SDL_GetError());
			success = false;
		}
		else
		{
			// Initialize render color
			SDL_SetRenderDrawColor(g_p_renderer, 0xff, 0xff ,0xff, 0xff);

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

bool create_basic_window_via_surface(bool success, std::string title)
{
	// Create window
	g_p_window = SDL_CreateWindow(title.c_str(), SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
	if(g_p_window == nullptr)
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
			g_p_screen_surface = SDL_GetWindowSurface(g_p_window);
		}
	}
	return success;
}

bool create_basic_window_via_texture_with_ttf(bool success, std::string title)
{
	// Create window
	g_p_window = SDL_CreateWindow(title.c_str(), SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
	if(g_p_window == nullptr)
	{
		printf("Window could not be created! SDL_Error: %s\n", SDL_GetError());
		success = false;
	}
	else
	{
		// Create renderer for window
		g_p_renderer = SDL_CreateRenderer(g_p_window, -1, SDL_RENDERER_ACCELERATED);
		if(g_p_renderer == nullptr)
		{
			printf("Renderer could not be created! SDL_Error: %s\n", SDL_GetError());
			success = false;
		}
		else
		{
			// Initialize render color to white
			SDL_SetRenderDrawColor(g_p_renderer, 0xff, 0xff ,0xff, 0xff);

			// Initialize PNG loading
			int img_flags = IMG_INIT_PNG;
			if(!(IMG_Init(img_flags) & img_flags))
			{
				printf("SDL_image could not initialize! SDL_image_Error: %s\n", IMG_GetError());
				success = false;
			}

			// Dont need this atm since im not using TTF lib

			// Initialize SDL_ttf
			if(TTF_Init() == -1)
			{
				printf("SDL_ttf could not initialize! SDL_ttf Error: %s\n", TTF_GetError());
				success = false;
			}
		}
	}
	return success;
}

bool create_basic_window_via_texture(bool success, std::string title)
{
	// Create window
	g_p_window = SDL_CreateWindow(title.c_str(), SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
	if(g_p_window == nullptr)
	{
		printf("Window could not be created! SDL_Error: %s\n", SDL_GetError());
		success = false;
	}
	else
	{
		// Create renderer for window
		g_p_renderer = SDL_CreateRenderer(g_p_window, -1, SDL_RENDERER_ACCELERATED);
		if(g_p_renderer == nullptr)
		{
			printf("Renderer could not be created! SDL_Error: %s\n", SDL_GetError());
			success = false;
		}
		else
		{
			// Initialize render color to white
			SDL_SetRenderDrawColor(g_p_renderer, 0xff, 0xff ,0xff, 0xff);

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
		// we'll see if this function is needed
		set_texture_filtering();

		// Not using ttf for mouse events so I switched the function
		success = create_basic_window_via_texture(success, "Mouse Events");
	}
	return success;
}

void close_basic_window_surface()
{
	// Free loaded image
	SDL_DestroyTexture(g_p_texture);
	g_p_texture = nullptr;

	// Destory Window
	SDL_DestroyRenderer(g_p_renderer);
	SDL_DestroyWindow(g_p_window);

	g_p_window = nullptr;
	g_p_renderer = nullptr;

	// Quit SDL subsystems
	IMG_Quit();
	SDL_Quit();
	return;
}

void close_basic_window_texture()
{
	// Free loaded images
	SDL_DestroyTexture(g_p_texture);
	g_p_texture = nullptr;

	// Destory window
	SDL_DestroyRenderer(g_p_renderer);
	SDL_DestroyWindow(g_p_window);
	g_p_renderer = nullptr;
	g_p_window = nullptr;

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
	SDL_DestroyRenderer(g_p_renderer);
	SDL_DestroyWindow(g_p_window);
	g_p_renderer = nullptr;
	g_p_window = nullptr;

	// Quit SDL subsystems
	IMG_Quit();
	SDL_Quit();
	return;
}

void close_sprite_sheets()
{
	// Free loaded images
	g_sprite_sheet_texture.free_texture();

	// Destroy window
	SDL_DestroyRenderer(g_p_renderer);
	SDL_DestroyWindow(g_p_window);
	g_p_renderer = nullptr;
	g_p_window = nullptr;

	// Quit SDL subsystems
	IMG_Quit();
	SDL_Quit();
	return;
}

void close_arrow()
{
	// Free loaded images
	g_arrow_texture.free_texture();

	// Destroy window
	SDL_DestroyRenderer(g_p_renderer);
	SDL_DestroyWindow(g_p_window);
	g_p_renderer = nullptr;
	g_p_window = nullptr;

	// Quit SDL subsystems
	IMG_Quit();
	SDL_Quit();
	return;
}

#if defined(SDL_TTF_MAJOR_VERSION)
void close_fonts()
{
	// Free loaded images
	g_text_texture.free_texture();

	// Free global font
	TTF_CloseFont(g_p_font);
	g_p_font = nullptr;

	// Destroy window
	SDL_DestroyRenderer(g_p_renderer);
	SDL_DestroyWindow(g_p_window);
	g_p_renderer = nullptr;
	g_p_window = nullptr;

	// Quit SDL subsystems
	TTF_Quit();
	IMG_Quit();
	SDL_Quit();
	return;
}
#endif

void close_buttons()
{
	// Free loaded textures
	g_button_sprite_sheet_texture.free_texture();

	// Destroy window
	SDL_DestroyRenderer(g_p_renderer);
	SDL_DestroyWindow(g_p_window);
	g_p_renderer = nullptr;
	g_p_window = nullptr;

	// Quit SDL subsystems
	IMG_Quit();
	SDL_Quit();
	return;
}

void close_my_window()
{
	// close sprite sheet stuff
	close_buttons();
	return;
}

void display_single_color_screen()
{
	// Dont forget to deallocate g_p_renderer when screen is closed
	SDL_SetRenderDrawColor(g_p_renderer, 0xdd, 0xff, 0xff, 0xff);
	SDL_RenderClear(g_p_renderer);
	
	// Update screen
	SDL_RenderPresent(g_p_renderer);

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
	SDL_RenderSetViewport(g_p_renderer, &topLeftViewport);

	// Render png texture to screen
	SDL_RenderCopy(g_p_renderer, g_p_texture, nullptr, nullptr);

	// Top right viewport
	SDL_Rect topRightViewport;
	topRightViewport.x = SCREEN_WIDTH / 2;
	topRightViewport.y = 0;
	topRightViewport.w = SCREEN_WIDTH / 2;
	topRightViewport.h = SCREEN_HEIGHT / 2;
	SDL_RenderSetViewport(g_p_renderer, &topRightViewport);

	// Render png texture to screen
	SDL_RenderCopy(g_p_renderer, g_p_texture, nullptr, nullptr);

	// bottom viewport
	SDL_Rect bottomViewport;
	bottomViewport.x = 0;
	bottomViewport.y = SCREEN_HEIGHT / 2;
	bottomViewport.w = SCREEN_WIDTH;
	bottomViewport.h = SCREEN_HEIGHT / 2;
	SDL_RenderSetViewport(g_p_renderer, &bottomViewport);

	// Render png texture to screen
	SDL_RenderCopy(g_p_renderer, g_p_texture, nullptr, nullptr);

	// Update the screen
	SDL_RenderPresent(g_p_renderer);
	return;
}

void display_basic_non_scaled_surface_image()
{
	// Apply the PNG Image
	SDL_BlitSurface(g_p_png_surface, nullptr, g_p_screen_surface, nullptr);

	// Update the surface
	SDL_UpdateWindowSurface(g_p_window);
	return;
}

void display_basic_scaled_texture_image()
{
	// Clear screen
	SDL_RenderClear(g_p_renderer);

	// Render texture to screen
	SDL_RenderCopy(g_p_renderer, g_p_texture, nullptr, nullptr);

	// Update screen
	SDL_RenderPresent(g_p_renderer);
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
	SDL_BlitScaled(g_p_current_surface, nullptr, g_p_screen_surface, &stretch_rect);

	// Update the surface
	SDL_UpdateWindowSurface(g_p_window);

	// Clear Screen
	SDL_RenderClear(g_p_renderer);

	// Render texture to screen
	SDL_RenderCopy(g_p_renderer, g_p_texture, nullptr, nullptr);

	// Update screen
	SDL_RenderPresent(g_p_renderer);
	return;
}

void display_quads_and_lines()
{
	// Render red filled quad
	SDL_Rect fillRect = {SCREEN_WIDTH / 4, SCREEN_HEIGHT / 4, SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2};
	// Red hex colors (r,g,b,a)
	SDL_SetRenderDrawColor(g_p_renderer, 0xff, 0x00, 0x00, 0xff);
	SDL_RenderFillRect(g_p_renderer, &fillRect);

	// Render green outlined quad
	SDL_Rect outlineRect = {SCREEN_WIDTH / 6, SCREEN_HEIGHT / 6, SCREEN_WIDTH * 2 / 3, SCREEN_HEIGHT * 2 / 3};
	// Green hex colors (r,g,b,a)
	SDL_SetRenderDrawColor(g_p_renderer, 0x00, 0xff, 0x00, 0xff);
	SDL_RenderDrawRect(g_p_renderer, &outlineRect);

	// Render blue horizontal line
	SDL_SetRenderDrawColor(g_p_renderer, 0x00, 0x00, 0xff, 0xff);
	SDL_RenderDrawLine(g_p_renderer, 0, SCREEN_HEIGHT / 2, SCREEN_WIDTH, SCREEN_HEIGHT / 2);

	// Draw vertical line of yellow dots
	SDL_SetRenderDrawColor(g_p_renderer, 0xff, 0xff, 0x00, 0xff);
	for(int i = 0; i < SCREEN_HEIGHT; i+=4)
	{
		SDL_RenderDrawPoint(g_p_renderer, SCREEN_WIDTH / 2, i);
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
	// Clear Screen, whats going on with the g_p_renderer
	SDL_SetRenderDrawColor(g_p_renderer, 0xff, 0xff, 0xff, 0xff);
	SDL_RenderClear(g_p_renderer);

	// Render top left sprite
	g_sprite_sheet_texture.render(0, 0, &g_sprite_clips[0]);

	// Render top right sprite
	g_sprite_sheet_texture.render(SCREEN_WIDTH - g_sprite_clips[1].w, 0, &g_sprite_clips[1]);

	// Render bottom left sprite
	g_sprite_sheet_texture.render(0, SCREEN_HEIGHT - g_sprite_clips[2].h, &g_sprite_clips[2]);

	// Render bottom right sprite
	g_sprite_sheet_texture.render(SCREEN_WIDTH - g_sprite_clips[3].w, SCREEN_HEIGHT - g_sprite_clips[3].h, &g_sprite_clips[3]);

	// Update the screen
	SDL_RenderPresent(g_p_renderer);
	return;
}


void display_color_modulation()
{
	// Clear screen, set it white
	SDL_SetRenderDrawColor(g_p_renderer, 0xff, 0xff, 0xff, 0xff);
	SDL_RenderClear(g_p_renderer);

	// Modulate and render texture
	g_modulated_texture.set_color(g_main_color_set.red, g_main_color_set.green, g_main_color_set.blue);
	g_modulated_texture.render(0, 0);

	// Update screen
	SDL_RenderPresent(g_p_renderer);
	return;
}

void display_alpha_blending()
{
	// Clear screen
	SDL_SetRenderDrawColor(g_p_renderer, 0xff, 0xff, 0xff, 0xff);
	SDL_RenderClear(g_p_renderer);

	// Render background
	g_background_texture.render(0, 0);

	// Render front blended
	g_modulated_texture.set_alpha(g_alpha_value);
	g_modulated_texture.render(0, 0);

	// Update screen
	SDL_RenderPresent(g_p_renderer);
	return;
}

void display_animated_sprites()
{
	// Clear screen
	SDL_SetRenderDrawColor(g_p_renderer, 0xff, 0xff, 0xff, 0xff);
	SDL_RenderClear(g_p_renderer);

	// Render current frame
	SDL_Rect *current_clip = &g_sprite_clips[g_animation_frame / 4];
	g_sprite_sheet_texture.render((SCREEN_WIDTH - current_clip->w) / 2, (SCREEN_HEIGHT - current_clip->h) / 2, current_clip);

	// Update screen
	SDL_RenderPresent(g_p_renderer);

	// Go to next frame
	++g_animation_frame;

	// Cycle animation
	if(g_animation_frame / 4 >= WALKING_ANIMATION_FRAMES)
	{
		g_animation_frame = 0;
	}
	return;
}

void display_rotation_and_flipping()
{
	// Clear screen
	SDL_SetRenderDrawColor(g_p_renderer, 0xff, 0xff, 0xff, 0xff);
	SDL_RenderClear(g_p_renderer);

	// Render arrow
	g_arrow_texture.render((SCREEN_WIDTH - g_arrow_texture.get_width()) / 2, (SCREEN_HEIGHT - g_arrow_texture.get_height()) / 2, nullptr, g_degrees, nullptr,
			g_flip_type);
	
	// Update screen
	SDL_RenderPresent(g_p_renderer);
	return;
}

#if defined(SDL_TTF_MAJOR_VERSION)
void display_font()
{
	// Set screen white
	SDL_SetRenderDrawColor(g_p_renderer, 0xff, 0xff, 0xff, 0xff);

	// Clear screen
	SDL_RenderClear(g_p_renderer);

	// Render current frame
	g_text_texture.render((SCREEN_WIDTH - g_text_texture.get_width()) / 2,(SCREEN_HEIGHT - g_text_texture.get_height()) / 2);

	// Update screen
	SDL_RenderPresent(g_p_renderer);
	return;
}
#endif

void display_buttons()
{
	// This for now will just show a blank white screen
	// Set screen white
	SDL_SetRenderDrawColor(g_p_renderer, 0xff, 0xff, 0xff, 0xff);

	// Clear screen
	SDL_RenderClear(g_p_renderer);

	// Update screen
	SDL_RenderPresent(g_p_renderer);
	return;
}

bool main_loop(bool quit, SDL_Event &r_e)
{
	// *** KEYBOARD DRIVEN EVENTS *** //
	// Handle events on queue
	while(SDL_PollEvent(&r_e) != 0)
	{	
		// User requests quit
		if(r_e.type == SDL_QUIT)
		{
			quit = true;
		}
		// Handles events for button press downs
		else if(r_e.type == SDL_KEYDOWN)
		{
			// just prints q for logging purposes
			handle_key_press_output_q(r_e);
		}
	}
	// *** DISPLAY RELATED CODE *** //
	display_buttons();
	return quit;
}


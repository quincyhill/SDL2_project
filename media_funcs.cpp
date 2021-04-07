#include "media_funcs.hpp" 
#include "window_logic.hpp"
#include "key_presses.hpp"
#include "L_Texture.hpp"

SDL_Texture *g_texture = nullptr;

SDL_Renderer *g_renderer = nullptr;

bool load_sprite_data(bool success)
{
	// Load sprite sheet texture
	if(!g_sprite_sheet_texture.load_from_file("./assets/img/spritesheet.png"))
	{
		printf("Failed to load sprite sheet texture!\n");
		success = false;
	}
	else
	{
		// Set top left sprite
		g_sprite_clips[0].x = 0;
		g_sprite_clips[0].y = 0;
		g_sprite_clips[0].w = 180;
		g_sprite_clips[0].h = 180;

		// Set top right sprite
		g_sprite_clips[1].x = 180;
		g_sprite_clips[1].y = 0;
		g_sprite_clips[1].w = 180;
		g_sprite_clips[1].h = 180;

		// Set bottom left sprite
		g_sprite_clips[2].x = 0;
		g_sprite_clips[2].y = 180;
		g_sprite_clips[2].w = 180;
		g_sprite_clips[2].h = 180;

		// Set bottom right sprite
		g_sprite_clips[3].x = 180;
		g_sprite_clips[3].y = 180;
		g_sprite_clips[3].w = 180;
		g_sprite_clips[3].h = 180;
	}
	return success;
}

bool load_character_and_background(bool success)
{
	// Load Foo' texture
	if(!g_character_texture.load_from_file("./assets/img/basiccharacter.png"))
	{
		printf("Failed to load Basic Character texture image!\n");
		success = false;
	}
	else
	{
		printf("Chracter is loaded\n");
	}

	// Load Background texture
	if(!g_background_texture.load_from_file("./assets/img/sunnybackground.png"))
	{
		printf("Failed to load Background texture image!\n");
		success = false;
	}
	else
	{
		printf("Background is loaded\n");
	}
	return success;
}

bool load_viewport_data(bool success)
{
	// viewport texture
	g_texture = load_texture("./assets/img/viewport.png");
	if(g_texture == nullptr)
	{
		printf("Failed to load png image!\n");
		success = false;
	}
	return success;
}

bool load_bitmap_image(bool success, std::string img_path)
{
	// Load splash image
	g_hello_world = SDL_LoadBMP(img_path.c_str());
	if(g_hello_world == nullptr)
	{
		printf("Unable to load image %s! SDL_Error: %s\n", img_path.c_str(), SDL_GetError());
		success = false;
	}
	return success;
}

bool load_media()
{
	// Loading success flag
	bool success = true;

	// This case im loading bitmap hello world
	success = load_bitmap_image(success, "./assets/img/helloworld.bmp");

	return success;
}


SDL_Texture *load_texture(std::string img_path)
{
	// The final texture
	SDL_Texture *new_texture = nullptr;

	// Load image at specified path
	SDL_Surface *loaded_surface = IMG_Load(img_path.c_str());

	if(loaded_surface == nullptr)
	{
		printf("Unable to load image %s! SDL_image Error: %s\n", img_path.c_str(), IMG_GetError());
	}
	else
	{
		// Create texture from surface pixels
		new_texture = SDL_CreateTextureFromSurface(g_renderer, loaded_surface);

		if(new_texture == nullptr)
		{
			printf("Unable to create texture from %s! SDL_Error: %s\n", img_path.c_str(), SDL_GetError());
		}

		// Get rid of old loaded surface
		SDL_FreeSurface(loaded_surface);
	}

	return new_texture;
}



SDL_Surface *load_surface(std::string img_path)
{
	// the final optimized image
	SDL_Surface *optimized_surface = nullptr;

	// The final texture
	SDL_Texture *new_texture = nullptr;

	// // Load image at specified path for bmp
	// sDL_Surface *loaded_surface = SDL_LoadBMP(path.c_str());

	// Load image at specified path for texture
	SDL_Surface *loaded_surface = IMG_Load(img_path.c_str());

	if(loaded_surface == nullptr)
	{
		printf("Unable to load image %s! SDL Error: %s\n", img_path.c_str(), SDL_GetError());
	}
	else
	{
		// // Convert surface to screen format
		// optimized_surface = SDL_ConvertSurface(loaded_surface, gScreenSurface->format, 0);

		// Creae texture from surface pixels
		new_texture = SDL_CreateTextureFromSurface(g_renderer, loaded_surface);
		// if(optimized_surface == nullptr)
		// {
		// 	printf("Unable to optimize image %s! SDL Error: %s\n", path.c_str(), SDL_GetError());
		// }

		if (new_texture == nullptr)
		{
			printf("Unable to create texture from %s! SDL_Error: %s\n", img_path.c_str(), SDL_GetError());
		}

		// Get rid of old loaded surface
		SDL_FreeSurface(loaded_surface);
	}
	return optimized_surface;
}

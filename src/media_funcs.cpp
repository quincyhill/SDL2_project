#include "../include/media_funcs.hpp" 
#include "../include/window_logic.hpp"
#include "../include/key_presses.hpp"
#include "../include/L_Texture.hpp"

SDL_Texture *g_p_texture = nullptr;

SDL_Renderer *g_p_renderer = nullptr;

SDL_Surface *g_p_png_surface = nullptr;

bool load_sprite_data(bool success)
{
	// Load sprite sheet texture
	if(!g_sprite_sheet_texture.load_from_file("./assets/img/spritesheet.png"))
	{
		std::printf("Failed to load sprite sheet texture!\n");
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
		std::printf("Failed to load Basic Character texture image!\n");
		success = false;
	}
	// Load Background texture
	if(!g_background_texture.load_from_file("./assets/img/sunnybackground.png"))
	{
		std::printf("Failed to load Background texture image!\n");
		success = false;
	}
	return success;
}

SDL_Surface *p_load_surface(std::string img_path)
{
	// Final surface
	SDL_Surface *p_optimized_surface = nullptr;

	// Load image at specified path
	SDL_Surface *p_loaded_surface = IMG_Load(img_path.c_str());
	if(p_loaded_surface == nullptr)
	{
		std::printf("Unable to load image: %s! SDL_Error: %s\n", img_path.c_str(), SDL_GetError());
	}
	else
	{
		// Convert surface to screen format
		p_optimized_surface = SDL_ConvertSurface(p_loaded_surface, g_p_screen_surface->format, 0);
		if(p_optimized_surface == nullptr)
		{
			std::printf("Unable to optimize image: %s! SDL_Error: %s\n", img_path.c_str(), SDL_GetError());
		}
		
		// Get rid of old loaded surace
		SDL_FreeSurface(p_loaded_surface);
	}
	return p_optimized_surface;
}

SDL_Texture *load_texture(std::string img_path)
{
	// The final texture
	SDL_Texture *p_new_texture = nullptr;

	// Load image at specified path
	SDL_Surface *p_loaded_surface = IMG_Load(img_path.c_str());

	if(p_loaded_surface == nullptr)
	{
		std::printf("Unable to load image %s! SDL_image Error: %s\n", img_path.c_str(), IMG_GetError());
	}
	else
	{
		// Create texture from surface pixels
		p_new_texture = SDL_CreateTextureFromSurface(g_p_renderer, p_loaded_surface);

		if(p_new_texture == nullptr)
		{
			std::printf("Unable to create texture from %s! SDL_Error: %s\n", img_path.c_str(), SDL_GetError());
		}

		// Get rid of old loaded surface
		SDL_FreeSurface(p_loaded_surface);
	}

	return p_new_texture;
}

bool load_viewport_data(bool success)
{
	// viewport texture
	g_p_texture = load_texture("./assets/img/viewport.png");
	if(g_p_texture == nullptr)
	{
		std::printf("Failed to load png image!\n");
		success = false;
	}
	return success;
}

bool load_alpha_blending_p_textures(bool success)
{
	// Load front alpha texture
	if(!g_modulated_texture.load_from_file("./assets/img/fadeout.png"))
	{
		std::printf("Failed to load front texture!\n");
		success = false;
	}
	else
	{
		// Set standard alpha bleeding
		g_modulated_texture.set_blend_mode(SDL_BLENDMODE_BLEND);
	}

	// Load background texture
	if(!g_background_texture.load_from_file("./assets/img/fadein.png"))
	{
		std::printf("Failed to background texture!\n");
		success = false;
	}

	return success;
}

bool load_animated_sprite_texture(bool success)
{
	// Load sprite sheet texture
	if(!g_sprite_sheet_texture.load_from_file("./assets/img/characterwalkspritesheet.png"))
	{
		std::printf("Failed to load walking animation texture!\n");
		success = false;
	}
	else
	{
		// set movement clips
		for(int i = 0; i < 4; i++)
		{
			g_sprite_clips[i].x = 100 * i;
			g_sprite_clips[i].y = 0;
			g_sprite_clips[i].w = 100;
			g_sprite_clips[i].h = 300;
		}
	}
	return success;
}

bool load_arrow_texture(bool success)
{
	// Load arrow texture
	if(!g_arrow_texture.load_from_file("./assets/img/arrow.png"))
	{
		std::printf("Failed to load arrow texture!\n");
		success = false;
	}
	return success;
}

#if defined(SDL_TTF_MAJOR_VERSION)
bool load_font_texture(bool success)
{
	// Open the font
	g_p_font = TTF_OpenFont("./assets/fonts/Lobster-Regular.ttf", 28);
	if(g_p_font == nullptr)
	{
		std::printf("Failed to load Lobster-Regular font! SDL_ttf Error: %s\n", TTF_GetError());
		success = false;
	}
	else
	{
		// Render text
		SDL_Color text_color = {0x00, 0x00, 0x00};
		if(!g_text_texture.load_from_rendered_text("The quick brown fox jumps over the lazy dog", text_color))
		{
			std::printf("Failed to render text texture!\n");
			success = false;
		}
	}
	return success;
}
#endif

bool load_mouse_button_texture(bool success)
{
	// Load all 4 mouse textures
	if(!g_button_sprite_sheet_texture.load_from_file("./assets/img/mouse_clicks/mousemovedout.png"))
	{
		std::printf("Failed to load mouse move out texture!\n");
		success = false;
	}
	else
	{
		std::printf("loaded mouse move out texture!");
	}

	if(!g_button_sprite_sheet_texture.load_from_file("./assets/img/mouse_clicks/mouseover.png"))
	{
		std::printf("Failed to load mouse over texture!\n");
		success = false;
	}
	else
	{
		std::printf("loaded mouse move over texture!");
	}

	if(!g_button_sprite_sheet_texture.load_from_file("./assets/img/mouse_clicks/mouseclickedon.png"))
	{
		std::printf("Failed to load mouse clicked on texture!\n");
		success = false;
	}
	else
	{
		std::printf("loaded mouse clicked on texture!");
	}

	if(!g_button_sprite_sheet_texture.load_from_file("./assets/img/mouse_clicks/mousereleasedon.png"))
	{
		std::printf("Failed to load mouse released texture!\n");
		success = false;
	}
	else
	{
		std::printf("loaded mouse releaded on texture!");
	}
	return success;
}

bool load_media()
{
	// Loading success flag
	bool success = true;

	// Load images for the mouse buttons
	success = load_mouse_button_texture(success);

	return success;
}



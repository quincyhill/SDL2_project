#include "L_Texture.hpp"
#include "media_funcs.hpp"
#include "window_logic.hpp"

L_Texture::L_Texture()
{
	// Constructor
	// make sure to clear out the pointer when done
	m_p_texture = nullptr;
	m_width = 0;
	m_height = 0;
}

L_Texture::~L_Texture()
{
	// Destructor
	free_texture();
}

bool L_Texture::load_from_file(std::string img_path)
{
	// Get rid of pre-existing texture
	free_texture();

	// The final texture
	SDL_Texture *p_new_texture = nullptr;

	// Load image at specified path
	SDL_Surface *p_loaded_surface = IMG_Load(img_path.c_str());
	if(p_loaded_surface == nullptr)
	{
		printf("Unable to load image %s! SDL_Error: %s\n", img_path.c_str(), IMG_GetError());
	}
	else
	{
		// Color key image
		SDL_SetColorKey(p_loaded_surface, SDL_TRUE, SDL_MapRGB(p_loaded_surface->format, 0, 0xff, 0xff));

		// Create texture from surface pixels
		p_new_texture = SDL_CreateTextureFromSurface(g_p_renderer, p_loaded_surface);
		if(p_new_texture == nullptr)
		{
			printf("Unable to create texture from %s! SDL_Error: %s\n", img_path.c_str(), SDL_GetError());
		}
		else
		{
			// Get image dimensions
			m_width = p_loaded_surface->w;
			m_height = p_loaded_surface->h;
		}

		// Get rid of old loaded surface
		SDL_FreeSurface(p_loaded_surface);
	}
	// Set m_p_texture to point to this new texture
	m_p_texture = p_new_texture;

	// prevent dangling pointer?
	p_new_texture = nullptr;

	// returns t / f checking if m_p_texture is null or not
	return m_p_texture != nullptr;
}

#if defined(SDL_TTF_MAJOR_VERSION)
bool L_Texture::load_from_rendered_text(std::string texture_text, SDL_Color text_color)
{
	// Get rid of existing texture
	free_texture();

	// Render text surface
	SDL_Surface *text_surface = TTF_RenderText_Solid(g_p_font, texture_text.c_str(), text_color);
	if(text_surface == nullptr)
	{
		printf("Unable to render text surface! SDL_ttf Error: %s\n", TTF_GetError());
	}
	else
	{
		// Create texture from surface pixels
		m_p_texture = SDL_CreateTextureFromSurface(g_p_renderer, text_surface);
		if(m_p_texture == nullptr)
		{
			printf("Unable to create texture from rendered text! SDL Error: %s\n", SDL_GetError());
		}
		else
		{
			// Get image dimensions
			m_width = text_surface->w;
			m_height = text_surface->h;
		}

		// Get rid of old surface
		SDL_FreeSurface(text_surface);
	}

	// Return success
	return m_p_texture != nullptr;
}
#endif

void L_Texture::free_texture()
{
	// Free texture if it exists
	if(m_p_texture != nullptr)
	{
		SDL_DestroyTexture(m_p_texture);

		// Set back to init state
		m_p_texture = nullptr;
		m_width = 0;
		m_height = 0;
	}
	return;
}

void L_Texture::render(int x, int y, SDL_Rect *clip, double angle, SDL_Point *center, SDL_RendererFlip flip)
{
	// Set rendering space and render to screen
	SDL_Rect render_quad = {x, y, m_width, m_height};

	// Set clip rendering dimensions
	if(clip != nullptr)
	{
		render_quad.w = clip->w;
		render_quad.h = clip->h;
	}

	// Render to screen
	SDL_RenderCopyEx(g_p_renderer, m_p_texture, clip, &render_quad, angle, center, flip);
	return;
}

void L_Texture::set_color(Uint8 red, Uint8 green, Uint8 blue)
{
	// Modulate texture
	SDL_SetTextureColorMod(m_p_texture, red, green, blue);
	return;
}

void L_Texture::set_blend_mode(SDL_BlendMode blending)
{
	// Set blending function
	SDL_SetTextureBlendMode(m_p_texture, blending);
	return;
}

void L_Texture::set_alpha(Uint8 alpha)
{
	// Modulate texture alpha
	SDL_SetTextureAlphaMod(m_p_texture, alpha);
	return;
}

int L_Texture::get_width()
{
	return this->m_width;
}

int L_Texture::get_height()
{
	return this->m_height;
}

L_Texture g_character_texture;
L_Texture g_background_texture;
SDL_Rect g_sprite_clips[4];
L_Texture g_sprite_sheet_texture;
L_Texture g_modulated_texture;
L_Texture g_arrow_texture;
L_Texture g_text_texture;
TTF_Font *g_p_font = nullptr;
L_Texture g_button_sprite_sheet_texture;

#include "L_Texture.hpp"
#include "media_funcs.hpp"
#include "window_logic.hpp"

L_Texture::L_Texture()
{
	// Constructor
	// make sure to clear out the pointer when done
	m_texture = nullptr;
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
	SDL_Texture *newTexture = nullptr;

	// Load image at specified path
	SDL_Surface *loadedSurface = IMG_Load(img_path.c_str());
	if(loadedSurface == nullptr)
	{
		printf("Unable to load image %s! SDL_Error: %s\n", img_path.c_str(), IMG_GetError());
	}
	else
	{
		// Color key image
		SDL_SetColorKey(loadedSurface, SDL_TRUE, SDL_MapRGB(loadedSurface->format, 0, 0xff, 0xff));

		// Create texture from surface pixels
		newTexture = SDL_CreateTextureFromSurface(g_renderer, loadedSurface);
		if(newTexture == nullptr)
		{
			printf("Unable to create texture from %s! SDL_Error: %s\n", img_path.c_str(), SDL_GetError());
		}
		else
		{
			// Get image dimensions
			m_width = loadedSurface->w;
			m_height = loadedSurface->h;
		}

		// Get rid of old loaded surface
		SDL_FreeSurface(loadedSurface);
	}

	// Where do i set newTexture back to null? potential bug here
	
	// Set m_texture to point to this new texture
	m_texture = newTexture;

	// returns t / f checking if m_texture is null or not
	return m_texture != nullptr;
}

void L_Texture::free_texture()
{
	// Free texture if it exists
	if(m_texture != nullptr)
	{
		SDL_DestroyTexture(m_texture);

		// Set back to init state
		m_texture = nullptr;
		m_width = 0;
		m_height = 0;
	}
}

void L_Texture::render(int x, int y, SDL_Rect *clip)
{
	// Set rendering space and render to screen
	SDL_Rect renderQuad = {x, y, m_width, m_height};

	// Set clip rendering dimensions
	if(clip != nullptr)
	{
		renderQuad.w = clip->w;
		renderQuad.h = clip->h;
	}

	// The source rect, idk if this fixes anything tbh, it didn't change anything when dimensions matched, not being used atm
	SDL_Rect mainSrcRect = {0, 0, 360, 360};

	// Render to screen
	SDL_RenderCopy(g_renderer, m_texture, nullptr, &renderQuad);
}

void L_Texture::set_color(Uint8 red, Uint8 green, Uint8 blue)
{
	// Modulate texture
	SDL_SetTextureColorMod(m_texture, red, green, blue);
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

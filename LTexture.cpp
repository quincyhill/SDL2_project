#include "LTexture.hpp"
#include "media_funcs.hpp"
#include "window_logic.hpp"

LTexture::LTexture()
{
	// Constructor
	m_texture = nullptr;
	m_width = 0;
	m_height = 0;
}

LTexture::~LTexture()
{
	// Destructor
	freeTexture();
}

bool LTexture::loadFromFile(std::string path)
{
	// Get rid fo preexisting texture
	freeTexture();

	// The final texture
	SDL_Texture *newTexture = nullptr;

	// Load image at specified path
	SDL_Surface *loadedSurface = IMG_Load(path.c_str());
	if(loadedSurface == nullptr)
	{
		printf("Unable to load image %s! SDL_Error: %s\n", path.c_str(), IMG_GetError());
	}
	else
	{
		// Color key image
		SDL_SetColorKey(loadedSurface, SDL_TRUE, SDL_MapRGB(loadedSurface->format, 0, 0xff, 0xff));

		// Create texture from surface pixels
		newTexture = SDL_CreateTextureFromSurface(gRenderer, loadedSurface);
		if(newTexture == nullptr)
		{
			printf("Unable to create texture from %s! SDL_Error: %s\n", path.c_str(), SDL_GetError());
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
	
	// Return success
	m_texture = newTexture;
	return m_texture != nullptr;
}

void LTexture::freeTexture()
{
	// Free texture if it exists
	if(m_texture != nullptr)
	{
		SDL_DestroyTexture(m_texture);
		m_texture = nullptr;
		m_width = 0;
		m_height = 0;
	}
}

void LTexture::render(int x, int y)
{
	// Set rendering space and render to screen
	SDL_Rect renderQuad = {x, y, m_width, m_height};
	SDL_RenderCopy(gRenderer, m_texture, nullptr, &renderQuad);
}


int LTexture::getWidth()
{
	return this->m_width;
}

int LTexture::getHeight()
{
	return this->m_height;
}

LTexture gCharacterTexture;
LTexture gBackgroundTexture;

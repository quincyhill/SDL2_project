#include "LTexture.hpp"
#include "media_funcs.hpp"
#include "window_logic.hpp"

LTexture::LTexture()
{
	// Constructor
	// make sure to clear out the pointer when done
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
	// Get rid of pre-existing texture
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

	// Where do i set newTexture back to null? potential bug here
	
	// Set m_texture to point to this new texture
	m_texture = newTexture;

	// returns t / f checking if m_texture is null or not
	return m_texture != nullptr;
}

void LTexture::freeTexture()
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

void LTexture::render(int x, int y, SDL_Rect *clip)
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
	SDL_RenderCopy(gRenderer, m_texture, nullptr, &renderQuad);
}

void LTexture::setColor(Uint8 red, Uint8 green, Uint8 blue)
{
	// Modulate texture
	SDL_SetTextureColorMod(m_texture, red, green, blue);
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
SDL_Rect gSpriteClips[4];
LTexture gSpriteSheetTexture;
LTexture gModulatedTexture;

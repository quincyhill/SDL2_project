#ifndef LTEXTURE_HP
#define LTEXTURE_HPP

#include <string>
#include <SDL2/SDL.h>

class LTexture
{
public:
	// Initializes variables (aka constructor)
	LTexture();

	// Deallocates mem (aka destructor)
	~LTexture();

	// Loads image at specified path
	bool loadFromFile(std::string path);

	// Deallocates texture
	void freeTexture();

	// Set color modulation
	void setColor(Uint8 red, Uint8 green, Uint8 blue);

	// Render texture at given point
	void render(int x, int y, SDL_Rect *clip = nullptr);

	// Gets image dimensions
	int getWidth();
	int getHeight();

private:
	// The actual hardware texture
	SDL_Texture *m_texture;

	// Image dimensions
	int m_width;
	int m_height;
};

// This is the character texture
extern LTexture gCharacterTexture;

// This is the background texture
extern LTexture gBackgroundTexture;

// Sprite clip 
extern SDL_Rect gSpriteClips[4];

// Main sheet texture
extern LTexture gSpriteSheetTexture;

// Color texture modulated by inputs
extern LTexture gModulatedTexture;

#endif

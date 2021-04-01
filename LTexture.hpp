#ifndef LTEXTURE_HPP
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

		// Render texture at given point
		void render(int x, int y);

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

#endif

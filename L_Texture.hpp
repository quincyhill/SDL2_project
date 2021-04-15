#ifndef L_TEXTURE_HP
#define L_TEXTURE_HPP

#include <string>
#include <SDL2/SDL.h>

class L_Texture
{
	public:
		// Initializes variables (aka constructor)
		L_Texture();
	
		// Deallocates mem (aka destructor)
		~L_Texture();
	
		// Loads image at specified path
		bool load_from_file(std::string img_path);
	
		// Deallocates texture
		void free_texture();
	
		// Set color modulation
		void set_color(Uint8 red, Uint8 green, Uint8 blue);
	
		// Render texture at given point
		void render(int x, int y, SDL_Rect *clip = nullptr);
	
		// Gets image dimensions
		int get_width();
		int get_height();
	
	private:
		// The actual hardware texture
		SDL_Texture *m_texture;
	
		// Image dimensions
		int m_width;
		int m_height;
};

// This is the character texture
extern L_Texture g_character_texture;

// This is the background texture
extern L_Texture g_background_texture;

// Sprite clip 
extern SDL_Rect g_sprite_clips[4];

// Main sheet texture
extern L_Texture g_sprite_sheet_texture;

// Color texture modulated by inputs
extern L_Texture g_modulated_texture;

#endif

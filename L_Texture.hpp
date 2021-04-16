#ifndef L_TEXTURE_HP
#define L_TEXTURE_HPP

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_image.h>
#include <stdio.h>
#include <string>
#include <cmath>

class L_Texture
{
	public:
		// Initializes variables (aka constructor)
		L_Texture();
	
		// Deallocates mem (aka destructor)
		~L_Texture();
	
		// Loads image at specified path
		bool load_from_file(std::string img_path);

		// Loads image from font string
		bool load_from_rendered_text(std::string texture_text, SDL_Color text_color);
	
		// Deallocates texture
		void free_texture();
	
		// Set color modulation
		void set_color(Uint8 red, Uint8 green, Uint8 blue);

		// Set blending
		void set_blend_mode(SDL_BlendMode blending);

		// Set alpha modulation
		void set_alpha(Uint8 alpha);
	
		// Render texture at given point
		void render(int x, int y, SDL_Rect *clip = nullptr, double angle = 0.0, SDL_Point *center = nullptr, SDL_RendererFlip flip = SDL_FLIP_NONE);
	
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

// Walking animation
const int WALKING_ANIMATION_FRAMES = 4;

// This is the character texture
extern L_Texture g_character_texture;

// This is the background texture
extern L_Texture g_background_texture;

// Sprite clip 
extern SDL_Rect g_sprite_clips[WALKING_ANIMATION_FRAMES];

// Main sheet texture
extern L_Texture g_sprite_sheet_texture;

// Color texture modulated by inputs
extern L_Texture g_modulated_texture;

// Arrow texture
extern L_Texture g_arrow_texture;

// Globally used font
extern TTF_Font *g_p_font;

// Rendered text texture
extern L_Texture g_text_texture;
#endif

#ifndef L_BUTTON_HPP
#define L_BUTTON_HPP
#include <SDL2/SDL.h>
// Button constants
extern const int BUTTON_WIDTH;
extern const int BUTTON_HEIGHT;
extern const int TOTAL_BUTTONS;

// enums
enum L_Button_Sprite
{
	BUTTON_SPRITE_MOUSE_OUT,
	BUTTON_SPRITE_MOUSE_OVER_MOTION,
	BUTTON_SPRITE_MOUSE_DOWN,
	BUTTON_SPRITE_MOUSE_UP,
	BUTTON_SPRITE_MOUSE_TOTAL,
};

class L_Button
{
	public:
		// Constructor for initializing stuff.
		L_Button();

		// Sets top left position
		void set_position(int x, int y);

		// Handles mouse event
		void handle_event(SDL_Event *p_e);

		// Shows button sprite
		void render();

	private:
		// Top left position
		SDL_Point m_position;

		// Currently used gloabl sprite
		L_Button_Sprite m_current_sprite;
};
#endif

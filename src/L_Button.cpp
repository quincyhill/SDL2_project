#include "../include/L_Button.hpp"
#include "../include/L_Texture.hpp"

// Button constants
const int BUTTON_WIDTH = 300;
const int BUTTON_HEIGHT = 200;
const int TOTAL_BUTTONS = 4;

L_Button::L_Button()
{
	m_position.x = 0;
	m_position.y = 0;
	m_current_sprite = BUTTON_SPRITE_MOUSE_OUT;
}

void L_Button::set_position(int x, int y)
{
	m_position.x = x;
	m_position.y = y;
}

void L_Button::handle_event(SDL_Event *p_e)
{
	// If mouse event happened
	if(p_e->type == SDL_MOUSEMOTION || p_e->type == SDL_MOUSEBUTTONDOWN || p_e->type == SDL_MOUSEBUTTONUP)
	{
		// Get mouse position
		int x, y;
		SDL_GetMouseState(&x, &y);

		// Check if mouse is in button
		bool inside = true;

		// Mouse is left of the button
		if(x < m_position.x)
		{
			inside = false;
		}
		// Mouse is right of the button
		else if(x > m_position.x + BUTTON_WIDTH)
		{
			inside = false;
		}
		// Mouse is above the button
		else if(y < m_position.y)
		{
			inside = false;
		}
		// Mouse is below the button
		else if(y > m_position.y + BUTTON_HEIGHT)
		{
			inside = false;
		}

		// Mouse is outside button
		if(!inside)
		{
			m_current_sprite = BUTTON_SPRITE_MOUSE_OUT;
		}
		// Mouse is inside button
		else
		{
			// Set mouse over sprite
			switch(p_e->type)
			{
				case SDL_MOUSEMOTION:
					m_current_sprite = BUTTON_SPRITE_MOUSE_OVER_MOTION;
					break;
				case SDL_MOUSEBUTTONDOWN:
					m_current_sprite = BUTTON_SPRITE_MOUSE_DOWN;
					break;
				case SDL_MOUSEBUTTONUP:
					m_current_sprite = BUTTON_SPRITE_MOUSE_UP;
					break;
			}
		}
	}
}

void L_Button::render()
{
	// Show current button sprite
	g_button_sprite_sheet_texture.render(m_position.x, m_position.y,&g_sprite_clips[m_current_sprite]);
}

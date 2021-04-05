#ifndef WINDOW_LOGIC_HPP
#define WINDOW_LOGIC_HPP

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <string>
#include <stdio.h>

/*
 * extern is used for variables and pointers functions are just the way they are
 */

struct TestColorSet
{
	Uint8 red;
	Uint8 green;
	Uint8 blue;
};

// These are the constants for screen sizes
extern const int SCREEN_WIDTH;
extern const int SCREEN_HEIGHT;

// The window we'll be rendering to
extern SDL_Window *gWindow;

// The surface contained by the window
extern SDL_Surface *gScreenSurface;

// The image we will load and show on the screen
extern SDL_Surface *gHelloWorld;

/*
 * Functions go here
 */

// Ininitialization flag responsible for setting up the window
bool init_my_window();

// Clears the window along with freeing memeory
void close_my_window();

// Main window loop, logic for every iteration goes here
bool main_loop(bool quit, TestColorSet &testColor_ref);

// Handle keypress switching, used if I have other things maps to different keys
void handleKeyPressSwitching(SDL_Event e);

// Hanle keypress for color moduation
void handleKeyPressColorModulation(SDL_Event e, TestColorSet &testColor_ref);

// Display simple white screen
void displaySingleColorScreen();

// Here is for displaying viewports
void displayViewportsToScreen();

// display some basic image
void displayBasicNonScaledImage();

// display scaled image
void displayBasicScaledImage();

// display screen with colors and lines
void displayQuadsAndLines();

// display sprite clips, this one needs some fixing
void displaySpriteClips();

// display character and background to screen, this one needs some fixing
void displayCharacterAndBackground();

// display sectioned screen with color moduation
void displayColorModulation(SDL_Event e, TestColorSet &testColor_ref);

#endif

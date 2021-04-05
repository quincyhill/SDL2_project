#include "window_logic.hpp"
#include "key_presses.hpp"
#include "media_funcs.hpp"
#include "LTexture.hpp"

// CONSTANTS
// 1280 x 720 for testing purposes for window size then eventual 1080p
const int SCREEN_WIDTH = 1280;
const int SCREEN_HEIGHT = 720;

SDL_Window *gWindow = nullptr;

SDL_Surface *gScreenSurface = nullptr;

SDL_Surface *gHelloWorld = nullptr;

bool init_my_window()
{
	bool success = true;

	// Initialize SDL
	if(SDL_Init(SDL_INIT_VIDEO) < 0)
	{
		printf("SDL could not initialize! SDL_Error: %s\n", SDL_GetError());
		success = false;
	}
	else
	{
		// Set texture filtering to linear
		if(!SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "1"))
		{
			printf("Warning: Linear texture filtering not enabled!");
		}

		// Create window
		gWindow = SDL_CreateWindow("Quincy's SDL Example", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);

		if(gWindow == nullptr)
		{
			printf("Window could not be created! SDL_Error: %s\n", SDL_GetError());
			success = false;
		}
		else
		{
			// Create renderer for window
			gRenderer = SDL_CreateRenderer(gWindow, -1, SDL_RENDERER_ACCELERATED);

			if(gRenderer == nullptr)
			{
				printf("Renderer could not be created! SDL_Error: %s\n",SDL_GetError());
				success = false;
			}
			else
			{
				// Initialize renderer color
				// 0xff is simply 255 in hexadecimal, so white in this case
				SDL_SetRenderDrawColor(gRenderer, 0xff, 0xff, 0xff, 0xff);

				// Initialize PNG loading
				int imgFlags = IMG_INIT_PNG;

				if(!(IMG_Init(imgFlags) & imgFlags))
				{
					printf("SDL_image could not initialize! SDL_image Error: %s\n", IMG_GetError());
					success = false;
				}
			}

			// // Get window surface
			// gScreenSurface = SDL_GetWindowSurface(gWindow);

			// // Fill the surface white
			// SDL_FillRect(screenSurface, nullptr, SDL_MapRGB(screenSurface->format, 0xFF, 0xFF, 0xFF));

			// Delay so that the color comes in, still some issue that it doesnt always colors in white temp "fix"
			// I saw someone do this youtube and ngl it seems kinda smart to do num/60 SDL_Delay(1000/60);

			// // Update the surface
			// SDL_UpdateWindowSurface(window);

			// // Wait two seconds
			// SDL_Delay(2000);
		}
	}

	return success;
}

void close_my_window()
{
	// Not using hello world no need to deallocate
	// // Deallocate surface
	// SDL_FreeSurface(gHelloWorld);
	// gHelloWorld = nullptr;
	// delete gHelloWorld;

	// Deallocate screenSurface
	SDL_FreeSurface(gScreenSurface);
	gScreenSurface = nullptr;

	// Free loaded image
	SDL_DestroyTexture(gTexture);
	gTexture = nullptr;

	// Destroy window 
	SDL_DestroyWindow(gWindow);
	// Destroy renderer
	SDL_DestroyRenderer(gRenderer);
	gRenderer = nullptr;
	gWindow = nullptr;

	// Quit SDL subsystems
	SDL_Quit();
	// Quit IMG subsystems
	IMG_Quit();
	
	/* This should be for Sprite stuff */
	// // Free loaded images
	// gSpriteSheetTexture.freeTexture();

	// // Destroy window
	// SDL_DestroyRenderer(gRenderer);
	// SDL_DestroyWindow(gWindow);
	// gRenderer = nullptr;
	// gWindow = nullptr;

	// // Quit SDL subsystems
	// IMG_Quit();
	// SDL_Quit();
}

void handleKeyPressSwitching(SDL_Event e)
{
	switch(e.key.keysym.sym)
	{
		case SDLK_UP:
			gCurrentSurface = gKeyPressSurfaces[KEY_PRESS_SURFACE_UP];
			break;

		case SDLK_DOWN:
			gCurrentSurface = gKeyPressSurfaces[KEY_PRESS_SURFACE_DOWN];
			break;

		case SDLK_LEFT:
			gCurrentSurface = gKeyPressSurfaces[KEY_PRESS_SURFACE_LEFT];
			break;

		case SDLK_RIGHT:
			gCurrentSurface = gKeyPressSurfaces[KEY_PRESS_SURFACE_RIGHT];
			break;

		default:
			gCurrentSurface = gKeyPressSurfaces[KEY_PRESS_SURFACE_DEFAULT];
			break;
	}

}

void displaySingleColorScreen()
{
	// Dont forget to deallocate gRenderer when screen is closed
	SDL_SetRenderDrawColor(gRenderer, 0xdd, 0xff, 0xff, 0xff);
	SDL_RenderClear(gRenderer);
	
	// Update screen
	SDL_RenderPresent(gRenderer);
	return;
}

void displayViewportsToScreen()
{
	// Top Left corner viewport
	SDL_Rect topLeftViewport;
	topLeftViewport.x = 0;
	topLeftViewport.y = 0;
	topLeftViewport.w = SCREEN_WIDTH / 2;
	topLeftViewport.h = SCREEN_HEIGHT / 2;
	SDL_RenderSetViewport(gRenderer, &topLeftViewport);

	// Render png texture to screen
	SDL_RenderCopy(gRenderer, gTexture, nullptr, nullptr);

	// Top right viewport
	SDL_Rect topRightViewport;
	topRightViewport.x = SCREEN_WIDTH / 2;
	topRightViewport.y = 0;
	topRightViewport.w = SCREEN_WIDTH / 2;
	topRightViewport.h = SCREEN_HEIGHT / 2;
	SDL_RenderSetViewport(gRenderer, &topRightViewport);

	// Render png texture to screen
	SDL_RenderCopy(gRenderer, gTexture, nullptr, nullptr);

	// bottom viewport
	SDL_Rect bottomViewport;
	bottomViewport.x = 0;
	bottomViewport.y = SCREEN_HEIGHT / 2;
	bottomViewport.w = SCREEN_WIDTH;
	bottomViewport.h = SCREEN_HEIGHT / 2;
	SDL_RenderSetViewport(gRenderer, &bottomViewport);

	// Render png texture to screen
	SDL_RenderCopy(gRenderer, gTexture, nullptr, nullptr);

	// Update the screen
	SDL_RenderPresent(gRenderer);
	return;
}

void displayBasicNonScaledImage()
{
	// Apply the image to screen
	SDL_BlitSurface(gCurrentSurface, nullptr, gScreenSurface, nullptr);
	SDL_UpdateWindowSurface(gWindow);
	return;
}

void displayBasicScaledImage()
{
	// Apply the stretched image
	SDL_Rect stretchRect;
	stretchRect.x = 0;
	stretchRect.y = 0;
	stretchRect.w = SCREEN_WIDTH;
	stretchRect.h = SCREEN_HEIGHT;
	SDL_BlitScaled(gCurrentSurface, nullptr, gScreenSurface, &stretchRect);

	// Update the surface
	SDL_UpdateWindowSurface(gWindow);

	// Clear Screen
	SDL_RenderClear(gRenderer);

	// Render texture to screen
	SDL_RenderCopy(gRenderer, gTexture, nullptr, nullptr);

	// Update screen
	SDL_RenderPresent(gRenderer);

	return;
}

void displayQuadsAndLines()
{
	// Render red filled quad
	SDL_Rect fillRect = {SCREEN_WIDTH / 4, SCREEN_HEIGHT / 4, SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2};
	// Red hex colors (r,g,b,a)
	SDL_SetRenderDrawColor(gRenderer, 0xff, 0x00, 0x00, 0xff);
	SDL_RenderFillRect(gRenderer, &fillRect);

	// Render green outlined quad
	SDL_Rect outlineRect = {SCREEN_WIDTH / 6, SCREEN_HEIGHT / 6, SCREEN_WIDTH * 2 / 3, SCREEN_HEIGHT * 2 / 3};
	// Green hex colors (r,g,b,a)
	SDL_SetRenderDrawColor(gRenderer, 0x00, 0xff, 0x00, 0xff);
	SDL_RenderDrawRect(gRenderer, &outlineRect);

	// Render blue horizontal line
	SDL_SetRenderDrawColor(gRenderer, 0x00, 0x00, 0xff, 0xff);
	SDL_RenderDrawLine(gRenderer, 0, SCREEN_HEIGHT / 2, SCREEN_WIDTH, SCREEN_HEIGHT / 2);

	// Draw vertical line of yellow dots
	SDL_SetRenderDrawColor(gRenderer, 0xff, 0xff, 0x00, 0xff);
	for(int i = 0; i < SCREEN_HEIGHT; i+=4)
	{
		SDL_RenderDrawPoint(gRenderer, SCREEN_WIDTH / 2, i);
	}
	return;
}

void displayCharacterAndBackground()
{
	// Render background texture to screen
	gBackgroundTexture.render(0, 0);

	// Render Character to the screen
	gCharacterTexture.render((SCREEN_WIDTH / 2) - 50, (SCREEN_HEIGHT / 2) - 150);
	return;
}

void displaySpriteClips()
{
	// Clear Screen
	SDL_SetRenderDrawColor(gRenderer, 0xff, 0xff, 0xff, 0xff);
	SDL_RenderClear(gRenderer);

	// Logging data to console
	for(int i = 0; i < 4; i++)
	{
		printf("Value of gSpriteClips[%i]'s x,y,w,h is: %i, %i, %i, %i\n", i, gSpriteClips[i].x, gSpriteClips[i].y, gSpriteClips[i].w, gSpriteClips[i].h);
		printf("Value of gSpriteClips[%i]'s memory loc is: %p \n\n", i, &gSpriteClips[i]);
	}

	// Render top left sprite
	gSpriteSheetTexture.render(0, 0, &gSpriteClips[0]);

	// Render top right sprite
	gSpriteSheetTexture.render(SCREEN_WIDTH - gSpriteClips[1].w, 0, &gSpriteClips[1]);

	// Render bottom left sprite
	gSpriteSheetTexture.render(0, SCREEN_HEIGHT - gSpriteClips[2].h, &gSpriteClips[2]);

	// Render bottom right sprite
	gSpriteSheetTexture.render(SCREEN_WIDTH - gSpriteClips[3].w, SCREEN_HEIGHT - gSpriteClips[3].h, &gSpriteClips[3]);

	// Update the screen
	SDL_RenderPresent(gRenderer);
	return;
}

void handleKeyPressColorModulation(SDL_Event e, TestColorSet &testColor_ref)
{
	TestColorSet &myTestColorSet = testColor_ref;
	switch(e.key.keysym.sym)
	{
		// Increase red
		case SDLK_q:
			myTestColorSet.red += 32;
			break;

		// Increase green
		case SDLK_w:
			myTestColorSet.green += 32;
			break;

		// Increase blue
		case SDLK_e:
			myTestColorSet.blue += 32;
			break;

		// Decrease red
		case SDLK_a:
			myTestColorSet.red -= 32;
			break;

		// Decrease green
		case SDLK_s:
			myTestColorSet.green -= 32;
			break;

		// Decrease blue
		case SDLK_d:
			myTestColorSet.blue -= 32;
			break;

	}
	return;
}

void displayColorModulation(SDL_Event e, TestColorSet &testColor_ref)
{
	TestColorSet &myTestColorSet = testColor_ref;
	// Clear screen, set it white
	SDL_SetRenderDrawColor(gRenderer, 0xcd, 0xff, 0xff, 0xff);
	SDL_RenderClear(gRenderer);

	// Modulate and render texture
	gModulatedTexture.setColor(myTestColorSet.red, myTestColorSet.green, myTestColorSet.blue);
	gModulatedTexture.render(0,0);

	// Update screen
	SDL_RenderPresent(gRenderer);
	return;
}

bool main_loop(bool quit, TestColorSet &testColor_ref)
{
	// Event handler
	SDL_Event e;
	// Create reference alias for quit_ref, no need to clear because all references have to point to a valid address aka NOT NULL

	// Create reference alias for testColor_ref, no need to clear because all references have to point to a valid address aka NOT NULL
	TestColorSet &myTestColorSet = testColor_ref;

	// Handle events on queue
	while(SDL_PollEvent(&e) != 0)
	{	
		// User requests quit
		if(e.type == SDL_QUIT)
		{
			// Changes the quit in main to true and exits via the pointer
			quit = true;
		}
		// Temp pausing action on selected surface from key selected
		else if(e.type == SDL_KEYDOWN)
		{
			// This would be for color modulation
			// handleKeyPressColorModulation(e,myTestColorSet);
			// in this case theres nothing to swith to atm so dont do anything
			// handleKeyPressSwitching(e);

			// This will print q if it is held down every loop
			switch(e.key.keysym.sym)
			{
				case SDLK_q:
					printf("The user pressed letter Q!\n");
					break;
				default:
					break;
			}
		}
		/* Here goes the screen related logic */
		displaySingleColorScreen();
	}
	return quit;
}


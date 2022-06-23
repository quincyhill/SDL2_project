#include <cstdio>
#include <SDL2/SDL.h>

// Screen dimensions
const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;
// The window
SDL_Window *gWindow = NULL;

// The surface contained by the window
SDL_Surface *gScreenSurface = NULL;

// The image we will load and show on the screen
SDL_Surface *gHelloWorld = NULL;

bool initWindow();

bool loadMedia();

void closeWindow();

bool initWindow(){
    // Initialize flag
    bool success = true;

    // 
    return success;
}

int main(int argc, char *argv[])
{

    // Initailize SDL
    if(SDL_Init(SDL_INIT_VIDEO) < 0) {
        std::printf("SDL could not initialize! SDL Error: %s\n", SDL_GetError());
    } else {
        // Create the window
        std::printf("We will will try to create a window\n");
        gWindow = SDL_CreateWindow("SDL Window", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
        if(gWindow==NULL) {
            std::printf("Window is null and couldn't be created! SDL Error: %s\n", SDL_GetError());
        } else {
            // Get window surface
            gScreenSurface = SDL_GetWindowSurface(gWindow);

            // Fill the surface white
            SDL_FillRect(gScreenSurface, NULL, SDL_MapRGB(gScreenSurface->format, 0xff, 0xff, 0x22));

            // Dont know what the issue is so this will do.
            SDL_Delay(200);

            SDL_UpdateWindowSurface(gWindow);

            // Wait two seconds then close window
            SDL_Delay(2000);
        }
    }

    // Destroy window
    SDL_DestroyWindow(gWindow);

    // Quit SDL Subsystems
    SDL_Quit();
    return 0;
}
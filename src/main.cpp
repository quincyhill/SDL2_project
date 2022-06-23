#include <cstdio>
#include <SDL2/SDL.h>
#include <string>

// Screen dimensions
const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;
// The window
SDL_Window *gWindow = nullptr;

// The surface contained by the window
SDL_Surface *gScreenSurface = nullptr;

// The image we will load and show on the screen
SDL_Surface *gHelloWorld = nullptr;

bool initWindow();
bool loadMedia();
void closeWindow();

bool initWindow()
{
    // Initialize flag
    bool success = true;
    if(SDL_Init(SDL_INIT_VIDEO) < 0) {
        std::printf("SDL could not initialize! SDL Error: %s\n", SDL_GetError());
    } else {
        // Create the window
        std::printf("We will will try to create a window\n");
        gWindow = SDL_CreateWindow("SDL Window", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
        if(gWindow==nullptr) {
            std::printf("Window is null and couldn't be created! SDL Error: %s\n", SDL_GetError());
            success = false;
        } else {
            // Get window surface
            gScreenSurface = SDL_GetWindowSurface(gWindow);
        }
    }
    return success;
}

bool loadMedia()
{
    std::string img_path = "assets/img/viewport2.bmp";

    bool success = true;
    // lets see
    gHelloWorld = SDL_LoadBMP(img_path.c_str());
    if(gHelloWorld == nullptr) {
        std::printf("Unable to load image %s! SDL Error: %s\n",SDL_GetError(), img_path.c_str());
        success = false;
    }

    return success;
}

void closeWindow()
{
    // Deallocate surface
    SDL_FreeSurface(gHelloWorld);
    // Point to null
    gHelloWorld = nullptr;

    // Destroy window
    SDL_DestroyWindow(gWindow);
    gWindow = nullptr;

    // Quit SDL Subsystems
    SDL_Quit();
}

int main(int argc, char *argv[])
{

    // Initailize SDL
    if(!initWindow()) {
        std::printf("Failed to initialize!\n");
    } else {
        // Load Media
        if(!loadMedia()) {
            std::printf("Failed to load media!");
        } else {
            // Apply the image
            SDL_BlitSurface(gHelloWorld, nullptr, gScreenSurface, nullptr);

            // Again delay the load for some reason until I can find a fix.
            SDL_Delay(50);

            // Update the window surface
            SDL_UpdateWindowSurface(gWindow);

            // Wait 2 Seconds then close
            SDL_Delay(2000);
        }
    }

    closeWindow();
    return 0;
}
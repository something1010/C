#include <iostream>
#include "SDL.h"
#include <map>

SDL_Window* init(const char* windowName, int SCREEN_WIDTH, int SCREEN_HEIGHT) {
    if (SDL_Init( SDL_INIT_VIDEO) < 0 ) {
        std::cout << "SDL could not initialize! SDL_Error: " << SDL_GetError() << std::endl;
        return nullptr;
    }
    SDL_Window* window = SDL_CreateWindow(
            windowName,
            SDL_WINDOWPOS_UNDEFINED,
            SDL_WINDOWPOS_UNDEFINED,
            SCREEN_WIDTH,
            SCREEN_HEIGHT,
            SDL_WINDOW_SHOWN);
    if (window == nullptr) {
        std::cout << "Window could not be created! SDL_Error: " << SDL_GetError() << std::endl;
    }
    return window;
}

SDL_Surface* loadRes(const char* toLoad){
    SDL_Surface* helloWorld = SDL_LoadBMP(toLoad);
    if (helloWorld == nullptr) {
        std::cout << "Unable to load image " << toLoad <<". SDL Error: " << SDL_GetError() << std::endl;
    }
    return helloWorld;
}

void close(SDL_Surface* helloWorld, SDL_Window* window){
    SDL_FreeSurface(helloWorld );
    helloWorld = nullptr;
    SDL_DestroyWindow(window);
    window = nullptr;
    SDL_Quit();
}

void magic(){
    SDL_Event e;
    enum KeyPressSurfaces
    {
        KEY_PRESS_SURFACE_DEFAULT,
        KEY_PRESS_SURFACE_UP,
        KEY_PRESS_SURFACE_DOWN,
        KEY_PRESS_SURFACE_LEFT,
        KEY_PRESS_SURFACE_RIGHT,
        KEY_PRESS_SURFACE_TOTAL
    };
    std::map<SDL_Keycode, const char *> outList = {
            {SDLK_UP, "Up"},
            {SDLK_DOWN, "Dn"},
            {SDLK_LEFT, "Lt"},
            {SDLK_RIGHT, "Rt"} };
    while(true) {
        SDL_PollEvent(&e);
        if(e.type == SDL_QUIT) break;
        if(e.type == SDL_KEYDOWN) std::cout << outList[e.key.keysym.sym] << std::endl;
    }
}

int main(){
    SDL_Window* window = init("angler sdl", 640, 426);
    if (window == nullptr) {return -1;}
    SDL_Surface* screenSurface = SDL_GetWindowSurface(window);
    const char* toLoad = "/Users/admin/files/c++/angler/res/l02.bmp";
    SDL_Surface* helloWorld = loadRes(toLoad);
    if (helloWorld == nullptr) {return -1;}
    SDL_BlitSurface(helloWorld, nullptr, screenSurface, nullptr );
    SDL_UpdateWindowSurface(window);
    magic();
    close(helloWorld, window);
    return 0;
}

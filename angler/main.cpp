
#include <iostream>
#include "SDL2/SDL.h"
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

struct point{
    int x = 0;
    int y = 0;
};
struct snake{
    point sn[1000];
    int lenght = 1;
    snake(int x, int y){
        sn[0].x = x;
        sn[0].y = y;
        for (int i = 1; i < 1000; ++i) {
            sn[i].x = 0;
            sn[i].y = 0;
        }
    }

};
int main(){
    snake s(5, 5);
    SDL_Window* window = init("angler sdl", 500, 500);
    if (window == nullptr) {return -1;}
    SDL_Rect fillRect = {s.sn[0].x * 50, s.sn[0].y * 50 ,50, 50};
    SDL_Renderer* gRenderer = SDL_CreateRenderer( window, -1, SDL_RENDERER_ACCELERATED );
    SDL_SetRenderDrawColor( gRenderer, 0xFF, 0x00, 0x00, 0xFF );
    SDL_RenderFillRect( gRenderer, &fillRect );
    SDL_RenderPresent( gRenderer );

    /*
    SDL_Surface* screenSurface = SDL_GetWindowSurface(window);
    const char* toLoad = "res/l02.bmp";
    SDL_Surface* helloWorld = loadRes(toLoad);
    if (helloWorld == nullptr) {return -1;}

    SDL_BlitSurface(helloWorld, nullptr, screenSurface, nullptr );
    SDL_UpdateWindowSurface(window);
    */

    SDL_Event e;
    int f = 0;
    while(true) {
        f ++;
        if (f >= 10){
            SDL_SetRenderDrawColor(gRenderer, 0xFF, 0x00, 0x00, 0xFF);
            f = 0;
            SDL_PollEvent(&e);
            if (e.type == SDL_QUIT) break;

            if( e.type == SDL_KEYDOWN ) {
                if (e.key.keysym.sym == SDLK_UP and s.sn[0].y != 0) s.sn[0].y -= 1;
                if (e.key.keysym.sym == SDLK_RIGHT and s.sn[0].x != 9) s.sn[0].x += 1;
                if (e.key.keysym.sym == SDLK_LEFT and s.sn[0].x != 0) s.sn[0].x -= 1;
                if (e.key.keysym.sym == SDLK_DOWN and s.sn[0].y != 9) s.sn[0].y += 1;
            }

            fillRect = {s.sn[0].x * 50, s.sn[0].y * 50 ,50, 50};
            SDL_RenderFillRect( gRenderer, &fillRect );
            SDL_RenderPresent( gRenderer );
        }
        if(f == 9){
            SDL_SetRenderDrawColor(gRenderer, 0x00, 0x00, 0x00, 0xFF);
            SDL_RenderClear( gRenderer );
        }
    }
    //close(helloWorld, window);
    return 0;
}

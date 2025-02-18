#include "graphics.h"
#include <SDL2/SDL.h>

SDL_Renderer* renderer;
SDL_Window* window;

void init_graphics() {
    SDL_Init(SDL_INIT_VIDEO);
    window = SDL_CreateWindow("PSVita Radio", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 960, 544, SDL_WINDOW_SHOWN);
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
}

void draw_frame() {
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderClear(renderer);
    SDL_RenderPresent(renderer);
}

void cleanup_graphics() {
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
}

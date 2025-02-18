#include "touch.h"
#include <SDL2/SDL.h>
#include <stdio.h>

void init_touch() {
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        printf("Errore inizializzazione SDL: %s\n", SDL_GetError());
    }
}

bool is_touch_swipe_left() {
    return false; // Implementa la logica con SDL
}

bool is_touch_swipe_right() {
    return false; // Implementa la logica con SDL
}

bool is_touch_swipe_up() {
    return false; // Implementa la logica con SDL
}

bool is_touch_swipe_down() {
    return false; // Implementa la logica con SDL
}

void cleanup_touch() {
    SDL_Quit();
}

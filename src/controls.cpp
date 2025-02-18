#include "controls.h"
#include <SDL2/SDL.h>
#include <stdio.h>

SDL_GameController* controller = NULL;

void init_controls() {
    if (SDL_Init(SDL_INIT_GAMECONTROLLER) < 0) {
        printf("Errore inizializzazione SDL Controller: %s\n", SDL_GetError());
    }
    if (SDL_NumJoysticks() > 0) {
        controller = SDL_GameControllerOpen(0);
        if (!controller) {
            printf("Impossibile aprire il controller: %s\n", SDL_GetError());
        }
    }
}

bool is_button_pressed(int button) {
    if (!controller) return false;
    return SDL_GameControllerGetButton(controller, static_cast<SDL_GameControllerButton>(button));
}

void cleanup_controls() {
    if (controller) {
        SDL_GameControllerClose(controller);
    }
    SDL_QuitSubSystem(SDL_INIT_GAMECONTROLLER);
}
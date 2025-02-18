#include "globals.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_mixer.h>
#include <SDL2/SDL_ttf.h>

SDL_Texture* background = NULL;
SDL_Texture* icon = NULL;
SDL_Texture* startup_icon = NULL;
SDL_Renderer* renderer = NULL;
SDL_Window* window = NULL;
SDL_GameController* controller = NULL;

void init_globals() {
    background = NULL;
    icon = NULL;
    startup_icon = NULL;
    renderer = NULL;
    window = NULL;
    controller = NULL;
}

void cleanup_globals() {
    if (background) SDL_DestroyTexture(background);
    if (icon) SDL_DestroyTexture(icon);
    if (startup_icon) SDL_DestroyTexture(startup_icon);
    if (renderer) SDL_DestroyRenderer(renderer);
    if (window) SDL_DestroyWindow(window);
    if (controller) SDL_GameControllerClose(controller);
}

bool should_exit() {
    SDL_Event event;
    while (SDL_PollEvent(&event)) {
        if (event.type == SDL_QUIT) {
            return true;
        }
    }
    return false;
}

#ifndef GLOBALS_H
#define GLOBALS_H

#include <SDL2/SDL.h>

extern SDL_Texture* background;
extern SDL_Texture* icon;
extern SDL_Texture* startup_icon;
extern SDL_Renderer* renderer;
extern SDL_Window* window;

bool should_exit();

#endif // GLOBALS_H


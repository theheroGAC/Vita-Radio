#include "globals.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_mixer.h>
#include <SDL2/SDL_ttf.h>
#include <psp2/kernel/processmgr.h>
#include <psp2/ctrl.h>
#include "audio.h"
#include "gui.h"
#include "network.h"
#include "equalizer.h"
#include "touch.h"
#include "favorites.h"
#include "audio_visualizer.h"
#include <curl/curl.h>

SDL_Texture* background;
SDL_Texture* icon;
SDL_Texture* startup_icon;
SDL_Renderer* renderer;
SDL_Window* window;

const char* shoutcast_stations[] = {
    "http://streaming.shoutcast.com/station1",
    "http://streaming.shoutcast.com/station2",
    "http://streaming.shoutcast.com/station3"
};
int current_station = 0;
int volume_level = 50;
int theme = 0; // 0 = dark, 1 = light

void change_station(int direction) {
    stop_shoutcast_stream();
    current_station += direction;
    if (current_station < 0) current_station = 2;
    if (current_station > 2) current_station = 0;
    start_shoutcast_stream(shoutcast_stations[current_station]);
}

void toggle_theme() {
    theme = 1 - theme;
}

void adjust_volume(int direction) {
    volume_level += direction * 5;
    if (volume_level < 0) volume_level = 0;
    if (volume_level > 100) volume_level = 100;
    set_audio_volume(volume_level);
}

int main() {
    SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO);
    window = SDL_CreateWindow("PSVita Radio", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 960, 544, SDL_WINDOW_SHOWN);
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    
    background = IMG_LoadTexture(renderer, "app0:/assets/background.png");
    icon = IMG_LoadTexture(renderer, "app0:/assets/icon.png");
    startup_icon = IMG_LoadTexture(renderer, "app0:/assets/startup_icon.png");
    
    init_audio();
    init_network();
    init_gui();
    init_touch();
    init_equalizer();
    init_visualizer();
    load_favorites();
    
    SceCtrlData pad;
    
    // Mostra icona di avvio per qualche secondo
    SDL_RenderClear(renderer);
    SDL_RenderCopy(renderer, background, NULL, NULL);
    SDL_RenderCopy(renderer, startup_icon, NULL, NULL);
    SDL_RenderPresent(renderer);
    SDL_Delay(2000);
    
    start_shoutcast_stream(shoutcast_stations[current_station]); // Avvia lo streaming iniziale
    
    while (1) {
        sceCtrlPeekBufferPositive(0, &pad, 1);
        
        SDL_RenderClear(renderer);
        SDL_RenderCopy(renderer, background, NULL, NULL);
        SDL_RenderCopy(renderer, icon, NULL, NULL);
        
        update_gui();
        update_touch();
        update_audio();
        update_equalizer();
        update_visualizer();
        render_visualizer();
        
        if (is_touch_swipe_left() || (pad.buttons & SCE_CTRL_LTRIGGER)) {
            change_station(-1);
        } else if (is_touch_swipe_right() || (pad.buttons & SCE_CTRL_RTRIGGER)) {
            change_station(1);
        }
        
        if (is_touch_swipe_up()) {
            adjust_volume(1);
        } else if (is_touch_swipe_down()) {
            adjust_volume(-1);
        }
        
        if (pad.buttons & SCE_CTRL_START) {
            toggle_theme();
        }
        
        SDL_RenderPresent(renderer);
        
        if (should_exit()) {
            break;
        }
    }
    
    stop_shoutcast_stream(); // Ferma lo streaming
    
    SDL_DestroyTexture(background);
    SDL_DestroyTexture(icon);
    SDL_DestroyTexture(startup_icon);
    cleanup_audio();
    cleanup_network();
    cleanup_gui();
    cleanup_touch();
    cleanup_equalizer();
    
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
    
    sceKernelExitProcess(0);
    return 0;
}

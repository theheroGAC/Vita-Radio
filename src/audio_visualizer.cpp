#include <vita2d.h>
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

vita2d_texture* background;
vita2d_texture* icon;
vita2d_texture* startup_icon;

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
    vita2d_init();
    vita2d_set_clear_color(RGBA8(0, 0, 0, 255));
    
    background = vita2d_load_PNG_file("app0:/assets/background.png");
    icon = vita2d_load_PNG_file("app0:/assets/icon.png");
    startup_icon = vita2d_load_PNG_file("app0:/assets/startup_icon.png");
    
    init_audio();
    init_network();
    init_gui();
    init_touch();
    init_equalizer();
    init_visualizer();
    load_favorites();
    
    SceCtrlData pad;
    
    // Mostra icona di avvio per qualche secondo
    vita2d_start_drawing();
    vita2d_clear_screen();
    vita2d_draw_texture(background, 0, 0);
    vita2d_draw_texture(startup_icon, 300, 150);
    vita2d_end_drawing();
    vita2d_swap_buffers();
    sceKernelDelayThread(2000000); // Ritardo di 2 secondi
    
    start_shoutcast_stream(shoutcast_stations[current_station]); // Avvia lo streaming iniziale
    
    while (1) {
        sceCtrlPeekBufferPositive(0, &pad, 1);
        
        vita2d_start_drawing();
        vita2d_clear_screen();
        
        vita2d_draw_texture(background, 0, 0);
        vita2d_draw_texture_tint(icon, 10, 10, RGBA8(255, 255, 255, 150)); // Icona con trasparenza
        
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
        
        vita2d_end_drawing();
        vita2d_swap_buffers();
        
        if (should_exit()) {
            break;
        }
    }
    
    stop_shoutcast_stream(); // Ferma lo streaming
    
    vita2d_free_texture(background);
    vita2d_free_texture(icon);
    vita2d_free_texture(startup_icon);
    cleanup_audio();
    cleanup_network();
    cleanup_gui();
    cleanup_touch();
    cleanup_equalizer();
    
    vita2d_fini();
    sceKernelExitProcess(0);
    return 0;
}

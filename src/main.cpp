#include <vita2d.h>
#include <psp2/kernel/processmgr.h>
#include "audio.h"
#include "gui.h"
#include "network.h"
#include "equalizer.h"
#include "touch.h"
#include "favorites.h"

int main() {
    vita2d_init();
    vita2d_set_clear_color(RGBA8(0, 0, 0, 255));
    
    init_audio();
    init_network();
    init_gui();
    init_touch();
    init_equalizer();
    load_favorites();
    
    while (1) {
        vita2d_start_drawing();
        vita2d_clear_screen();
        
        update_gui();
        update_touch();
        update_audio();
        update_equalizer();
        
        vita2d_end_drawing();
        vita2d_swap_buffers();
        
        if (should_exit()) {
            break;
        }
    }
    
    cleanup_audio();
    cleanup_network();
    cleanup_gui();
    cleanup_touch();
    cleanup_equalizer();
    
    vita2d_fini();
    sceKernelExitProcess(0);
    return 0;
}

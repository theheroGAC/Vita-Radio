#include "gui.h"
#include <vita2d.h>
#include <psp2/ctrl.h>

void init_gui() {
    // Inizializza la grafica
    vita2d_init();
    vita2d_set_clear_color(RGBA8(0, 0, 0, 255));
}

void update_gui() {
    // Disegna interfaccia utente
    vita2d_start_drawing();
    vita2d_clear_screen();
    // Aggiungere qui gli elementi UI
    vita2d_end_drawing();
    vita2d_swap_buffers();
}

void cleanup_gui() {
    // Pulisce le risorse grafiche
    vita2d_fini();
}

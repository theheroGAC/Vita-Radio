#include "equalizer.h"
#include <stdio.h>

static int eq_settings[5] = {0, 0, 0, 0, 0}; // Bassi, medi, alti, presenza, brillantezza

void init_equalizer() {
    printf("Equalizzatore inizializzato\n");
}

void update_equalizer() {
    // Simula la gestione dell'equalizzatore
    printf("Aggiornamento equalizzatore: %d %d %d %d %d\n", eq_settings[0], eq_settings[1], eq_settings[2], eq_settings[3], eq_settings[4]);
}

void adjust_equalizer(int band, int value) {
    if (band >= 0 && band < 5) {
        eq_settings[band] = value;
        printf("Equalizzatore aggiornato: Banda %d -> %d\n", band, value);
    }
}

void cleanup_equalizer() {
    printf("Equalizzatore pulito\n");
}

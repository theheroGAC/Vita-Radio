#include "audio.h"
#include <psp2/audioout.h>
#include <mpg123.h>

namespace Audio {
    float volume = 0.5f;

    void init() {
        mpg123_init();
    }

    void playStream(const char *url) {
        // Logica per riprodurre il flusso radio
    }

    void stop() {
        // Stoppa la radio
    }

    void togglePause() {
        // Mette in pausa o riprende la radio
    }

    void prevStation() {
        // Cambia alla stazione precedente
    }

    void nextStation() {
        // Cambia alla stazione successiva
    }

    void setVolume(float vol) {
        volume = vol;
    }

    void setEQ(int bass, int mid, int treble) {
        // Logica per impostare l'equalizzatore
    }
}

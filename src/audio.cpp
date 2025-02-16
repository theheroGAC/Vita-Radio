#include "audio.h"
#include <psp2/audioout.h>
#include <psp2/kernel/threadmgr.h>
#include <stdio.h>

void init_audio() {
    // Inizializza l'audio
    sceAudioOutInit();
}

void update_audio() {
    // Aggiorna lo stato dell'audio (es. streaming radio)
}

void cleanup_audio() {
    // Chiude l'audio e rilascia le risorse
    sceAudioOutRelease();
}

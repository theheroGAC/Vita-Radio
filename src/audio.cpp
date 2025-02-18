#include "audio.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL_mixer.h>
#include <stdio.h>

// Variabile per gestire l'audio
Mix_Music* music = NULL;

void init_audio() {
    if (SDL_Init(SDL_INIT_AUDIO) < 0) {
        printf("Errore nell'inizializzazione dell'audio: %s\n", SDL_GetError());
        return;
    }
    if (Mix_OpenAudio(48000, MIX_DEFAULT_FORMAT, 2, 2048) < 0) {
        printf("Errore nell'apertura dell'audio: %s\n", Mix_GetError());
        return;
    }
}

void update_audio() {
    // Qui puoi aggiungere la gestione dello streaming audio
}

void cleanup_audio() {
    Mix_FreeMusic(music);
    Mix_CloseAudio();
    SDL_QuitSubSystem(SDL_INIT_AUDIO);
}

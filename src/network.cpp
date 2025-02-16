#include "network.h"
#include <psp2/net/net.h>
#include <psp2/net/http.h>
#include <stdio.h>

void init_network() {
    // Inizializza il modulo di rete
    sceNetInit();
    sceHttpInit();
}

void connect_to_stream(const char* url) {
    // Simula la connessione a uno stream radio online
    printf("Connessione a: %s\n", url);
}

void cleanup_network() {
    // Pulisce le risorse di rete
    sceHttpTerm();
    sceNetTerm();
}

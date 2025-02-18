#include "network.h"
#include <curl/curl.h>
#include <stdio.h>

void init_network() {
    // Inizializza la libreria curl
    if (curl_global_init(CURL_GLOBAL_ALL) != 0) {
        printf("Errore inizializzazione curl\n");
    }
}

void cleanup_network() {
    curl_global_cleanup();
}


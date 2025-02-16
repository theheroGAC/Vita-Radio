#include "favorites.h"
#include <vector>
#include <string>
#include <stdio.h>

std::vector<std::string> favorite_stations;

void load_favorites() {
    // Simulazione caricamento preferiti
    favorite_stations.push_back("http://radio1.example.com");
    favorite_stations.push_back("http://radio2.example.com");
    printf("Stazioni preferite caricate\n");
}

void add_favorite(const char* url) {
    favorite_stations.push_back(url);
    printf("Aggiunta stazione preferita: %s\n", url);
}

void remove_favorite(const char* url) {
    for (auto it = favorite_stations.begin(); it != favorite_stations.end(); ++it) {
        if (*it == url) {
            favorite_stations.erase(it);
            printf("Rimossa stazione preferita: %s\n", url);
            break;
        }
    }
}

void list_favorites() {
    printf("Stazioni preferite:\n");
    for (const auto& station : favorite_stations) {
        printf("- %s\n", station.c_str());
    }
}

cmake_minimum_required(VERSION 3.6)

if(NOT DEFINED CMAKE_TOOLCHAIN_FILE)
  if(DEFINED ENV{VITASDK})
    set(CMAKE_TOOLCHAIN_FILE "$ENV{VITASDK}/share/vita.toolchain.cmake" CACHE PATH "toolchain file")
  else()
    message(FATAL_ERROR "Please define VITASDK to point to your SDK path!")
  endif()
endif()

project(PSVitaRadio)
include("${VITASDK}/share/vita.cmake" REQUIRED)

# Set app-specific variables
set(VITA_APP_NAME "PSVitaRadio")
set(VITA_TITLEID  "VITARADIO0001")
set(VITA_VERSION  "01.00")

# Includi la directory dei file di intestazione
include_directories(${CMAKE_SOURCE_DIR}/include)

# Aggiungi i file sorgente
file(GLOB SOURCES "src/*.cpp")

# Crea l'eseguibile per PS Vita
add_executable(PSVitaRadio ${SOURCES})

# Linka le librerie necessarie
target_link_libraries(PSVitaRadio
    SDL2
    SDL2_mixer
    SDL2_image
    SDL2_ttf
	webp
	webpdemux
	pthread
    curl
    jpeg
    freetype
    ssl
    crypto
    m
    stdc++
    png
    z
)

# Crea il file VPK con le immagini corrette
vita_create_self(PSVitaRadio.self PSVitaRadio)
vita_create_vpk(PSVitaRadio.vpk ${VITA_TITLEID} PSVitaRadio.self
    VERSION ${VITA_VERSION}
    NAME ${VITA_APP_NAME}
    FILE app0:/assets/icon0.png assets/icon0.png
    FILE app0:/assets/background.png assets/background.png
)

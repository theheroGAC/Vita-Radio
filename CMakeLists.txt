cmake_minimum_required(VERSION 3.2)

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

# Add executable files
add_executable(PSVitaRadio
    src/main.cpp
    src/audio.cpp
    src/gui.cpp
    src/network.cpp
    src/equalizer.cpp
    src/touch.cpp
    src/favorites.cpp
    assets/icon.png
    assets/background.png
)

# Create VPK package
vita_create_self(PSVitaRadio.self PSVitaRadio)
vita_create_vpk(PSVitaRadio.vpk PSVitaRadio VITA_RADIO SCE_APP_TITLE assets/icon.png)


#include <vita2d.h>
#include <psp2/touch.h>
#include <psp2/kernel/processmgr.h>
#include "audio.h"
#include "network.h"

vita2d_pgf *pgf;
bool running = true;

enum EQPreset { FLAT, ROCK, JAZZ, POP };
EQPreset currentPreset = FLAT;

void applyEQ(EQPreset preset) {
    switch (preset) {
        case FLAT: Audio::setEQ(0, 0, 0); break;
        case ROCK: Audio::setEQ(5, -2, 3); break;
        case JAZZ: Audio::setEQ(-2, 4, 2); break;
        case POP:  Audio::setEQ(3, 1, 5); break;
    }
}

void drawMenu() {
    vita2d_start_drawing();
    vita2d_clear_screen();

    vita2d_pgf_draw_text(pgf, 100, 100, RGBA8(255,255,255,255), 20, "PS Vita Radio");

    // Pulsanti virtuali
    vita2d_draw_rectangle(80, 450, 120, 60, RGBA8(50,50,255,255));
    vita2d_pgf_draw_text(pgf, 105, 485, RGBA8(255,255,255,255), 20, "⏮");

    vita2d_draw_rectangle(240, 450, 120, 60, RGBA8(50,255,50,255));
    vita2d_pgf_draw_text(pgf, 270, 485, RGBA8(255,255,255,255), 20, "⏯");

    vita2d_draw_rectangle(400, 450, 120, 60, RGBA8(50,50,255,255));
    vita2d_pgf_draw_text(pgf, 425, 485, RGBA8(255,255,255,255), 20, "⏭");

    vita2d_draw_rectangle(600, 450, 120, 60, RGBA8(255,150,50,255));
    vita2d_pgf_draw_text(pgf, 625, 485, RGBA8(255,255,255,255), 20, "🎛 EQ");

    vita2d_end_drawing();
    vita2d_swap_buffers();
}

void handleTouch() {
    SceTouchData touch;
    sceTouchPeek(SCE_TOUCH_PORT_FRONT, &touch, 1);

    if (touch.reportNum > 0) {
        int x = touch.report[0].x * 960 / 1920;
        int y = touch.report[0].y * 544 / 1088;

        if (y > 450 && y < 510) {
            if (x > 80 && x < 200) Audio::prevStation();
            if (x > 240 && x < 360) Audio::togglePause();
            if (x > 400 && x < 520) Audio::nextStation();
            if (x > 600 && x < 720) {
                currentPreset = static_cast<EQPreset>((currentPreset + 1) % 4);
                applyEQ(currentPreset);
            }
        }
    }
}

int main() {
    vita2d_init();
    pgf = vita2d_load_default_pgf();

    Audio::init();
    Network::init();
    Audio::playStream("http://example.com/stream.mp3");

    while (running) {
        handleTouch();
        drawMenu();
        sceKernelDelayThread(100 * 1000);
    }

    vita2d_fini();
    vita2d_free_pgf(pgf);
    sceKernelExitProcess(0);
    return 0;
}

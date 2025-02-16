#ifndef AUDIO_H
#define AUDIO_H

namespace Audio {
    void init();
    void playStream(const char *url);
    void stop();
    void togglePause();
    void prevStation();
    void nextStation();
    void setVolume(float vol);
    void setEQ(int bass, int mid, int treble);
}

#endif

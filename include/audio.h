#ifndef AUDIO_H
#define AUDIO_H

void init_audio();
void start_shoutcast_stream(const char* url);
void stop_shoutcast_stream();
void set_audio_volume(int volume);
void update_audio();
void cleanup_audio();

#endif // AUDIO_H

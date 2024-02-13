// audio.hpp

#ifndef AUDIO_HPP
#define AUDIO_HPP

#include <SDL2/SDL_mixer.h>
#include <iostream>
#include <stdexcept>

class Audio {
public:
    Audio();
    ~Audio();
    
    void cleanUp();
    void openAudio();
    Mix_Music* loadMusic(const char* path);
    Mix_Chunk* loadWAV(const char* path);
    void playAudioChannel(Mix_Chunk* chunk);
    void closeAudio();
    bool audioPlaying();
    void playMusic(Mix_Music* music, int loops);
    void pauseMusic();
    void resumeMusic();
    bool isMusicPaused();

private:
    static constexpr int MAX_AUDIO_CHUNKS = 10;
    
    Mix_Music* bgMusic;
    Mix_Chunk* audios[MAX_AUDIO_CHUNKS];
};

#endif

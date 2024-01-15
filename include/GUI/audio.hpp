#ifndef AUDIO_HPP
#define AUDIO_HPP

#include <SDL2/SDL_mixer.h>
#include <iostream>
#include <vector>

class Audio
{
    public:
    void cleanUp()
    {
        // Cleanup audio chunks
        for (Mix_Chunk *audio : audios)
        {
            Mix_FreeChunk(audio);
        }

        // Cleanup background music
        if (bgMusic != nullptr)
        {
            Mix_FreeMusic(bgMusic);
        }

        // Close audio system
        closeAudio();

        Mix_Quit();
    }

    void openAudio()
    {
        // Open SDL audio
        if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0)
        {
            throw std::runtime_error("Mixer init failed: " + std::string(Mix_GetError()));
        }
    }

    // Music and Audio Functions

    Mix_Music *loadMusic(const char *path)
    {
        // Load background music
        Mix_Music *mp3 = Mix_LoadMUS(path);

        if (!mp3)
        {
            throw std::runtime_error("Mix_LoadMUS Error: " + std::string(Mix_GetError()));
        }

        bgMusic = mp3;
        return mp3;
    }

    Mix_Chunk *loadWAV(const char *path)
    {
        // Load audio chunk
        Mix_Chunk *wav = Mix_LoadWAV(path);
        if (!wav)
        {
            throw std::runtime_error("Mix_LoadWAV Error: " + std::string(Mix_GetError()));
        }

        audios.push_back(wav);
        return wav;
    }

    void playAudioChannel(Mix_Chunk *chunk)
    {
        // Play audio chunk in a new channel
        Mix_PlayChannel(-1, chunk, 0);
    }

    void closeAudio()
    {
        // Close SDL audio
        Mix_CloseAudio();
    }

    bool audioPlaying()
    {
        // Check if music is playing
        return Mix_PlayingMusic();
    }

    void playMusic(Mix_Music *music, int loops)
    {
        // Play background music
        Mix_PlayMusic(music, loops);
    }

    void pauseMusic()
    {
        // Pause background music
        Mix_PauseMusic();
    }

    void resumeMusic()
    {
        // Resume background music
        Mix_ResumeMusic();
    }

    bool isMusicPaused()
    {
        // Check if background music is paused
        return Mix_PausedMusic();
    }

private:
    Mix_Music *bgMusic;
    std::vector<Mix_Chunk *> audios;
};

#endif
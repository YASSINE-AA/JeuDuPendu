#include "audio.hpp"

Audio::Audio() : bgMusic(nullptr) {
    for (int i = 0; i < MAX_AUDIO_CHUNKS; ++i) {
        audios[i] = nullptr;
    }
}

Audio::~Audio() {
    cleanUp();
}

void Audio::cleanUp() {
    // Cleanup background music
    if (bgMusic != nullptr) {
        Mix_FreeMusic(bgMusic);
    }

    // Cleanup audio chunks
    for (int i = 0; i < MAX_AUDIO_CHUNKS; ++i) {
        if (audios[i] != nullptr) {
            Mix_FreeChunk(audios[i]);
            audios[i] = nullptr;
        }
    }

    // Close audio system
    closeAudio();
    Mix_Quit();
}

void Audio::openAudio() {
    // Open SDL audio
    if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0) {
        throw std::runtime_error("Mixer init failed: " + std::string(Mix_GetError()));
    }
}

Mix_Music* Audio::loadMusic(const char* path) {
    // Load background music
    Mix_Music* mp3 = Mix_LoadMUS(path);

    if (!mp3) {
        throw std::runtime_error("Mix_LoadMUS Error: " + std::string(Mix_GetError()));
    }

    bgMusic = mp3;
    return mp3;
}

Mix_Chunk* Audio::loadWAV(const char* path) {
    // Find an available slot
    int slot = -1;
    for (int i = 0; i < MAX_AUDIO_CHUNKS; ++i) {
        if (audios[i] == nullptr) {
            slot = i;
            break;
        }
    }
    
    if (slot == -1) {
        throw std::runtime_error("No available slot for audio chunk.");
    }

    // Load audio chunk
    Mix_Chunk* wav = Mix_LoadWAV(path);
    if (!wav) {
        throw std::runtime_error("Mix_LoadWAV Error: " + std::string(Mix_GetError()));
    }

    audios[slot] = wav;
    return wav;
}

void Audio::playAudioChannel(Mix_Chunk* chunk) {
    // Play audio chunk in a new channel
    Mix_PlayChannel(-1, chunk, 0);
}

void Audio::closeAudio() {
    // Close SDL audio
    Mix_CloseAudio();
}

bool Audio::audioPlaying() {
    // Check if music is playing
    return Mix_PlayingMusic();
}

void Audio::playMusic(Mix_Music* music, int loops) {
    // Play background music
    Mix_PlayMusic(music, loops);
}

void Audio::pauseMusic() {
    // Pause background music
    Mix_PauseMusic();
}

void Audio::resumeMusic() {
    // Resume background music
    Mix_ResumeMusic();
}

bool Audio::isMusicPaused() {
    // Check if background music is paused
    return Mix_PausedMusic();
}
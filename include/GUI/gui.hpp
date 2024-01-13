#ifndef GUI_HPP
#define GUI_HPP

#include <string>
#include <stdexcept>
#include <filesystem>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_keyboard.h>
#include <unistd.h>
#include <SDL2/SDL_mixer.h>

class GUI
{
public:
    GUI() : win(nullptr), ren(nullptr) {}

    void cleanUp()
    {
        for (SDL_Texture *texture : textures)
        {
            SDL_DestroyTexture(texture);
        }

        for (TTF_Font *font : fonts)
        {
            TTF_CloseFont(font);
        }

        for (Mix_Chunk *audio : audios)
        {
            Mix_FreeChunk(audio);
        }

        if (bgMusic)
            Mix_FreeMusic(bgMusic);

        if (ren != nullptr)
            SDL_DestroyRenderer(ren);
        if (win != nullptr)
            SDL_DestroyWindow(win);
        closeAudio();
        Mix_Quit();
        TTF_Quit();
        IMG_Quit();
        SDL_Quit();
    }

    void init()
    {

        if (SDL_Init(SDL_INIT_EVERYTHING | SDL_INIT_AUDIO) != 0)
        {
            throw std::runtime_error("SDL_Init Error: " + std::string(SDL_GetError()));
        }

        int flags = IMG_INIT_JPG | IMG_INIT_PNG;
        int initted = IMG_Init(flags);
        if ((initted & flags) != flags)
        {
            throw std::runtime_error("IMG_Init Error: " + std::string(IMG_GetError()));
        }
        if (TTF_Init() < 0)
        {
            throw std::runtime_error("SDL_ttf initialization failed: " + std::string(TTF_GetError()));
        }
        int flag = MIX_INIT_MP3;

        if (Mix_Init(MIX_INIT_MP3) != flag)
        {
            throw std::runtime_error(Mix_GetError());
        }
    }

    void openAudio()
    {
        if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0)
        {
            throw std::runtime_error("Mixer init failed! \n");
        }
    }

    Mix_Music *loadMusic(const char *path)
    {
        Mix_Music *mp3 = Mix_LoadMUS(path);

        if (!mp3)
        {
            throw std::runtime_error(Mix_GetError());
        }

        bgMusic = mp3;
        return mp3;
    }

    Mix_Chunk *loadWAV(const char *path)
    {
        Mix_Chunk *wav = Mix_LoadWAV(path);
        if (!wav)
        {
            throw std::runtime_error(Mix_GetError());
        }

        audios.push_back(wav);
        return wav;
    }

    void playAudioChannel(Mix_Chunk *chunk)
    {
        Mix_PlayChannel(-1, chunk, 0);
    }

    void closeAudio()
    {
        Mix_CloseAudio();
    }

    bool audioPlaying()
    {
        return Mix_PlayingMusic();
    }

    void playMusic(Mix_Music *music, int loops)
    {
        Mix_PlayMusic(music, loops);
    }

    void pauseMusic()
    {
        Mix_PauseMusic();
    }

    void resumeMusic()
    {
        Mix_ResumeMusic();
    }

    bool isMusicPaused()
    {

        return Mix_PausedMusic();
    }

    void renderCircle(int centerX, int centerY, int radius)
    {

        for (int angle = 0; angle <= 360; ++angle)
        {

            int x = centerX + (int)(radius * cos(angle * M_PI / 180.0));
            int y = centerY + (int)(radius * sin(angle * M_PI / 180.0));

            SDL_RenderDrawPoint(ren, x, y);
        }
    }

    void renderLine(int x1, int y1, int x2, int y2, int lineThickness)
    {

        for (int i = 0; i < lineThickness; ++i)
        {
            SDL_RenderDrawLine(ren, x1, y1 + i, x2, y2 + i);
        }
    }

    TTF_Font *openFont(const char *file, int size)
    {
        TTF_Font *font = TTF_OpenFont(file, size);
        if (font == nullptr)
            throw std::runtime_error("TTF_Open Error: " + std::string(TTF_GetError()));

        fonts.push_back(font);
        return font;
    }
    SDL_Texture *renderFont(TTF_Font *font, const char *text, SDL_Color color, int x, int y)
    {

        SDL_Surface *textSurface = TTF_RenderText_Solid(font, text, color);
        if (textSurface == nullptr)
        {
            throw std::runtime_error("TTF_RenderText_Solid Error: " + std::string(TTF_GetError()));
        }

        SDL_Texture *textTexture = SDL_CreateTextureFromSurface(ren, textSurface);
        SDL_FreeSurface(textSurface);

        if (textTexture == nullptr)
        {
            throw std::runtime_error("SDL_CreateTextureFromSurface Error: " + std::string(SDL_GetError()));
        }

        if (ren != nullptr)
        {
            SDL_Rect dest = {x, y, textSurface->w, textSurface->h};
            SDL_RenderCopy(ren, textTexture, NULL, &dest);
        }
        else
        {
            throw std::runtime_error("Renderer not initialized!");
        }

        textures.push_back(textTexture);

        return textTexture;
    }

    void createWindow(int x, int y, int w, int h)
    {
        win = SDL_CreateWindow("Hangman", x, y, w, h, SDL_WINDOW_SHOWN);
        if (win == nullptr)
        {
            throw std::runtime_error("SDL_CreateWindow Error: " + std::string(SDL_GetError()));
        }
    }

    void createRenderer()
    {
        ren = SDL_CreateRenderer(win, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
        if (ren == nullptr)
        {
            throw std::runtime_error("SDL_CreateRenderer Error: " + std::string(SDL_GetError()));
        }
    }

    void render(SDL_Texture *texture, SDL_Rect *dest)
    {
        if (ren != nullptr)
        {
            SDL_RenderCopy(ren, texture, NULL, dest);
        }
        else
        {
            throw std::runtime_error("Render not initialized!");
        }
    }

    SDL_Texture *getTexture(const char *filename)
    {
        SDL_Texture *tex = IMG_LoadTexture(ren, filename);

        if (tex == nullptr)
            throw runtime_error((std::string) "Texture for " + filename + " is null! ");
        textures.push_back(tex);
        return tex;
    }

    void clearRender()
    {
        if (ren != nullptr)
        {
            for (SDL_Texture *texture : textures)
            {
                SDL_DestroyTexture(texture);
            }
            SDL_RenderClear(ren);
        }
        else
        {
            throw std::runtime_error("Render not initialized!");
        }
    }

    void renderHangman(int incorrectGuesses, int difficulty)
    {
        if (difficulty == 0 && incorrectGuesses >= 1 || difficulty == 1 && incorrectGuesses >= 1 || difficulty == 2 && incorrectGuesses >= 1)
        {
            renderLine(100, 500, 200, 500, 5);
        }

        if (difficulty == 0 && incorrectGuesses >= 2 || difficulty == 1 && incorrectGuesses >= 1 || difficulty == 2 && incorrectGuesses >= 1)
        {
            renderLine(150, 300, 150, 500, 5);
        }

        if (difficulty == 0 && incorrectGuesses >= 3  || difficulty == 1 && incorrectGuesses >= 2 || difficulty == 2 && incorrectGuesses >= 1)
        {
            renderLine(150, 300, 300, 300, 5);
        }

        if (difficulty == 0 && incorrectGuesses >= 4  || difficulty == 1 && incorrectGuesses >= 2 || difficulty == 2 && incorrectGuesses >= 2)
        {
            renderLine(300, 300, 300, 350, 5);
        }

        if (difficulty == 0 && incorrectGuesses >= 5  || difficulty == 1 && incorrectGuesses >= 2 || difficulty == 2 && incorrectGuesses >= 2)
        {
            renderCircle(300, 375, 20);
        }

        if (difficulty == 0 && incorrectGuesses >= 6  || difficulty == 1 && incorrectGuesses >= 3 || difficulty == 2 && incorrectGuesses >= 3)
        {
            renderLine(300, 395, 300, 450, 5);
        }

        if (difficulty == 0 && incorrectGuesses >= 7  || difficulty == 1 && incorrectGuesses >= 4|| difficulty == 2 && incorrectGuesses >= 3)
        {
            renderLine(300, 410, 320, 430, 5);
            renderLine(300, 410, 280, 430, 5);
        }

        if (difficulty == 0 && incorrectGuesses >= 8  || difficulty == 1 && incorrectGuesses >= 5|| difficulty == 2 && incorrectGuesses >= 3)
        {
            renderLine(300, 450, 320, 470, 5);
            renderLine(300, 450, 280, 470, 5);
        }
    }

    void update()
    {
        if (ren != nullptr)
        {
            SDL_RenderPresent(ren);
        }
        else
        {
            throw std::runtime_error("Render not initialized!");
        }
    }
    char convertSDLKeyToChar(SDL_Keycode key)
    {
        if ((key >= SDLK_a && key <= SDLK_z) || (key >= SDLK_0 && key <= SDLK_9))
        {
            return static_cast<char>(key);
        }

        return '\0';
    }

    void getMousePosition(int *x, int *y)
    {
        SDL_GetMouseState(x, y);
    }

    bool isBtnArea(int mouseX, int mouseY, SDL_Rect rect)
    {
        if ((mouseX > rect.x && mouseX < rect.x + rect.w) && (mouseY > rect.y && mouseY < rect.y + rect.h))
        {
            return true;
        }
        return false;
    }

    void renderRect(SDL_Rect rect)
    {
        if (ren != nullptr)
        {
            SDL_RenderDrawRect(ren, &rect);
        }
    }

private:
    SDL_Window *win;
    SDL_Renderer *ren;
    vector<SDL_Texture *> textures;
    Mix_Music *bgMusic;
    vector<Mix_Chunk *> audios;
    vector<TTF_Font *> fonts;
};

#endif

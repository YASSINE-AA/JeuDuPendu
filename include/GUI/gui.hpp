#ifndef GUI_HPP
#define GUI_HPP

#include <string>
#include <stdexcept>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

class GUI
{
public:
    GUI() : win(nullptr), ren(nullptr), backgroundTexture(nullptr) {}

    ~GUI()
    {
        cleanUp();
    }

    void init()
    {
        if (SDL_Init(SDL_INIT_EVERYTHING) != 0)
        {
            throw std::runtime_error("SDL_Init Error: " + std::string(SDL_GetError()));
        }
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
        SDL_RenderCopy(ren, texture, NULL, dest);
        SDL_RenderPresent(ren);
    }

    SDL_Texture *getTexture(const char *filename)
    {
        return IMG_LoadTexture(ren, filename);
    }

    void clearRender()
    {
        SDL_RenderClear(ren);
    }

    void update()
    {
        SDL_RenderPresent(ren);
    }

    void handleEvents()
    {
        SDL_Event event;
        while (SDL_PollEvent(&event))
        {
            listenForExit(event);
        }
    }

private:
    SDL_Window *win;
    SDL_Renderer *ren;
    SDL_Texture *backgroundTexture;

    void cleanUp()
    {
        if (backgroundTexture != nullptr)
            SDL_DestroyTexture(backgroundTexture);
        if (ren != nullptr)
            SDL_DestroyRenderer(ren);
        if (win != nullptr)
            SDL_DestroyWindow(win);
        SDL_Quit();
    }

    void listenForExit(SDL_Event &event)
    {
        if (event.type == SDL_QUIT)
        {
            cleanUp();
            throw std::runtime_error("SDL_QUIT event received");
        }
    }
};

#endif

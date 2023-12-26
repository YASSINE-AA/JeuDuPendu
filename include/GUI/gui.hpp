#ifndef GUI_HPP
#define GUI_HPP

#include <string>
#include <stdexcept>
#include <filesystem>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <unistd.h>

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

        if (ren != nullptr)
            SDL_DestroyRenderer(ren);
        if (win != nullptr)
            SDL_DestroyWindow(win);
        TTF_Quit();
        IMG_Quit();
        SDL_Quit();
    }

    void init()
    {

        if (SDL_Init(SDL_INIT_EVERYTHING) != 0)
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
        SDL_FreeSurface(textSurface); // Free the surface after creating the texture.

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

    void handleEvents(bool &loadMainMenu, bool &loadGame)
    {
        SDL_Event event;
        while (SDL_PollEvent(&event))
        {
            if (event.type == SDL_QUIT)
            {
                cleanUp();
            }
            else if (event.type == SDL_MOUSEBUTTONDOWN)
            {

                int x;
                int y;
                getMousePosition(&x, &y);
                if (isQuitBtnArea(x, y))
                {
                    cleanUp();
                }
                else if (isStartBtnArea(x, y))
                {
                    loadGame = true;
                    loadMainMenu = false;
                }
            }
        }
    }

private:
    SDL_Window *win;
    SDL_Renderer *ren;
    vector<SDL_Texture *> textures;
    vector<TTF_Font *> fonts;

    void getMousePosition(int *x, int *y)
    {
        SDL_GetMouseState(x, y);
    }

    bool isStartBtnArea(int mouseX, int mouseY)
    {
        if ((mouseX < 334 && mouseX > 150) && (mouseY > 180 && mouseY < 262))
        {
            return true;
        }

        return false;
    }

    bool isQuitBtnArea(int mouseX, int mouseY)
    {
        if ((mouseX < 334 && mouseX > 150) && (mouseY > 300 && mouseY < 382))
        {
            return true;
        }
        return false;
    }
};

#endif

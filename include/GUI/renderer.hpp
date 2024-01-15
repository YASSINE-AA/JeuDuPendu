#ifndef RENDERER_HPP
#define RENDERER_HPP
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <iostream>
#include <vector>

class Renderer
{
public:
    Renderer(SDL_Window *win) : win(win) {}

    void cleanUp()
    {
        // Cleanup textures
        for (SDL_Texture *texture : textures)
        {
            SDL_DestroyTexture(texture);
        }

        // Cleanup fonts
        for (TTF_Font *font : fonts)
        {
            TTF_CloseFont(font);
        }

        // Cleanup renderer
        if (ren != nullptr)
        {
            SDL_DestroyRenderer(ren);
        }

        TTF_Quit();
        IMG_Quit();
    }

    void createRenderer()
    {
        // Create SDL renderer
        ren = SDL_CreateRenderer(win, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
        if (ren == nullptr)
        {
            throw std::runtime_error("SDL_CreateRenderer Error: " + std::string(SDL_GetError()));
        }
    }

    void render(SDL_Texture *texture, SDL_Rect *dest)
    {
        // Render texture on screen
        if (ren != nullptr)
        {
            SDL_RenderCopy(ren, texture, NULL, dest);
        }
        else
        {
            throw std::runtime_error("Renderer not initialized!");
        }
    }

    SDL_Texture *getTexture(const char *filename)
    {
        // Load image file as texture
        SDL_Texture *tex = IMG_LoadTexture(ren, filename);

        if (tex == nullptr)
            throw std::runtime_error("Texture for " + std::string(filename) + " is null!");

        textures.push_back(tex);
        return tex;
    }

    void clearRender()
    {
        // Clear renderer and cleanup textures
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
            throw std::runtime_error("Renderer not initialized!");
        }
    }

    // Update and Input Functions

    void update()
    {
        // Present renderer
        if (ren != nullptr)
        {
            SDL_RenderPresent(ren);
        }
        else
        {
            throw std::runtime_error("Renderer not initialized!");
        }
    }

    // Rendering Functions

    void renderCircle(int centerX, int centerY, int radius)
    {
        // Render a circle using SDL_RenderDrawPoint
        for (int angle = 0; angle <= 360; ++angle)
        {
            int x = centerX + (int)(radius * cos(angle * M_PI / 180.0));
            int y = centerY + (int)(radius * sin(angle * M_PI / 180.0));
            SDL_RenderDrawPoint(ren, x, y);
        }
    }

    void renderLine(int x1, int y1, int x2, int y2, int lineThickness)
    {
        // Render a line using SDL_RenderDrawLine
        for (int i = 0; i < lineThickness; ++i)
        {
            SDL_RenderDrawLine(ren, x1, y1 + i, x2, y2 + i);
        }
    }

    void renderRect(SDL_Rect rect)
    {
        // Render rectangle on screen
        if (ren != nullptr)
        {
            SDL_RenderDrawRect(ren, &rect);
        }
    }

    void renderRectFilled(SDL_Rect rect)
    {
        if (ren != nullptr)
        {
            SDL_SetRenderDrawColor(ren, 240, 240, 240, 255);
            SDL_RenderFillRect(ren, &rect);
            SDL_SetRenderDrawColor(ren, 0, 0, 0, 255);
            SDL_RenderDrawRect(ren, &rect);
        }
    }

    // Font Functions

    TTF_Font *openFont(const char *file, int size)
    {
        // Open TTF font
        TTF_Font *font = TTF_OpenFont(file, size);
        if (font == nullptr)
            throw std::runtime_error("TTF_OpenFont Error: " + std::string(TTF_GetError()));

        fonts.push_back(font);
        return font;
    }

    int renderFont(TTF_Font *font, const char *text, SDL_Color color, int x, int y)
    {
        int w;
        // Render text to surface, create texture, and render on screen
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
            w = textSurface->w;
            SDL_RenderCopy(ren, textTexture, NULL, &dest);
            SDL_DestroyTexture(textTexture);
        }
        else
        {
            throw std::runtime_error("Renderer not initialized!");
        }
        return w;
    }

    // Game related
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

        if (difficulty == 0 && incorrectGuesses >= 3 || difficulty == 1 && incorrectGuesses >= 2 || difficulty == 2 && incorrectGuesses >= 1)
        {
            renderLine(150, 300, 300, 300, 5);
        }

        if (difficulty == 0 && incorrectGuesses >= 4 || difficulty == 1 && incorrectGuesses >= 2 || difficulty == 2 && incorrectGuesses >= 2)
        {
            renderLine(300, 300, 300, 350, 5);
        }

        if (difficulty == 0 && incorrectGuesses >= 5 || difficulty == 1 && incorrectGuesses >= 2 || difficulty == 2 && incorrectGuesses >= 2)
        {
            renderCircle(300, 375, 20);
        }

        if (difficulty == 0 && incorrectGuesses >= 6 || difficulty == 1 && incorrectGuesses >= 3 || difficulty == 2 && incorrectGuesses >= 3)
        {
            renderLine(300, 395, 300, 450, 5);
        }

        if (difficulty == 0 && incorrectGuesses >= 7 || difficulty == 1 && incorrectGuesses >= 4 || difficulty == 2 && incorrectGuesses >= 3)
        {
            renderLine(300, 410, 320, 430, 5);
            renderLine(300, 410, 280, 430, 5);
        }

        if (difficulty == 0 && incorrectGuesses >= 8 || difficulty == 1 && incorrectGuesses >= 5 || difficulty == 2 && incorrectGuesses >= 3)
        {
            renderLine(300, 450, 320, 470, 5);
            renderLine(300, 450, 280, 470, 5);
        }
    }

private:
    SDL_Window *win;   // current window
    SDL_Renderer *ren; // renderer
    std::vector<SDL_Texture *> textures;
    std::vector<TTF_Font *> fonts;
};
#endif
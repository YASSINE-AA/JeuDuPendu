// renderer.cpp

#include "renderer.hpp"

Renderer::Renderer(SDL_Window *win) : win(win), ren(nullptr), textures(nullptr), fonts(nullptr), numTextures(0), numFonts(0) {}

Renderer::~Renderer()
{
    cleanUp();
}

void Renderer::cleanUp()
{
    // Cleanup textures
    for (int i = 0; i < numTextures; ++i)
    {
        SDL_DestroyTexture(textures[i]);
    }
    delete[] textures;

    // Cleanup fonts
    for (int i = 0; i < numFonts; ++i)
    {
        TTF_CloseFont(fonts[i]);
    }
    delete[] fonts;

    // Cleanup renderer
    if (ren != nullptr)
    {
        SDL_DestroyRenderer(ren);
    }

    TTF_Quit();
    IMG_Quit();
}

void Renderer::createRenderer()
{
    // Create SDL renderer
    ren = SDL_CreateRenderer(win, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    if (ren == nullptr)
    {
        throw std::runtime_error("SDL_CreateRenderer Error: " + std::string(SDL_GetError()));
    }
}

int Renderer::getTextHeight(TTF_Font *font)
{
    if (font == nullptr)
    {
        return 0;
    }
    return TTF_FontHeight(font) + TTF_FontAscent(font) + TTF_FontDescent(font);
}

void Renderer::getTextSize(TTF_Font *font, const char *text, int *width, int *height)
{
    if (font == nullptr || text == nullptr || width == nullptr || height == nullptr)
    {
        *width = 0;
        *height = 0;
        return;
    }

    SDL_Surface *surface = TTF_RenderText_Solid(font, text, {255, 255, 255});
    if (surface == nullptr)
    {
        *width = 0;
        *height = 0;
        return;
    }

    *width = surface->w;
    *height = surface->h;

    SDL_FreeSurface(surface);
}

void Renderer::render(SDL_Texture *texture, SDL_Rect *dest)
{
    if (ren != nullptr)
    {
        SDL_RenderCopy(ren, texture, NULL, dest);
    }
    else
    {
        throw std::runtime_error("Renderer not initialized!");
    }
}

SDL_Texture *Renderer::getTexture(const char *filename)
{
    SDL_Texture *tex = IMG_LoadTexture(ren, filename);

    if (tex == nullptr)
        throw std::runtime_error("Texture for " + std::string(filename) + " is null!");

    SDL_Texture **temp = new SDL_Texture *[numTextures + 1];
    for (int i = 0; i < numTextures; ++i)
    {
        temp[i] = textures[i];
    }
    temp[numTextures++] = tex;
    delete[] textures;
    textures = temp;
    return tex;
}

void Renderer::clearRender()
{
    if (ren != nullptr)
    {
        for (int i = 0; i < numTextures; ++i)
        {
            SDL_DestroyTexture(textures[i]);
        }
        SDL_RenderClear(ren);
    }
    else
    {
        throw std::runtime_error("Renderer not initialized!");
    }
}

void Renderer::update()
{
    if (ren != nullptr)
    {
        SDL_RenderPresent(ren);
    }
    else
    {
        throw std::runtime_error("Renderer not initialized!");
    }
}

void Renderer::renderCircle(int centerX, int centerY, int radius)
{
    for (int angle = 0; angle <= 360; ++angle)
    {
        int x = centerX + static_cast<int>(radius * cos(angle * M_PI / 180.0));
        int y = centerY + static_cast<int>(radius * sin(angle * M_PI / 180.0));
        SDL_RenderDrawPoint(ren, x, y);
    }
}

void Renderer::renderLine(int x1, int y1, int x2, int y2, int lineThickness)
{
    for (int i = 0; i < lineThickness; ++i)
    {
        SDL_RenderDrawLine(ren, x1, y1 + i, x2, y2 + i);
    }
}

void Renderer::renderRect(SDL_Rect rect)
{
    if (ren != nullptr)
    {
        SDL_RenderDrawRect(ren, &rect);
    }
}

void Renderer::renderRectFilled(SDL_Rect rect, SDL_Color border, SDL_Color inside)
{
    if (ren != nullptr)
    {
        SDL_SetRenderDrawColor(ren, inside.r, inside.g, inside.b, inside.a);
        SDL_RenderFillRect(ren, &rect);

        SDL_SetRenderDrawColor(ren, border.r, border.g, border.b, border.a);
        SDL_RenderDrawRect(ren, &rect);

        SDL_SetRenderDrawColor(ren, 0, 0, 0, 255); // Reset render draw color
    }
}

TTF_Font *Renderer::openFont(const char *file, int size)
{
    TTF_Font *font = TTF_OpenFont(file, size);
    if (font == nullptr)
        throw std::runtime_error("TTF_OpenFont Error: " + std::string(TTF_GetError()));

    TTF_Font **temp = new TTF_Font *[numFonts + 1];
    for (int i = 0; i < numFonts; ++i)
    {
        temp[i] = fonts[i];
    }
    temp[numFonts++] = font;
    delete[] fonts;
    fonts = temp;
    return font;
}

int Renderer::renderFont(TTF_Font *font, const char *text, SDL_Color color, int x, int y)
{
    int w;
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

void Renderer::renderHangman(int incorrectGuesses, int difficulty)
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

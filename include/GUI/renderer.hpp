// renderer.hpp

#ifndef RENDERER_HPP
#define RENDERER_HPP

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <iostream>
#include <cmath>
#include <stdexcept>

class Renderer {
public:
    Renderer(SDL_Window* win);
    ~Renderer();
    
    void cleanUp();
    void createRenderer();
    int getTextHeight(TTF_Font* font);
    void getTextSize(TTF_Font* font, const char* text, int* width, int* height);
    void render(SDL_Texture* texture, SDL_Rect* dest);
    SDL_Texture* getTexture(const char* filename);
    void clearRender();
    void update();
    void renderCircle(int centerX, int centerY, int radius);
    void renderLine(int x1, int y1, int x2, int y2, int lineThickness);
    void renderRect(SDL_Rect rect);
    void renderRectFilled(SDL_Rect rect, SDL_Color border, SDL_Color inside);
    TTF_Font* openFont(const char* file, int size);
    int renderFont(TTF_Font* font, const char* text, SDL_Color color, int x, int y);
    void renderHangman(int incorrectGuesses, int difficulty);

private:
    SDL_Window* win;
    SDL_Renderer* ren;
    SDL_Texture** textures;
    TTF_Font** fonts;
    int numTextures;
    int numFonts;
};

#endif

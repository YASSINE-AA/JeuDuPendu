#ifndef TEXTBOX_HPP
#define TEXTBOX_HPP
#include "renderer.hpp"
#include "states.hpp"

class TextBox
{
public:
    int x, y;
    TextBox(Renderer renderer, States states, TTF_Font *font, std::string text, std::string placeholder, int x, int y) : renderer(renderer), states(states), font(font), text(text), placeholder(placeholder), x(x), y(y) {}
    void render();
    void setPlaceHolder(std::string placeholder);
    void setText(std::string text);
    std::string getText();
    void handleEvents(SDL_Event e);

private:
    Renderer renderer;
    States states;
    TTF_Font *font;
    SDL_Rect dimensions;
    std::string text;
    std::string placeholder;
    int textWidth;
};
#endif
#include "textBox.hpp"

void TextBox::setPosition(int newX, int newY)
{
    x = newX;
    y = newY;
}

std::string TextBox::getText() {
    return text;
}

void TextBox::render()
{
    renderer.renderRectFilled({x, y, 185, 28}, {0, 0, 0, 255}, {240, 240, 240, 255}); // render shape

    // render placeholder
    if (text == "")
        renderer.renderFont(font, (const char *)placeholder.c_str(), {170, 170, 170}, x + 5, y + 0.5);
    else
    {
        textWidth = renderer.renderFont(font, (const char *)text.c_str(), {0, 0, 0}, x + 5, y + 0.5);
    }
}

void TextBox::handleEvents(SDL_Event &e)
{
    // backspace
    if (e.type == SDL_KEYDOWN)
    {
        if (e.key.keysym.sym == SDLK_BACKSPACE)
        {
            if (text != "")
                text.pop_back();
        }
        else
        {
            char c = states.convertSDLKeyToChar(e.key.keysym.sym);
            if (c != '\0' && textWidth < 170)
                text.push_back(c);
        }
    }
}
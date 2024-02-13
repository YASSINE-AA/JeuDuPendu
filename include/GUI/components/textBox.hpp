#ifndef TEXTBOX_HPP
#define TEXTBOX_HPP

#include "customComponent.hpp"

class TextBox : public CustomComponent {
public:
    TextBox(Renderer &renderer, States &states, TTF_Font *font, std::string text, std::string placeholder, int x, int y)
        : CustomComponent(renderer, states), font(font), text(text), placeholder(placeholder), x(x), y(y) {}

    void render() override;
    void setPlaceHolder(std::string placeholder);
    
    void setText(std::string text);
    void setPosition(int x, int y) override;
    std::string getText();
    void handleEvents(SDL_Event& e) override;

private:
    int x, y;
    TTF_Font *font;
    std::string text;
    std::string placeholder;
    int textWidth;
};

#endif

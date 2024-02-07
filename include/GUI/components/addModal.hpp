#ifndef ADDMODAL_HPP
#define ADDMODAL_HPP

#include "customComponent.hpp"

#include <vector>

class AddModal : public CustomComponent
{
public:
    AddModal(Renderer &renderer, States &states, Window &window, TTF_Font *&font, TTF_Font *&contentFont, std::string title, std::string content, BinaryTree tree, Dictionary dictionary)
        : CustomComponent(renderer, states), window(window), font(font), contentFont(contentFont), title(title), content(content), tree(tree), dictionary(dictionary)
    {
        std::tie(width, height) = window.getWindowDimensions();
        x = width / 2 - modalW / 2;
        y = height / 2 - modalH / 2;
        addBtnRect = (SDL_Rect){x + 15, y+105, 75, 33};
        deleteBtnRect = (SDL_Rect){x + 100, y+105, 75, 33};
        closeBtnRect = (SDL_Rect){x + 270, y + 5, 20, 20};
    }

    int x, y;
    void render() override;
    void setTitle(std::string t);
    void setContent(std::string c);
    bool isClosed() { return isClosed_; }
    void setVisibilty(bool state) { isClosed_ = !state; }
    void setWord(std::string &word);
    std::string getWord() { return word; };
    void setPosition(int x, int y) override {} // fix this
    void sendSubmit()
    {
        isSubmitSent_ = true;
    }

    bool getSubmit() {return isSubmitSent_;} 
    void resetSubmit() {isSubmitSent_ = false;}
    void handleEvents(SDL_Event e) override;

private:
    BinaryTree tree;
    bool isSubmitSent_ = false;
    Dictionary dictionary;
    std::string word;
    int width, height;
    bool isClosed_ = true;
    Window window;
    TTF_Font *font;
    TTF_Font *contentFont;
    SDL_Rect deleteBtnRect;
    SDL_Rect addBtnRect;
    SDL_Rect closeBtnRect;
    int modalW = 300;
    int modalH = 160;
    int contentYOffset = 0;
    int contentXOffset = 0;
    std::string title;
    std::string content;
};

#endif

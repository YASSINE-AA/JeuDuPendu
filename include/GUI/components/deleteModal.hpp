#ifndef DELETEMODAL_HPP
#define DELETEMODAL_HPP

#include "renderer.hpp"
#include "states.hpp"
#include "window.hpp"
#include "binary_tree.hpp"
#include "customComponent.hpp"

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <functional>
#include <string>

class DeleteModal : public CustomComponent {
public:
    using SubmitCallback = std::function<void()>;

    DeleteModal(Renderer& renderer, States& states, Window& window, TTF_Font*& font, TTF_Font*& contentFont, std::string title, std::string content, BinaryTree tree, Dictionary dictionary);

    void render() override;
    void setTitle();
    void setContent(const std::string& c);
    bool isClosed() const { return isClosed_; }
    void setVisibility(bool state);
    SDL_Rect getDimensions() const { return dimensions; }
    void setWord(const std::string& word);
    std::string getWord() const { return word; };
    void setPosition(int x, int y) override; // Implement this method

    void sendSubmit();

    void setSubmitCallback(const SubmitCallback& callback);

    void handleEvents(SDL_Event& e) override;

private:
    void initializePosition();
    void initializeButtonRects();
    int x, y;
    BinaryTree tree;
    Dictionary dictionary;
    std::string word;
    int width, height;
    bool isClosed_ = true;
    Window window;
    TTF_Font* font;
    TTF_Font* contentFont;
    SDL_Rect deleteBtnRect;
    SDL_Rect addBtnRect;
    SDL_Rect closeBtnRect;
    SDL_Rect dimensions;
    int modalW = 300;
    int modalH = 160;
    int contentYOffset = 0;
    int contentXOffset = 0;
    std::string title;
    std::string content;
    SubmitCallback submitCallback_;
};

#endif

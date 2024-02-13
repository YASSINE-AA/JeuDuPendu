#include "deleteModal.hpp"
DeleteModal::DeleteModal(Renderer &renderer, States &states, Window &window, TTF_Font *&font, TTF_Font *&contentFont, std::string title, std::string content, BinaryTree tree, Dictionary dictionary)
    : CustomComponent(renderer, states), window(window), font(font), contentFont(contentFont), title(title), content(content), tree(tree), dictionary(dictionary)
{
    std::tie(width, height) = window.getWindowDimensions();
    initializePosition();
    initializeButtonRects();
}

void DeleteModal::setPosition(int x, int y)
{
}

void DeleteModal::setVisibility(bool state)
{
    isClosed_ = !state;
}

void DeleteModal::sendSubmit()
{
    if (submitCallback_)
        submitCallback_();
}

void DeleteModal::setSubmitCallback(const SubmitCallback &callback)
{
    submitCallback_ = callback;
}

void DeleteModal::initializePosition()
{
    int windowWidth, windowHeight;
    std::tie(windowWidth, windowHeight) = window.getWindowDimensions();
    x = windowWidth / 2 - modalW / 2;
    y = windowHeight / 2 - modalH / 2;
    dimensions = {x, y, modalW, modalH};
}

void DeleteModal::initializeButtonRects()
{
    initializePosition();
    addBtnRect = {x + 15, y + 105, 75, 33};
    deleteBtnRect = {x + 100, y + 105, 75, 33};
    closeBtnRect = {x + 270, y + 5, 20, 20};
}
void DeleteModal::render()
{
    if (!isClosed())
    {
        renderer.renderRectFilled(dimensions, {0, 0, 0, 255}, {240, 240, 240, 255});
        renderer.renderFont(font, title.c_str(), {0, 0, 0}, x + 15, y + 25);
        renderer.renderFont(contentFont, content.c_str(), {0, 0, 0}, x + 15, y + 70);
        renderer.render(renderer.getTexture("assets/close.png"), &closeBtnRect);
        renderer.render(renderer.getTexture("assets/submit.bmp"), &deleteBtnRect);
        renderer.render(renderer.getTexture("assets/cancel.bmp"), &addBtnRect);
    }
}

void DeleteModal::setWord(const std::string &w)
{
    word = w;
}

void DeleteModal::setContent(const std::string &c)
{
    content = c;
}
void DeleteModal::handleEvents(SDL_Event &e)
{
    if (e.type == SDL_MOUSEBUTTONDOWN)
    {

        int mouseX, mouseY;
        states.getMousePosition(&mouseX, &mouseY);

        if (states.isBtnArea(mouseX, mouseY, closeBtnRect))
        {
            // Close button clicked
            std::cout << "called" << std::endl;
            setVisibility(false);
        }
        else if (states.isBtnArea(mouseX, mouseY, deleteBtnRect) && !isClosed_)
        {

            sendSubmit(); // Call submit callback
            setVisibility(false);
        }
        else if (states.isBtnArea(mouseX, mouseY, addBtnRect) && !isClosed_)
        {
            // Add button clicked
            // setVisibility(false);
        }
    }
}

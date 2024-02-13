#include "addModal.hpp"

void AddModal::initializePosition()
{
    std::tie(width, height) = window.getWindowDimensions();
    x = width / 2 - modalW / 2;
    y = height / 2 - modalH / 2;
}

void AddModal::initializeButtonRects()
{
    addBtnRect = (SDL_Rect){x + 15, y + 145, 75, 33};
    deleteBtnRect = (SDL_Rect){x + 100, y + 145, 75, 33};
    closeBtnRect = (SDL_Rect){x + 270, y + 5, 20, 20};
    dimensions = {x, y, modalW, modalH};
}

// Constructors
AddModal::AddModal(Renderer &renderer, States &states, Window &window, TTF_Font *&font, TTF_Font *&contentFont, std::string title, std::string content, BinaryTree tree, Dictionary dictionary)
    : CustomComponent(renderer, states), window(window), font(font), contentFont(contentFont), title(title), content(content), tree(tree), dictionary(dictionary), textBox(TextBox(renderer, states, font, "", "ex: help", 115, 300))
{
    initializePosition();
    initializeButtonRects();
}

// Render method
void AddModal::render()
{
    if (!isClosed())
    {
        // render frame
        renderer.renderRectFilled({x, y, modalW, modalH}, {0, 0, 0, 255}, {240, 240, 240, 255});

        // render title and content
        renderer.renderFont(font, (const char *)title.c_str(), (SDL_Color){0, 0, 0}, x + 15, y + 25);

        // render textbox
        textBox.render();

        renderer.renderFont(contentFont, (const char *)content.c_str(), (SDL_Color){0, 0, 0}, x + 15, y + 70);
        renderer.render(renderer.getTexture("assets/close.png"), &closeBtnRect);
        renderer.render(renderer.getTexture("assets/submit.bmp"), &deleteBtnRect);
        renderer.render(renderer.getTexture("assets/cancel.bmp"), &addBtnRect);
    }
}

// Setter methods
void AddModal::setTitle(const std::string &t)
{
    title = t;
}

void AddModal::setContent(const std::string &c)
{
    content = c;
}

void AddModal::setVisibility(bool state)
{
    isClosed_ = !state;
}

void AddModal::setWord(const std::string &w)
{
    word = w;
}

// Getter methods
bool AddModal::isClosed() const
{
    return isClosed_;
}

SDL_Rect AddModal::getDimensions() const
{
    return dimensions;
}

std::string AddModal::getWord() const
{
    return word;
}

std::string AddModal::getTextBoxValue()
{
    return textBox.getText();
}

void AddModal::sendUpdate()
{
    updateListBox = true;
}

void AddModal::resetUpdate()
{
    updateListBox = false;
}

bool AddModal::getUpdate() {
    return updateListBox;
}

void AddModal::handleEvents(SDL_Event &e)
{
    textBox.handleEvents(e);

    if (e.type == SDL_MOUSEBUTTONDOWN && !isClosed())
    {
        int mouseX, mouseY;
        states.getMousePosition(&mouseX, &mouseY);

        if (states.isBtnArea(mouseX, mouseY, closeBtnRect))
        {
            setVisibility(false);
        }
        else if (states.isBtnArea(mouseX, mouseY, deleteBtnRect) && !isClosed_)
        {
            addWordCallback(*this, tree, dictionary);
            setVisibility(false);
        }
        else if (states.isBtnArea(mouseX, mouseY, addBtnRect) && !isClosed_)
        {
            setVisibility(false);
        }
    }
}

void AddModal::setPosition(int x, int y)
{
    // Implementation of setPosition method
}

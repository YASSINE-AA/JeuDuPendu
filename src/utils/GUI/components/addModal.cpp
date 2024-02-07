#include "addModal.hpp"

void AddModal::render()
{
    if (!isClosed())
    {
        // render frame
        renderer.renderRectFilled({x, y, modalW, modalH}, {0, 0, 0, 255}, {240, 240, 240, 255});

        // render title and content
        renderer.renderFont(font, (const char *)title.c_str(), (SDL_Color){0, 0, 0}, x + 15, y + 25);

        renderer.renderFont(contentFont, (const char *)content.c_str(), (SDL_Color){0, 0, 0}, x + 15, y + 70);
        renderer.render(renderer.getTexture("assets/close.png"), &closeBtnRect);
        renderer.render(renderer.getTexture("assets/submit.bmp"), &deleteBtnRect);
        renderer.render(renderer.getTexture("assets/cancel.bmp"), &addBtnRect);
    }
}

void AddModal::setWord(std::string &w)
{
    word = w;
}

void AddModal::setTitle(std::string t) {
    title = t;
}

void AddModal::setContent(std::string c)
{
    content = c;
}

void AddModal::handleEvents(SDL_Event e)
{

    int mouseX, mouseY;
    states.getMousePosition(&mouseX, &mouseY);

    if (states.isBtnArea(mouseX, mouseY, closeBtnRect))
    {
        setVisibilty(false);
    }
    else if (states.isBtnArea(mouseX, mouseY, deleteBtnRect) && !isClosed_)
    {
        // TODO: delete from tree
        sendSubmit();
        
    }
    else if (states.isBtnArea(mouseX, mouseY, addBtnRect) && !isClosed_)
    {
        resetSubmit();
        setVisibilty(false);
    }
}
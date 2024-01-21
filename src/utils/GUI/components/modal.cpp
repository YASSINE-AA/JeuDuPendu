#include "modal.hpp"

void Modal::render()
{
    // render frame
    renderer.renderRectFilled({x, y, modalW, modalH}, {0, 0, 0, 255}, {240, 240, 240, 255});

    // render title and content
    renderer.renderFont(font, (const char *)title.c_str(), (SDL_Color){0, 0, 0}, x + 15, y + 25);

    // TODO! Implement a simple word wrapping mechanism for longer texts.
    renderer.renderFont(contentFont, (const char *)content.c_str(), (SDL_Color){0, 0, 0}, x + 15, y + 70);
    textBox.setPosition(x + 15, y + 100);
    textBox.render();

    renderer.render(renderer.getTexture("assets/delete.bmp"), &deleteBtnRect);
    renderer.render(renderer.getTexture("assets/push.bmp"), &addBtnRect);
}
void Modal::handleEvents(SDL_Event e)
{
    if (e.type == SDL_KEYDOWN)
    {
        textBox.handleEvents(e);
    }
    else if (e.type == SDL_MOUSEBUTTONDOWN)
    {
        int mouseX, mouseY;
        states.getMousePosition(&mouseX, &mouseY);

        if (states.isBtnArea(mouseX, mouseY, addBtnRect))
        {
            std::string word = textBox.getText();
            pushItemToListBox(word);

        }
        else if (states.isBtnArea(mouseX, mouseY, deleteBtnRect))
        {
            // TODO: Implement deletion logic if needed
        }
    }
}
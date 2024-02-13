#ifndef ADDMODAL_HPP
#define ADDMODAL_HPP

#include "customComponent.hpp"
#include "textBox.hpp"

#include <vector>

class AddModal : public CustomComponent
{
public:
    typedef std::function<void(AddModal &, BinaryTree &, Dictionary &)> CallbackFunction;

    AddModal(Renderer &renderer, States &states, Window &window, TTF_Font *&font, TTF_Font *&contentFont, std::string title, std::string content, BinaryTree tree, Dictionary dictionary);

    void setAddWordCallback(CallbackFunction callback)
    {
        addWordCallbackFunction = callback;
    }



    void addWordCallback(AddModal &addModal, BinaryTree &tree, Dictionary &dictionary)
    {
        if (addWordCallbackFunction)
        {
            addWordCallbackFunction(addModal, tree, dictionary);
        }
    }
    // Render method
    void render() override;

    // Setter methods
    void setTitle(const std::string &t);
    void setContent(const std::string &c);
    void setVisibility(bool state);
    void setWord(const std::string &word);

    // Getter methods
    bool isClosed() const;
    SDL_Rect getDimensions() const;
    std::string getWord() const;
    std::string getTextBoxValue();

    // Other methods
    void sendSubmit();
    void sendUpdate();
    void resetUpdate();
    bool getUpdate();
    void handleEvents(SDL_Event &e) override;
    void setPosition(int x, int y) override;

private:
    // Private helper methods
    void initializePosition();
    void initializeButtonRects();

    // Member variables
    int x, y;
    BinaryTree tree;
    TextBox textBox;
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
    SDL_Rect dimensions;
    int modalW = 300;
    int modalH = 200;
    int contentYOffset = 0;
    int contentXOffset = 0;
    std::string title;
    std::string content;
    CallbackFunction addWordCallbackFunction;
    bool updateListBox = false;
};

#endif
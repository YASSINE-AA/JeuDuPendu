#include <iostream>
#include <iomanip>
#include <vector>
#include <forward_list>
#include "dictionary.hpp"
#include "binary_tree.hpp"
#include "game.hpp"
#include <stdio.h>
#include <stdlib.h>
#include "gui.hpp"
#include <SDL2/SDL.h>

using namespace std;

int main()
{
    GUI gui = GUI();
    gui.init();
    int width = 500;
    int height = 600;
    gui.createWindow(0, 0, width, height);
    gui.createRenderer();
    TTF_Font *titleFont = gui.openFont("assets/fonts/cedarville.ttf", 56);
    SDL_Rect titleRect = {10, 10, 26, 26};
    cout << (width / 2) - 50 << endl;
    SDL_Rect startRect = {width / 2 - 100, height / 2 - 120, 194, 82};
    SDL_Rect quitRect = {width / 2 - 100, height / 2, 194, 82};

    bool loadMainMenu = true;
    bool loadGame = false;
    while (true)
    {
        gui.clearRender();

        gui.render(gui.getTexture("assets/bg.bmp"), NULL);
        if (loadMainMenu)
        {
            gui.renderFont(titleFont, "Hangman!", (SDL_Color){0, 0, 0}, 140, 40);
            gui.render(gui.getTexture("assets/start.bmp"), &startRect);
            gui.render(gui.getTexture("assets/quit.bmp"), &quitRect);
        }
        else if (loadGame)
        {
            gui.renderFont(titleFont, "____", (SDL_Color){0, 0, 0}, 140, 40);
        }

        gui.update();
        gui.handleEvents(loadMainMenu, loadGame);
    }
    return EXIT_SUCCESS;
}

/*


    Dictionary dict = Dictionary("dict.txt");
    BinaryTree tree = BinaryTree(dict.allWords);
    string randomWord = dict.getRandomWord();
    Game game = Game(randomWord, tree);
    cout << "word is: " << randomWord << endl;
    char userGuess;
    while (!game.isGameOver() && !game.isGameWon())
    {
        cout << "Guess character: ";
        cin >> userGuess;
        game.guessLetter(userGuess);
    }

    game.displayWord();
*/
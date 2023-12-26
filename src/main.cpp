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
    Dictionary dictionary = Dictionary("dict.txt");
    BinaryTree tree = BinaryTree(dictionary.allWords);
    string randomWord = dictionary.getRandomWord();
    string placeholder = randomWord;
    for (char &c : placeholder)
    {
        c = '_';
    }

    Game game = Game(randomWord, tree);
    cout << randomWord << endl;
    GUI gui = GUI();
    gui.init();
    int width = 500;
    int height = 600;
    gui.createWindow(0, 0, width, height);
    gui.createRenderer();
    TTF_Font *titleFont = gui.openFont("assets/fonts/pacifico.ttf", 56);
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
        else if (game.isGameOver() || game.isGameWon())
        {
            loadGame = false;
            char *msg;
            if (game.isGameOver())
                msg = (char *)"You have lost!";
            else
                msg = (char *)"You have won!";
            gui.renderFont(titleFont, msg, (SDL_Color){0, 0, 0}, 100, 40);
        }

        else if (loadGame)
        {
            TTF_SetFontSize(titleFont, 34);
            gui.renderFont(titleFont, ("Wrong Guesses: " + std::to_string(game.incorrectGuesses)).c_str(), (SDL_Color){1, 0, 0}, 100, 180);
            TTF_SetFontSize(titleFont, 54);

            gui.renderFont(titleFont, (char *)placeholder.c_str(), (SDL_Color){0, 0, 0}, 100, 40);
        }

        SDL_Event event;
        while (SDL_PollEvent(&event))
        {
            if (event.type == SDL_QUIT)
            {
                gui.cleanUp();
            }
            else if (event.type == SDL_MOUSEBUTTONDOWN)
            {

                int x;
                int y;
                gui.getMousePosition(&x, &y);
                if (gui.isQuitBtnArea(x, y))
                {
                    gui.cleanUp();
                }
                else if (gui.isStartBtnArea(x, y))
                {
                    loadGame = true;
                    loadMainMenu = false;
                }
            }
            else if (event.type == SDL_KEYDOWN)
            {

                char pressedChar = gui.convertSDLKeyToChar(event.key.keysym.sym);

                if (pressedChar != '\0')
                {

                    if (loadGame)
                    {
                        vector<int> pos = game.guessLetter(pressedChar);

                        for (int p : pos)
                        {
                            placeholder[p] = pressedChar;
                        }
                    }
                }
            }
        }
        gui.update();
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
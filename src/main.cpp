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
    string placeholder;
    Game game = Game(tree);
    GUI gui = GUI();
    gui.init();
    int width = 500;
    int height = 600;
    gui.createWindow(0, 0, width, height);
    gui.createRenderer();
    TTF_Font *titleFont = gui.openFont("assets/fonts/pacifico.ttf", 56);
    cout << (width / 2) - 50 << endl;
    SDL_Rect startRect = {width / 2 - 100, height / 2 - 120, 194, 82};
    SDL_Rect menuRect = {10, 10, 36, 36};
    SDL_Rect quitRect = {width / 2 - 100, height / 2, 194, 82};
    bool loadMainMenu = true;
    bool loadGame = false;
    bool gameFinished = false;

    while (true)
    {
        gui.clearRender();

        gui.render(gui.getTexture("assets/bg.bmp"), NULL);
        if (loadMainMenu)
        {
            TTF_SetFontSize(titleFont, 54);

            gui.renderFont(titleFont, "Hangman! v1.0", (SDL_Color){0, 0, 0}, 110, 38);
            TTF_SetFontSize(titleFont, 24);

            gui.renderFont(titleFont, "Created by Yassine Ahmed Ali", (SDL_Color){0, 0, 0}, 110, 520);

            gui.render(gui.getTexture("assets/start.bmp"), &startRect);
            gui.render(gui.getTexture("assets/quit.bmp"), &quitRect);
        }
        else if (gameFinished)
        {
            loadGame = false;
            char *msg;
            if (game.isGameOver())
            {
                msg = (char *)"You have lost!";
                TTF_SetFontSize(titleFont, 30);

                gui.renderFont(titleFont, (char *)((string) "The word was: " + (string)game.wordToGuess).c_str(), (SDL_Color){0, 0, 0}, 120, 340);
            }

            else
                msg = (char *)"You have won!";
            TTF_SetFontSize(titleFont, 54);

            gui.renderFont(titleFont, msg, (SDL_Color){0, 0, 0}, 100, 40);
            TTF_SetFontSize(titleFont, 34);
            gui.renderFont(titleFont, "Want to play again?", (SDL_Color){0, 0, 0}, 120, 130);
            SDL_Rect playAgainRect = startRect;
            playAgainRect.y += 50;
            playAgainRect.x += 20;
            gui.render(gui.getTexture("assets/start.bmp"), &playAgainRect);
            gui.render(gui.getTexture("assets/menu.bmp"), &menuRect);
        }

        else if (loadGame)
        {
            TTF_SetFontSize(titleFont, 34);
            gui.renderFont(titleFont, ("Wrong Guesses: " + std::to_string(game.incorrectGuesses)).c_str(), (SDL_Color){1, 0, 0}, 100, 180);
            TTF_SetFontSize(titleFont, 54);

            gui.renderFont(titleFont, (char *)placeholder.c_str(), (SDL_Color){0, 0, 0}, 100, 40);
            gui.renderHangman(game.incorrectGuesses);
            gameFinished = game.isGameOver() || game.isGameWon();
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
                cout << x << endl;
                cout << y << endl;
                if (!gameFinished && !loadGame)
                {
                    if (gui.isStartBtnArea(x, y))
                    {
                        game.reset();

                        string randomWord = dictionary.getRandomWord();
                        game.setWord(randomWord);
                        cout << randomWord << endl;
                        placeholder = randomWord;
                        for (char &c : placeholder)
                        {
                            c = '_';
                        }
                        loadGame = true;
                        loadMainMenu = false;
                    }
                    else if (gui.isQuitBtnArea(x, y))
                    {
                        gui.cleanUp();
                    }
                }

                else if (gameFinished && !loadGame)
                {
                    if (gui.isPlayAgainBtnArea(x, y))
                    {
                        game.reset();
                        gameFinished = false;
                        string randomWord = dictionary.getRandomWord();
                        game.setWord(randomWord);
                        cout << randomWord << endl;
                        placeholder = randomWord;
                        for (char &c : placeholder)
                        {
                            c = '_';
                        }
                        loadGame = true;
                    }
                    else if (gui.isGoBackToMenuArea(x, y))
                    {
                        gameFinished = false;
                        loadGame = false;
                        loadMainMenu = true;
                    }
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

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

string startNewGame(Game &game, Dictionary dictionary)
{
    game.reset();
    string randomWord = dictionary.getRandomWord();
    game.setWord(randomWord);
    return randomWord;
}

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
    SDL_Rect settingsRect = {width / 2 - 100, height / 2 -20, 194, 82};
    SDL_Rect quitRect = {width / 2 - 100, height / 2 + 80, 194, 82};
    SDL_Rect muteUnmuteRect = {10, 10, 36, 36};
    SDL_Rect playAgainRect = startRect;
    playAgainRect.y += 50;
    playAgainRect.x += 20;
    bool loadMainMenu = true;
    bool loadGame = false;
    bool gameFinished = false;
    gui.openAudio();
    gui.playMusic(gui.loadMusic("assets/bg.wav"), 20);

    while (true)
    {
        gui.clearRender();

        gui.render(gui.getTexture("assets/bg.bmp"), NULL);
        if (!loadMainMenu)
        {
            gui.render(gui.getTexture("assets/menu.bmp"), &menuRect);
            muteUnmuteRect.x = 60;
            gui.render(gui.getTexture("assets/mute.bmp"), &muteUnmuteRect);
        }

        if (loadMainMenu)
        {
            muteUnmuteRect.x = 10;
            gui.render(gui.getTexture("assets/mute.bmp"), &muteUnmuteRect);

            TTF_SetFontSize(titleFont, 54);

            gui.renderFont(titleFont, "Hangman! v1.0", (SDL_Color){0, 0, 0}, 110, 38);
            TTF_SetFontSize(titleFont, 24);

            gui.renderFont(titleFont, "Created by Yassine Ahmed Ali", (SDL_Color){0, 0, 0}, 110, 520);

            gui.render(gui.getTexture("assets/start.bmp"), &startRect);
            gui.render(gui.getTexture("assets/settings.bmp"), &settingsRect);
            gui.render(gui.getTexture("assets/quit.bmp"), &quitRect);
        }
        else if (gameFinished)
        {
            if (loadGame)
                SDL_Delay(1000);

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

            gui.render(gui.getTexture("assets/start.bmp"), &playAgainRect);
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
                if (gui.isBtnArea(x, y, muteUnmuteRect))
                {
                    gui.playAudioChannel(gui.loadWAV("assets/click.mp3"));
                    if (!gui.isMusicPaused())
                    {
                        gui.pauseMusic();
                    }
                    else
                    {
                        gui.resumeMusic();
                    }
                }

                if (!loadMainMenu)
                {
                    if (gui.isBtnArea(x, y, menuRect))
                    {

                        gui.playAudioChannel(gui.loadWAV("assets/click.mp3"));

                        gameFinished = false;
                        loadGame = false;
                        loadMainMenu = true;
                        game.reset();
                    }
                }
                if (!gameFinished && !loadGame)
                {
                    if (gui.isBtnArea(x, y, startRect))
                    {
                        gui.playAudioChannel(gui.loadWAV("assets/click.mp3"));
                        placeholder = startNewGame(game, dictionary);

                        for (char &c : placeholder)
                        {
                            c = '_';
                        }
                        loadGame = true;
                        loadMainMenu = false;
                    }
                    else if (gui.isBtnArea(x, y, quitRect))
                    {
                        gui.playAudioChannel(gui.loadWAV("assets/click.mp3"));
                        SDL_Delay(1000);
                        gui.cleanUp();
                    }
                }

                else if (gameFinished && !loadGame)
                {
                    if (gui.isBtnArea(x, y, playAgainRect))
                    {
                        gui.playAudioChannel(gui.loadWAV("assets/click.mp3"));

                        gameFinished = false;
                        placeholder = startNewGame(game, dictionary);
                        for (char &c : placeholder)
                        {
                            c = '_';
                        }
                        loadGame = true;
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

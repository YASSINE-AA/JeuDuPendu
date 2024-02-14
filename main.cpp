#include <iostream>
#include <iomanip>
#include <vector>
#include <forward_list>
// Custom Components
#include "listBox.hpp"
#include "textBox.hpp"
#include "deleteModal.hpp"
#include "game.hpp"
#include <stdio.h>
#include <stdlib.h>
#include "gui.hpp"
#include "audio.hpp"
#include "renderer.hpp"
#include "window.hpp"
#include "states.hpp"

using namespace std;

bool startNewGame(Game &game, Dictionary dictionary, string &placeholder, vector<string> &visited, int difficulty)
{
    game.reset();
    game.setDifficulty(difficulty);
    int borneMin;
    int borneMax;
    switch (difficulty)
    {
    case 0:
        borneMin = 3;
        borneMax = 5;
        break;

    case 1:
        borneMin = 5;
        borneMax = 6;
        break;

    case 2:
        borneMin = 6;
        borneMax = 10;
        break;

    default:
        break;
    }
    string randomWord = game.wordTree.getRandomWord(borneMin, borneMax, visited);
    std::cout << randomWord << std::endl;
    if (randomWord != "#")
    {
        placeholder = randomWord;
        for (char &c : placeholder)
        {
            c = '_';
        }
        game.setWord(randomWord);
        return true;
    }
    else
    {
        return false;
    }
}

int main()
{

    // Flags
    bool loadMainMenu = true;
    bool loadGame = false;
    bool gameFinished = false;
    bool loadSettings = false;
    bool loadOptions = false;

    bool mouseWheelTouched = false;
    bool renderModal = false;

    // Game Init
    int difficulty = 0;
    int streak = 0;
    int score = 0;
    vector<string> visited = {};
    Dictionary dictionary = Dictionary();
    std::string currentTheme = dictionary.getTheme();
    std::cout << currentTheme << std::endl;
    BinaryTree tree = BinaryTree(dictionary.allWords);
    string placeholder;
    Game game = Game(tree, difficulty);

    int offset = 0;
    int multiplier = 1;

    // GUI Init
    GUI gui = GUI();
    Audio audio = Audio();
    Window window = Window();
    States states = States();
    gui.init();
    // gui.initAudio();
    gui.initRenderer();
    int width = 500;
    int height = 600;
    int listPos = 110;
    int listSize = dictionary.allWords.size() * 40;
    window.createWindow(0, 0, width, height);
    Renderer renderer = Renderer(window.getWindow());
    renderer.createRenderer();
    TTF_Font *titleFont = renderer.openFont("assets/fonts/pacifico.ttf", 56);
    TTF_Font *normalFont = renderer.openFont("assets/fonts/roboto.ttf", 24);
    TTF_Font *contentFont = renderer.openFont("assets/fonts/roboto.ttf", 14);

    const char *mutePath = "assets/mute.bmp";

    // Rect
    SDL_Rect startRect = {width / 2 - 90, height / 2 - 120, 194, 82};
    SDL_Rect menuRect = {10, 10, 36, 36};
    SDL_Rect addRect = {450, 10, 36, 36};
    SDL_Rect quitRect = {width / 2 - 90, height / 2 + 100, 194, 82};
    SDL_Rect muteUnmuteRect = {10, 10, 36, 36};
    SDL_Rect playAgainRect = startRect;
    SDL_Rect easyRect = {160, 150, 180, 85};
    SDL_Rect normalRect = {160, 250, 180, 85};
    SDL_Rect difficultRect = {160, 350, 180, 85};
    SDL_Rect selectionRect = easyRect;
    SDL_Rect confirmRect = {400, 470, 60, 60};
    SDL_Rect optionsRect = {width / 2 - 90, height / 2 - 10, 194, 82};
    SDL_Rect listBounds = {100, 100, 350, 480};
    playAgainRect.y += 50;
    playAgainRect.x += 20;

    // BG Music
    audio.openAudio();
    audio.playMusic(audio.loadMusic("assets/bg.mp3"), 20);

    // Custom components
    ListBox listBox = ListBox(renderer, states, window, normalFont, contentFont, dictionary, tree, listBounds, 40);

    // Sounds
    Mix_Chunk *clickChunk = audio.loadWAV("assets/click.mp3");

    while (true)
    {
        renderer.clearRender();

        renderer.render(renderer.getTexture("assets/bg.bmp"), NULL);
        if (!loadMainMenu)
        {
            renderer.render(renderer.getTexture("assets/menu.bmp"), &menuRect);
            muteUnmuteRect.x = 60;
            renderer.render(renderer.getTexture(mutePath), &muteUnmuteRect);
        }

        if (loadMainMenu)
        {
            muteUnmuteRect.x = 10;
            renderer.render(renderer.getTexture(mutePath), &muteUnmuteRect);

            TTF_SetFontSize(titleFont, 54);

            renderer.renderFont(titleFont, "Hangman v1.0", (SDL_Color){0, 0, 0}, 110, 38);
            TTF_SetFontSize(titleFont, 24);

            renderer.renderFont(titleFont, "Created by Yassine and Ikram.", (SDL_Color){0, 0, 0}, 110, 520);

            renderer.render(renderer.getTexture("assets/start.bmp"), &startRect);
            renderer.render(renderer.getTexture("assets/options.bmp"), &optionsRect);
            renderer.render(renderer.getTexture("assets/quit.bmp"), &quitRect);
        }
        else if (loadOptions)
        {
            TTF_SetFontSize(titleFont, 30);
            renderer.renderFont(titleFont, "Dictionary", (SDL_Color){0, 0, 0}, 200, 39);

            listBox.render();
        }

        else if (loadSettings)
        {

            TTF_SetFontSize(titleFont, 30);

            renderer.renderFont(titleFont, "Choose the difficulty:", (SDL_Color){0, 0, 0}, 125, 65);

            renderer.render(renderer.getTexture("assets/easy.bmp"), &easyRect);
            renderer.render(renderer.getTexture("assets/normal.bmp"), &normalRect);
            renderer.render(renderer.getTexture("assets/difficult.bmp"), &difficultRect);
            renderer.render(renderer.getTexture("assets/confirm.bmp"), &confirmRect);

            renderer.renderRect(selectionRect);
        }
        else if (gameFinished)
        {
            if (loadGame)
                SDL_Delay(1000);

            loadGame = false;

            const char *msg = ("score: " + std::to_string(score)).c_str();

            TTF_SetFontSize(titleFont, 54);

            renderer.renderFont(titleFont, msg, (SDL_Color){0, 0, 0}, 100, 40);
            TTF_SetFontSize(titleFont, 34);
            renderer.renderFont(titleFont, "Want to play again?", (SDL_Color){0, 0, 0}, 120, 130);

            renderer.render(renderer.getTexture("assets/start.bmp"), &playAgainRect);
        }

        else if (loadGame)
        {

            TTF_SetFontSize(titleFont, 20);

            renderer.renderFont(titleFont, ("Hint: the current theme is " + currentTheme).c_str(), (SDL_Color){255, 0, 0}, 105, 155);
            TTF_SetFontSize(titleFont, 30);
            renderer.renderFont(titleFont, ("Tries left: " + std::to_string(game.maxGuesses - game.incorrectGuesses)).c_str(), (SDL_Color){0, 0, 0}, 130, 10);
            renderer.renderFont(titleFont, ("streak: " + std::to_string(streak)).c_str(), (SDL_Color){0, 0, 0}, 350, 0);
            renderer.renderFont(titleFont, ("score: " + std::to_string(score)).c_str(), (SDL_Color){0, 0, 0}, 350, 25);

            TTF_SetFontSize(titleFont, 34);
            renderer.renderFont(titleFont, ("Wrong Guesses: " + std::to_string(game.incorrectGuesses)).c_str(), (SDL_Color){0, 0, 0}, 100, 190);
            TTF_SetFontSize(titleFont, 54);

            renderer.renderFont(titleFont, (char *)placeholder.c_str(), (SDL_Color){0, 0, 0}, 100, 40);
            renderer.renderHangman(game.incorrectGuesses, difficulty);
            if (game.isGameWon() || game.isGameOver())
            {
                std::cout << "called" << std::endl;

                if (game.isGameWon())
                {
                    streak++;
                    score = streak * 50;
                }
                if (!startNewGame(game, dictionary, placeholder, visited, difficulty))
                {
                    gameFinished = true;
                    loadGame = false;
                    loadMainMenu = false;
                    loadSettings = false;
                    loadOptions = false;
                }
            }
        }

        SDL_Event event;
        while (SDL_PollEvent(&event))
        {
            if (loadOptions)
            {
                listBox.handleEvents(event);
            }
            if (event.type == SDL_QUIT)
            {
                audio.cleanUp();
                renderer.cleanUp();
                gui.destroy();
            }
            else if (event.type == SDL_MOUSEBUTTONDOWN)
            {
                int x;
                int y;
                states.getMousePosition(&x, &y);
                if (states.isBtnArea(x, y, muteUnmuteRect))
                {
                    audio.playAudioChannel(clickChunk);
                    if (!audio.isMusicPaused())
                    {
                        mutePath = "assets/unmute.bmp";
                        audio.pauseMusic();
                    }
                    else
                    {
                        mutePath = "assets/mute.bmp";
                        audio.resumeMusic();
                    }
                }

                if (!loadMainMenu)
                {
                    if (states.isBtnArea(x, y, menuRect))
                    {

                        audio.playAudioChannel(clickChunk);

                        gameFinished = false;
                        loadGame = false;
                        loadMainMenu = true;
                        loadOptions = false;

                        game.reset();
                        streak = 0;
                        score = 0;
                    }
                }
                if (loadMainMenu)
                {
                    if (states.isBtnArea(x, y, startRect))
                    {
                        audio.playAudioChannel(clickChunk);
                        loadOptions = false;
                        loadMainMenu = false;
                        loadSettings = true;
                    }
                    else if (states.isBtnArea(x, y, quitRect))
                    {
                        audio.playAudioChannel(clickChunk);
                        SDL_Delay(1000);
                        audio.cleanUp();
                        renderer.cleanUp();
                        gui.destroy();
                    }

                    else if (states.isBtnArea(x, y, optionsRect))
                    {
                        audio.playAudioChannel(clickChunk);

                        loadOptions = true;
                        loadMainMenu = false;
                        loadSettings = false;
                        loadGame = false;
                    }
                }

                else if (gameFinished && !loadGame)
                {
                    if (states.isBtnArea(x, y, playAgainRect))
                    {
                        audio.playAudioChannel(clickChunk);
                        gameFinished = false;
                        loadGame = true;
                        loadMainMenu = false;
                        loadOptions = false;
                        game.reset();
                        visited.clear();
                        streak = 0;
                        score = 0;
                        startNewGame(game, dictionary, placeholder, visited, difficulty);
                    }
                }
                else if (loadSettings)
                {
                    if (states.isBtnArea(x, y, easyRect))
                    {
                        audio.playAudioChannel(clickChunk);
                        selectionRect = easyRect;
                        difficulty = 0;
                        game.setDifficulty(0);
                    }
                    else if (states.isBtnArea(x, y, normalRect))
                    {
                        audio.playAudioChannel(clickChunk);
                        selectionRect = normalRect;
                        difficulty = 1;
                        game.setDifficulty(1);
                    }
                    else if (states.isBtnArea(x, y, difficultRect))
                    {
                        audio.playAudioChannel(clickChunk);
                        selectionRect = difficultRect;
                        difficulty = 2;
                        game.setDifficulty(2);
                    }
                    else if (states.isBtnArea(x, y, confirmRect))
                    {
                        audio.playAudioChannel(clickChunk);
                        startNewGame(game, dictionary, placeholder, visited, difficulty);
                        streak = 0;
                        score = 0;
                        loadGame = true;
                        loadSettings = false;
                    }
                }
            }
            else if (event.type == SDL_KEYDOWN)
            {
                char pressedChar = states.convertSDLKeyToChar(event.key.keysym.sym);

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
        renderer.update();
    }

    return EXIT_SUCCESS;
}

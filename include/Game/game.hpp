#ifndef GAME_HPP
#define GAME_HPP

#include <string>
#include <iostream>

using namespace std;

class Game
{
private:
    string wordToGuess;
    int maxGuesses;
    int incorrectGuesses;
    int correctGuesses;

public:
    Game(string word) : wordToGuess(word), incorrectGuesses(0), correctGuesses(0), maxGuesses(5) {}

    bool isGameOver() const
    {
        if (incorrectGuesses == maxGuesses)
        {
            cout << "Game over!" << endl;
        }
    }
    bool isGameWon() const
    {
        if (correctGuesses == wordToGuess.length())
        {
            cout << "You have won!" << endl;
        }
    }
    void displayWord() const
    {
        cout << wordToGuess << endl;
    }
    void guessLetter(char character){
        // TODO
    };
};

#endif
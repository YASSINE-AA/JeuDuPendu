#ifndef GAME_HPP
#define GAME_HPP

#include <string>
#include <iostream>

using namespace std;

class Game
{
private:
    string wordToGuess;
    BinaryTree wordTree;
    int maxGuesses;
    int incorrectGuesses;
    int correctGuesses;

public:
    Game(string word, BinaryTree tree) : wordToGuess(word), wordTree(tree), incorrectGuesses(0), correctGuesses(0), maxGuesses(5) {}

    bool isGameOver() const
    {
        if (incorrectGuesses == maxGuesses)
        {
            cout << "Game over!" << endl;
            return true;
        }
        return false;
    }

    bool isGameWon() const
    {
        if (correctGuesses == wordToGuess.length())
        {
            cout << "You have won!" << endl;
            return true;
        }
        return false;
    }

    void displayWord() const
    {
        cout << "The word was: " << wordToGuess << endl;
    }

    void guessLetter(char character)
    {
        vector<int> letterPositions = wordTree.getLetterPosition(character, wordToGuess);
        if (letterPositions.size() > 0)
        {
            cout << "Char in word!" << endl;
            correctGuesses++;
        }
        else
        {
            cout << "Char isn't in word!" << endl;
            incorrectGuesses++;
        }
    };
};

#endif
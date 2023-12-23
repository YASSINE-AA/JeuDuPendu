#ifndef GAME_HPP
#define GAME_HPP

#include <string>
#include <iostream>
#include <set>

using namespace std;

class Game
{
private:
    string wordToGuess;
    BinaryTree wordTree;
    int maxGuesses;
    int correctGuesses;
    int incorrectGuesses;
    set<char> guessedChars;

public:
    Game(string word, BinaryTree tree) : wordToGuess(word), wordTree(tree), correctGuesses(0), incorrectGuesses(0), maxGuesses(5) {}

    bool isGameOver() const
    {
        if (incorrectGuesses == maxGuesses)
        {
            cout << guessedChars.size() << endl;
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
        if (guessedChars.find(character) == guessedChars.end())
        {
            vector<int> letterPositions = wordTree.getLetterPosition(character, wordToGuess);
            if (letterPositions.size() > 0)
            {
                cout << "Char in word!" << endl;
                correctGuesses += letterPositions.size();

                guessedChars.insert(character);
            }
            else
            {
                cout << "Char isn't in word!" << endl;
                incorrectGuesses++;
            }
        }
        else
        {
            cout << "You have already guessed that word!" << endl;
        }
    };
};

#endif
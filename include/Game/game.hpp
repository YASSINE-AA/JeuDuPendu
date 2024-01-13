#ifndef GAME_HPP
#define GAME_HPP

#include <string>
#include <iostream>
#include <set>

using namespace std;

class Game
{

public:
    string wordToGuess;
    BinaryTree wordTree;
    int maxGuesses;
    int difficulty;
    int correctGuesses;
    int incorrectGuesses;
    set<char> guessedChars;
    Game(BinaryTree tree, int difficulty) : wordTree(tree), correctGuesses(0), incorrectGuesses(0), difficulty(difficulty)
    {
        setDifficulty(difficulty);
    }

    void setWord(string word)
    {
        wordToGuess = word;
    }

    void setDifficulty(int level)
    {
        difficulty = level;
        switch (difficulty)
        {
        case 0:
            // easy
            maxGuesses = 8;

            break;

        case 1:
            // normal
            maxGuesses = 5;

            break;

        case 2:
            // difficult
            maxGuesses = 3;

            break;

        default:
            break;
        }
    }

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

    vector<int> guessLetter(char character)
    {
        if (guessedChars.find(character) == guessedChars.end())
        {
            vector<int> letterPositions = wordTree.getLetterPosition(character, wordToGuess);
            if (letterPositions.size() > 0)
            {
                correctGuesses += letterPositions.size();

                guessedChars.insert(character);
                return letterPositions;
            }
            else
            {
                incorrectGuesses++;
                return {};
            }
        }
        else
        {
            cout << "You have already guessed that word!" << endl;
            return {};
        }
    };

    void reset()
    {
        correctGuesses = 0;
        incorrectGuesses = 0;
        guessedChars.clear();
    }
};

#endif
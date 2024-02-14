#include "game.hpp"

Game::Game(BinaryTree tree, int difficulty) : wordTree(tree), correctGuesses(0), incorrectGuesses(0), difficulty(difficulty)
{
    setDifficulty(difficulty);
}

void Game::setWord(string word)
{
    wordToGuess = word;
}

void Game::setDifficulty(int level)
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

bool Game::isGameOver() const
{
    if (incorrectGuesses == maxGuesses)
    {
        return true;
    }
    return false;
}

bool Game::isGameWon() const
{
    if (correctGuesses == wordToGuess.length())
    {
        return true;
    }
    return false;
}

void Game::displayWord() const
{
    cout << "The word was: " << wordToGuess << endl;
}

vector<int> Game::guessLetter(char character)
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
        return {};
    }
}

void Game::reset()
{
    correctGuesses = 0;
    incorrectGuesses = 0;
    guessedChars.clear();
}

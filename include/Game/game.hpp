#ifndef GAME_HPP
#define GAME_HPP

#include <string>
#include <iostream>
#include <set>
#include "binary_tree.hpp"
#include <gtest/gtest.h> // Include Google Test header

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

    Game(BinaryTree tree, int difficulty);

    void setWord(string word);

    void setDifficulty(int level);

    bool isGameOver() const;

    bool isGameWon() const;

    void displayWord() const;

    vector<int> guessLetter(char character);

    void reset();

};

#endif

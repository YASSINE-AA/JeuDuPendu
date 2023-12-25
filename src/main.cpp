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
    Dictionary dict = Dictionary("dict.txt");
    BinaryTree tree = BinaryTree();
    tree.createFromDict(dict.allWords);
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

    return EXIT_SUCCESS;
}
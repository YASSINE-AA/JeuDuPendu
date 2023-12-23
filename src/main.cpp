#include <iostream>
#include <iomanip>
#include <vector>
#include <forward_list>
#include "dictionary.hpp"
#include "binary_tree.hpp"
#include "game.hpp"

using namespace std;

int main()
{
    BinaryTree tree = BinaryTree();
    Dictionary dictionary = Dictionary("dict.txt");
    string randomWord = dictionary.getRandomWord();
    tree.createFromDict(dictionary.allWords);
    Game game = Game(randomWord, tree);
    cout << "psst, word is " << randomWord << endl;
    char userGuess;
    while(!game.isGameWon() && !game.isGameOver()) {
        cout << "Guess letter: ";
        cin >> userGuess;
        game.guessLetter(userGuess);

    }
    
    

    return 0;
}
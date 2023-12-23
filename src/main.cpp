#include <iostream>
#include <iomanip>
#include <vector>
#include <forward_list>
#include "dictionary.hpp"
#include "binary_tree.hpp"
#include "binary_tree_node.hpp"

using namespace std;

int main()
{
    BinaryTree tree = BinaryTree();
    Dictionary dictionary = Dictionary("dict.txt");

    tree.createFromDict(dictionary.allWords);
    cout << tree.isWordInTree("imperative") << endl;
    tree.deleteWord("imperative");
    cout << tree.isWordInTree("imperative") << endl;

    return 0;
}
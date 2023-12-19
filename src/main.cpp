#include <iostream>
#include <iomanip>
#include <vector>
#include <forward_list>
#include "dictionary.hpp"
#include "binary_tree.hpp"
#include "binary_tree_node.hpp"
#include <SFML/Graphics.hpp>

using namespace std;

void printTree(BinaryTreeNode *root, int space = 0, int count = 5)
{
    if (!root)
        return;

    space += count;

    printTree(root->FD, space, count);

    std::cout << std::setw(space) << root->value << std::endl;

    printTree(root->FG, space, count);
}

int main()
{

     

    BinaryTree tree = BinaryTree();
    vector<int> testVec;
    forward_list<string> dict = Dictionary::readFromFile("dict.txt");
    tree.createFromDict(dict);
    cout << tree.isWordInTree("imperative") << endl;
    return 0;
}
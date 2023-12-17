#include <iostream>
#include <iomanip> 
#include <vector>
#include "utils/BinaryTreeNode/binary_tree_node.h"
#include "utils/BinaryTree/binary_tree.h"

using namespace std;

void printTree(BinaryTreeNode* root, int space = 0, int count = 5) {
    if (!root)
        return;

    space += count;

    printTree(root->FD, space, count); 

    std::cout << std::setw(space) << root->value << std::endl; 

    printTree(root->FG, space, count); 
}

int main()
{
    int lettersFound = 0;
    BinaryTree tree = BinaryTree();
    BinaryTreeNode *root = nullptr;
    string testDict[6] = {"cas", "ces", "ci", "de", "des", "do"};
    root = tree.createBinaryTreeFromDict(testDict, 6);
  
    printTree(root);
    return 0;
}
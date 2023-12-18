#include <iostream>
#include <iomanip> 
#include <vector>
#include "utils/BinaryTreeNode/binary_tree_node.hpp"
#include "utils/BinaryTree/binary_tree.hpp"

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
    vector<int> testVec;
    BinaryTreeNode *root = nullptr;
    string testDict[6] = {"cas", "ces", "ci", "de", "des", "do"};
    root = tree.createBinaryTreeFromDict(testDict, 6);
    testVec = tree.getLetterPosition(root, 'd', (string) "ci");

    for(int v: testVec) {
        cout<<v<<endl;
    }
    //cout << testVec << endl;
    printTree(root);
    return 0;
}
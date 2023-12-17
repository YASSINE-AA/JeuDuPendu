#ifndef BINARY_TREE_H
#define BINARY_TREE_H

#include "../BinaryTreeNode/binary_tree_node.h"
#include <string>
#include <set>
#include <iostream>

using namespace std;

class BinaryTree
{

public:
    BinaryTreeNode *tete;
    BinaryTree() : tete(nullptr) {}
    void insertWord(BinaryTreeNode*& root, string word, int pos);
    BinaryTreeNode *createBinaryTreeFromDict(string dictionary[100], int dictSize);

};

#endif
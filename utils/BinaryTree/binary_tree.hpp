#ifndef BINARY_TREE_H
#define BINARY_TREE_H

#include "../BinaryTreeNode/binary_tree_node.hpp"
#include <string>
#include <set>
#include <iostream>
#include <vector>

using namespace std;

class BinaryTree
{

public:
    BinaryTreeNode *tete;
    BinaryTree() : tete(nullptr) {}
    void insertWord(BinaryTreeNode*& root, string word, int pos=0);
    void deleteWord(BinaryTreeNode *&root, string word, int pos=0);
    vector<int> getLetterPosition(BinaryTreeNode* root, char letter, string codeWord, int pos=0, vector<int>res={});
    BinaryTreeNode *createBinaryTreeFromDict(string dictionary[100], int dictSize);

};

#endif
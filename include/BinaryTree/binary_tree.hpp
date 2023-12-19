#ifndef BINARY_TREE_H
#define BINARY_TREE_H

#include "binary_tree_node.hpp"
#include <string>
#include <set>
#include <iostream>
#include <forward_list>
#include <vector>

using namespace std;

class BinaryTree
{
private:
    BinaryTreeNode* tete;

public:
    BinaryTree() : tete(nullptr) {}
    void insertWord(const string &word) {
        insertWordHelper(tete, word);
    }
    bool isWordInTree(const string &word) {
        return isWordInTreeHelper(tete, word);
    }

    void deleteWord(const string &word) {
        deleteWordHelper(tete, word);
    }
    
    vector<int> getLetterPosition(BinaryTreeNode* root, char letter, const string &codeWord, int pos=0, vector<int>res={});
    BinaryTreeNode *createFromDict(forward_list<string> dictionary);

private:
    void insertWordHelper(BinaryTreeNode *&root, const string &word, int pos=0);
    void deleteWordHelper(BinaryTreeNode *&root, const string &word, int pos=0);
    bool isWordInTreeHelper(BinaryTreeNode *root, const string &word, int pos=0);
};

#endif
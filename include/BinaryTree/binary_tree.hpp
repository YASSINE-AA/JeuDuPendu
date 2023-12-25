#ifndef BINARY_TREE_H
#define BINARY_TREE_H

#include "binary_tree_node.hpp"
#include <string>
#include <set>
#include <iostream>
#include <forward_list>
#include <vector>
#include <iomanip>

using namespace std;

class BinaryTree
{
public:
    BinaryTree() : tete(nullptr) {}
    void insertWord(const string &word)
    {
        insertWordHelper(tete, word);
    }
    bool isWordInTree(const string &word)
    {
        return isWordInTreeHelper(tete, word);
    }

    void deleteWord(const string &word)
    {
        deleteWordHelper(tete, word, tete);
    }

    void printTree()
    {
        printTreeHelper(tete);
    }

    vector<int> getLetterPosition(char letter, const string &codeWord)
    {
        return getLetterPositionHelper(tete, letter, codeWord);
    }

    BinaryTreeNode *createFromDict(vector<string> dictionary);

private:
    BinaryTreeNode *tete;
    void printTreeHelper(BinaryTreeNode *root, int space = 0, int count = 5);
    void insertWordHelper(BinaryTreeNode *&root, const string &word, int pos = 0);
    void deleteWordHelper(BinaryTreeNode *&root, string word, BinaryTreeNode *&nodeToRemove, int pos = 0);
    vector<int> getLetterPositionHelper(BinaryTreeNode *root, char letter, const string &codeWord, int pos = 0, vector<int> res = {});
    bool isWordInTreeHelper(BinaryTreeNode *root, const string &word, int pos = 0);
};

#endif
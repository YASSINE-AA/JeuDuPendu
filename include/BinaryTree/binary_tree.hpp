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
    BinaryTree(vector<string> dictionary) : tete(nullptr)
    {
        createFromDict(dictionary);
    }

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

    string getRandomWord(int minLength, int maxLength)
    {
        return getRandomWordHelper(minLength, maxLength, tete);
    }

    vector<int> getLetterPosition(char letter, const string &codeWord)
    {
        return getLetterPositionHelper(tete, letter, codeWord);
    }

private:
    BinaryTreeNode *tete;
    string getRandomWordHelper(int minLength, int maxLength, BinaryTreeNode *root, string finalWord = "");
    BinaryTreeNode *getRandomCompatibleNode(BinaryTreeNode *node, int minLength, int maxLength, string finalWord);
    int getNumberOfRightChildren(BinaryTreeNode *root, int number = 0);
    int getNumberOfLeftChildren(BinaryTreeNode *root, int number = 0);
    void createFromDict(vector<string> dictionary);
    void printTreeHelper(BinaryTreeNode *root, int space = 0, int count = 5);
    void insertWordHelper(BinaryTreeNode *&root, const string &word, int pos = 0);
    void deleteWordHelper(BinaryTreeNode *&root, string word, BinaryTreeNode *&nodeToRemove, int pos = 0);
    vector<int> getLetterPositionHelper(BinaryTreeNode *root, char letter, const string &codeWord, int pos = 0, vector<int> res = {});
    bool isWordInTreeHelper(BinaryTreeNode *root, const string &word, int pos = 0);
};

#endif
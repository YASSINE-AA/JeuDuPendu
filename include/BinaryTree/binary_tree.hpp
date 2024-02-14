#ifndef BINARY_TREE_H
#define BINARY_TREE_H

#include <string>
#include <set>
#include <iostream>
#include <forward_list>
#include <vector>
#include <iomanip>
#include <algorithm> 

#include "binary_tree_node.hpp" // Include necessary headers outside of the guard

class BinaryTree
{
public:
    BinaryTree(std::vector<std::string> dictionary) : tete(nullptr)
    {
        createFromDict(dictionary);
    }

    void insertWord(const std::string &word);
    bool isWordInTree(const std::string &word);
    void deleteWord(const std::string &word);
    void printTree();
    std::string getRandomWord(int minLength, int maxLength, std::vector<std::string> &visited);
    std::vector<int> getLetterPosition(char letter, const std::string &codeWord);

private:
    BinaryTreeNode *tete;
    std::string getRandomWordHelper(BinaryTreeNode *root, std::string finalWord = "");
    BinaryTreeNode *getRandomCompatibleNode(BinaryTreeNode *node, int minLength, int maxLength, std::string finalWord);
    int getNumberOfRightChildren(BinaryTreeNode *root, int number = 0);
    int getNumberOfLeftChildren(BinaryTreeNode *root, int number = 0);
    void createFromDict(std::vector<std::string> dictionary);
    void printTreeHelper(BinaryTreeNode *root, int space = 0, int count = 5);
    void insertWordHelper(BinaryTreeNode *&root, const std::string &word, int pos = 0);
    void deleteWordHelper(BinaryTreeNode *&root, std::string word, BinaryTreeNode *&nodeToRemove, int pos = 0);
    std::vector<int> getLetterPositionHelper(BinaryTreeNode *root, char letter, const std::string &codeWord, int pos = 0, std::vector<int> res = {});
    bool isWordInTreeHelper(BinaryTreeNode *root, const std::string &word, int pos = 0);
};

#endif

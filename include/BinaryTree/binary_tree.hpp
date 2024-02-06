#ifndef BINARY_TREE_H
#define BINARY_TREE_H

#include "binary_tree_node.hpp"
#include <string>
#include <set>
#include <iostream>
#include <forward_list>
#include <vector>
#include <iomanip>
#include <algorithm> 

class BinaryTree
{
public:
    BinaryTree(std::vector<std::string> dictionary) : tete(nullptr)
    {
        createFromDict(dictionary);
    }

    void insertWord(const std::string &word)
    {
        insertWordHelper(tete, word);
    }
    bool isWordInTree(const std::string &word)
    {
        return isWordInTreeHelper(tete, word);
    }

    void deleteWord(const std::string &word)
    {
        deleteWordHelper(tete, word, tete);
    }

    void printTree()
    {
        printTreeHelper(tete);
    }

    std::string getRandomWord(int minLength, int maxLength, std::vector<std::string> &visited)
    {
        std::string word;
        int tries = 0;
        while (true)
        {
            word = getRandomWordHelper(tete);
            if(word.length() >= minLength && word.length() <= maxLength &&  std::find(visited.begin(), visited.end(), word) == visited.end()) {
                std:: cout << "found" << std::endl;
                visited.push_back(word);
                return word;
            } else {
                tries ++;
                if(tries > 1000) return "#";
            }
        }
    }

    std::vector<int> getLetterPosition(char letter, const std::string &codeWord)
    {
        return getLetterPositionHelper(tete, letter, codeWord);
    }

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
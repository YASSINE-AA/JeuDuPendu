#include "binary_tree.h"

void BinaryTree::insertWord(BinaryTreeNode *&root, string word, int pos = 0)
{
    if (pos == word.length())
    {
        if (root == nullptr)
            root = new BinaryTreeNode('\\0');
        else
        {
            root->FD = new BinaryTreeNode('\\0');
        }
    }
    else if (root == nullptr)
    {
        root = new BinaryTreeNode(word[pos]);
        insertWord(root->FG, word, pos + 1);
    }
    else
    {
        if (root->value < word[pos])
        {
            insertWord(root->FD, word, pos);
        }
        else if (root->value > word[pos])
        {
            BinaryTreeNode *newNode = new BinaryTreeNode(word[pos]);
            newNode->FD = root;
            insertWord(newNode->FG, word, pos + 1);
        }
        else
        {
            insertWord(root->FG, word, pos + 1);
        }
    }
}

BinaryTreeNode *BinaryTree::createBinaryTreeFromDict(string dictionary[100], int dictSize)
{
    BinaryTreeNode *root = nullptr;
    insertWord(root, "cas", 0);
    insertWord(root, "ce", 0);
    insertWord(root, "cees", 0);
    insertWord(root, "ces", 0);

    return root;
}

#include "binary_tree.hpp"

void BinaryTree::insertWord(BinaryTreeNode *&root, string word, int pos)
{
    if (pos == word.length())
    {
        if (root == nullptr)
            root = new BinaryTreeNode('\0');
        else
        {
            root->FD = new BinaryTreeNode('\0');
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
            if (root->FD == nullptr || (root->FD->value > word[pos]))
            {
                BinaryTreeNode *newNode = new BinaryTreeNode(word[pos]);
                newNode->FD = root->FD;
                root->FD = newNode;
                insertWord(newNode->FG, word, pos + 1);
            }
            else
            {
                insertWord(root->FD, word, pos);
            }
        }

        else
        {
            insertWord(root->FG, word, pos + 1);
        }
    }
}

vector<int> BinaryTree::getLetterPosition(BinaryTreeNode *root, char letter, string codeWord, int pos, vector<int> res)
{
    if (root == nullptr)
    {
        cout << "Empty/Invalid tree!" << endl;
        return {};
    }

    if (pos == codeWord.length())
    {
        return res;
    }
    else if (root->value == codeWord[pos])
    {
        if (root->value == letter)
            res.push_back(pos);
        return getLetterPosition(root->FG, letter, codeWord, pos + 1, res);
    }
    else
    {
        return getLetterPosition(root->FD, letter, codeWord, pos, res);
    }
}

BinaryTreeNode *BinaryTree::createBinaryTreeFromDict(string dictionary[100], int dictSize)
{
    BinaryTreeNode *root = nullptr;
    for (int i = 0; i < dictSize; i++)
    {
        insertWord(root, dictionary[i]);
    }
    return root;
}

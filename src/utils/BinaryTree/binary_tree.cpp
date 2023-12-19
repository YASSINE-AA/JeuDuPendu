#include "binary_tree.hpp"

void BinaryTree::insertWordHelper(BinaryTreeNode *&root, const string &word, int pos)
{
    if (pos == word.length())
    {
        if (root == nullptr)
            root = new BinaryTreeNode('\0');
        else
            root->FD = new BinaryTreeNode('\0');
    }
    else if (root == nullptr)
    {
        root = new BinaryTreeNode(word[pos]);
        insertWordHelper(root->FG, word, pos + 1);
    }
    else
    {
        if (word[pos] > root->value)
        {
            if (root->FD == nullptr || root->FD->value > word[pos])
            {
                BinaryTreeNode *newNode = new BinaryTreeNode(word[pos]);
                newNode->FD = root->FD;
                root->FD = newNode;
                insertWordHelper(newNode->FG, word, pos + 1);
            }
            else
            {
                insertWordHelper(root->FD, word, pos);
            }
        }
        else if (word[pos] < root->value)
        {
            BinaryTreeNode *newNode = new BinaryTreeNode(word[pos]);
            newNode->FD = root;
            root = newNode;
            insertWordHelper(newNode->FG, word, pos + 1);
        }
        else
        {
            insertWordHelper(root->FG, word, pos + 1);
        }
    }
}

bool BinaryTree::isWordInTreeHelper(BinaryTreeNode *root, const string &word, int pos)
{
    if (root == nullptr)
    {
        return false;
    }
    else if (pos == word.length())
    {
        if (root->value == '\0')
            return true;
        else
            return false;
    }
    else if (word[pos] == root->value)
    {
        return isWordInTreeHelper(root->FG, word, pos + 1);
    }
    else
    {
        return isWordInTreeHelper(root->FD, word, pos);
    }
}

vector<int> BinaryTree::getLetterPosition(BinaryTreeNode *root, char letter, const string &codeWord, int pos, vector<int> res)
{
    if (root == nullptr)
    {
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

BinaryTreeNode *BinaryTree::createFromDict(forward_list<string> dictionary)
{
    BinaryTreeNode *root = nullptr;
    for (const string &word : dictionary)
    {
        insertWord(word);
    }
}

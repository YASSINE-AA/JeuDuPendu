#include "binary_tree.hpp"


void BinaryTree::printTreeHelper(BinaryTreeNode *root, int space, int count)
{
    if (!root)
        return;

    space += count;

    printTreeHelper(root->FD, space, count);

    std::cout << std::setw(space) << root->value << std::endl;

    printTreeHelper(root->FG, space, count);
}

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

void BinaryTree::deleteWordHelper(BinaryTreeNode *&root, string word, BinaryTreeNode *&nodeToRemove, int pos)
{
    if (root == nullptr)
    {
        cout << "Word is not in tree!" << endl;
    }
    else if (pos == word.length())
    {
        if (root->value == '\0')
        {
            if (root->FD == nullptr)
                nodeToRemove = nullptr;
            else
                root = root->FD;
        }
    }
    else if (word[pos] == root->value)
    {
        deleteWordHelper(root->FG, word, nodeToRemove, pos + 1);
    }
    else if (word[pos] != root->value)
    {
        deleteWordHelper(root->FD, word, root->FD, pos);
    }
}

vector<int> BinaryTree::getLetterPositionHelper(BinaryTreeNode *root, char letter, const string &codeWord, int pos, vector<int> res)
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
        if (root->value == letter) {
res.push_back(pos);
cout << "added " << pos << endl;
        }
            
        return getLetterPositionHelper(root->FG, letter, codeWord, pos + 1, res);
    }
    else
    {
        return getLetterPositionHelper(root->FD, letter, codeWord, pos, res);
    }
}

BinaryTreeNode *BinaryTree::createFromDict(vector<string> dictionary)
{
    BinaryTreeNode *root = nullptr;
    for (const string &word : dictionary)
    {
        insertWord(word);
    }
}

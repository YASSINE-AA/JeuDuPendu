#include "binary_tree.hpp"

void BinaryTree::printTreeHelper(BinaryTreeNode *root, int space, int count)
{
    if (!root)
        return;

    space += count;

    printTreeHelper(root->FD, space, count);

    printTreeHelper(root->FG, space, count);
}

void BinaryTree::insertWordHelper(BinaryTreeNode *&root, const std::string &word, int pos)
{
    if (pos == word.length())
    {
        if (root == nullptr)
            root = new BinaryTreeNode('\0');
        else if (root->value == '\0')
        {
            std::cout << "word already exists! " << word << std::endl;
        }
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

bool BinaryTree::isWordInTreeHelper(BinaryTreeNode *root, const std::string &word, int pos)
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

void BinaryTree::deleteWordHelper(BinaryTreeNode *&root, std::string word, BinaryTreeNode *&nodeToRemove, int pos)
{
    if (root == nullptr)
    {
        std::cout << "Word is not in tree!" << std::endl;
    }
    else if (pos == word.length())
    {
        if (root->value == '\0')
        {
            if (root->FD == nullptr)
            {
                free(nodeToRemove);
                nodeToRemove = nullptr;
            }

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

std::vector<int> BinaryTree::getLetterPositionHelper(BinaryTreeNode *root, char letter, const std::string &codeWord, int pos, std::vector<int> res)
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

        return getLetterPositionHelper(root->FG, letter, codeWord, pos + 1, res);
    }
    else
    {
        return getLetterPositionHelper(root->FD, letter, codeWord, pos, res);
    }
}

int BinaryTree::getNumberOfRightChildren(BinaryTreeNode *root, int number)
{
    if (root == nullptr)
    {
        return number;
    }
    else
    {
        return getNumberOfRightChildren(root->FD, number + 1);
    }
}

int BinaryTree::getNumberOfLeftChildren(BinaryTreeNode *root, int number)
{
    if (root == nullptr)
    {
        return -1;
    }
    else if (root->value == '\0')
    {
        return number;
    }
    else
    {
        return getNumberOfLeftChildren(root->FG, number + 1);
    }
}

std::string BinaryTree::getRandomWordHelper(BinaryTreeNode *root, std::string finalWord)
{

    if (root == nullptr)
    {
        return finalWord;
    }

    else if (root->value == '\0')
    {
        if (root->FD == nullptr)
        {
            return finalWord;
        }
        else
        {
            if (rand() % 2)
                return getRandomWordHelper(root->FD, finalWord);
            else
            {
                return finalWord;
            }
        }
    }
    else
    {
        if (rand() % 2)
        {
            finalWord += root->value;
            return getRandomWordHelper(root->FG, finalWord);
        }
        else
        {
            if (root->FD != nullptr)
                return getRandomWordHelper(root->FD, finalWord);

            finalWord += root->value;
            return getRandomWordHelper(root->FG, finalWord);
        }
    }
}

void BinaryTree::createFromDict(std::vector<std::string> dictionary)
{
    BinaryTreeNode *root = nullptr;
    for (const std::string &word : dictionary)
    {
        insertWord(word);
    }
}

void BinaryTree::insertWord(const std::string &word)
{
    insertWordHelper(tete, word);
}

bool BinaryTree::isWordInTree(const std::string &word)
{
    return isWordInTreeHelper(tete, word);
}

void BinaryTree::deleteWord(const std::string &word)
{
    deleteWordHelper(tete, word, tete);
}

void BinaryTree::printTree()
{
    printTreeHelper(tete);
}

std::string BinaryTree::getRandomWord(int minLength, int maxLength, std::vector<std::string> &visited)
{
    std::string word;
    int tries = 0;
    while (true)
    {
        word = getRandomWordHelper(tete);
        if (word.length() >= minLength && word.length() <= maxLength && std::find(visited.begin(), visited.end(), word) == visited.end())
        {
            visited.push_back(word);
            return word;
        }
        else
        {
            tries++;
            if (tries > 1000)
                return "#";
        }
    }
}

std::vector<int> BinaryTree::getLetterPosition(char letter, const std::string &codeWord)
{
    return getLetterPositionHelper(tete, letter, codeWord);
}
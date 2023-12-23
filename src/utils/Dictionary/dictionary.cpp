#include "dictionary.hpp"

vector<string> Dictionary::readFromFile(const string &filename)
{
    ifstream dictFile(filename);

    if (!dictFile.is_open())
    {
        cerr << "Couldn't open file: " << filename << endl;
        return {};
    }

    vector<string> words;
    string word;

    while (dictFile >> word)
    {
        words.push_back(word);
    }

    return words;
}
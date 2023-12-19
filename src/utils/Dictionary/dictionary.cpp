#include "dictionary.hpp"

forward_list<string> Dictionary::readFromFile(const string &filename)
{
    ifstream dictFile(filename);

    if (!dictFile.is_open())
    {
        cerr << "Couldn't open file: " << filename << endl;
        return {};
    }

    forward_list<string> words;
    string word;

    while (dictFile >> word)
    {
        words.push_front(word);
    }

    return words;
}
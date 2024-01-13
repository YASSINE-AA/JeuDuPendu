#include "dictionary.hpp"

std::vector<std::string> Dictionary::readFromFile(const std::string &filename)
{
    std::ifstream dictFile(filename);

    if (!dictFile.is_open())
    {
        std::cerr << "Couldn't open file: " << filename << std::endl;
        return {};
    }

    std::vector<std::string> words;
    std::string word;

    while (dictFile >> word)
    {
        words.push_back(word);
    }

    return words;
}
#include <string>
#include <iostream>
#include <vector>
#include <fstream>
#include <cstdlib>
#include <algorithm>

class Dictionary
{
public:
    void deleteFromFile(const std::string &filename, const std::string &wordToDelete);
    bool isWordInFile(const std::string &filename, const std::string &wordToCheck);
    void addToFile(const std::string &filename, const std::string &wordToDelete);
    std::vector<std::string> allWords;
    Dictionary(std::string filename)
    {
        srand((unsigned)time(NULL));
        allWords = readFromFile(filename);
    }

private:
    static std::vector<std::string> readFromFile(const std::string &filename);
};
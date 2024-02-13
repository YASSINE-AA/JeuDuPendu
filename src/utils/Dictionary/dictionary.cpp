#include "dictionary.hpp"

std::vector<std::string> Dictionary::readFromFile(const std::string &filename)
{
    std::ifstream dictFile(filename);
    std::vector<std::string> words;

    if (!dictFile.is_open())
    {
        std::cerr << "Couldn't open file: " << filename << std::endl;
        return {};
    }

    std::string word;
    while (dictFile >> word)
    {
        words.push_back(std::move(word)); // Use move semantics to avoid unnecessary copying
    }

    return words;
}

void Dictionary::deleteFromFile(const std::string &filename, const std::string &wordToDelete)
{
    std::ifstream inputFile(filename);
    if (!inputFile.is_open())
    {
        std::cerr << "Error opening input file." << std::endl;
        return;
    }

    std::ofstream tempFile("temp.txt");
    if (!tempFile.is_open())
    {
        std::cerr << "Error opening temporary file." << std::endl;
        inputFile.close();
        return;
    }

    std::string word;
    bool wordFound = false;

    while (inputFile >> word)
    {
        if (word == wordToDelete)
        {
            wordFound = true;
            continue; // Skip writing the wordToDelete to the temporary file
        }
        tempFile << word << std::endl;
    }

    inputFile.close();
    tempFile.close();

    if (!wordFound)
    {
        std::cerr << "Word not found in the file." << std::endl;
        std::remove("temp.txt");
        return;
    }

    if (std::remove(filename.c_str()) != 0)
    {
        std::cerr << "Error removing original file." << std::endl;
        std::remove("temp.txt");
        return;
    }

    if (std::rename("temp.txt", filename.c_str()) != 0)
    {
        std::cerr << "Error renaming temporary file." << std::endl;
        return;
    }

    std::cout << "Word '" << wordToDelete << "' deleted successfully." << std::endl;
}

bool Dictionary::isWordInFile(const std::string &filename, const std::string &wordToCheck)
{
    std::ifstream inFile(filename);
    std::string word;

    if (!inFile.is_open())
    {
        std::cerr << "Error: Unable to open file " << filename << std::endl;
        return false;
    }

    while (inFile >> word)
    {
        if (word == wordToCheck)
        {
            inFile.close();
            return true;
        }
    }

    inFile.close();
    return false;
}

void Dictionary::addToFile(const std::string &filename, const std::string &wordToAdd)
{
    if (isWordInFile(filename, wordToAdd))
    {
        std::cout << "Word '" << wordToAdd << "' already exists in the file." << std::endl;
        return;
    }

    std::ofstream outFile(filename, std::ios_base::app);
    if (!outFile.is_open())
    {
        std::cerr << "Error: Unable to open file " << filename << std::endl;
        return;
    }

    outFile << wordToAdd << std::endl;
    outFile.close();

    std::cout << "Word '" << wordToAdd << "' added to the file successfully." << std::endl;
}

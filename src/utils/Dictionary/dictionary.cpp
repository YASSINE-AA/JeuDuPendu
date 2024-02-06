#include "dictionary.hpp"
#include <cstdio> // For std::remove and std::rename

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

void Dictionary::deleteFromFile(const std::string &filename, const std::string &wordToDelete)
{
    // Open input file
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

    // Close files
    inputFile.close();
    tempFile.close();

    // Check if the word was found
    if (!wordFound)
    {
        std::cerr << "Word not found in the file." << std::endl;
        std::remove("temp.txt"); // Delete the temporary file
        return;
    }

    // Remove the original file
    if (std::remove(filename.c_str()) != 0)
    {
        std::cerr << "Error removing original file." << std::endl;
        std::remove("temp.txt"); // Delete the temporary file
        return;
    }

    // Rename the temporary file to the original filename
    if (std::rename("temp.txt", filename.c_str()) != 0)
    {
        std::cerr << "Error renaming temporary file." << std::endl;
        return;
    }

    std::cout << "Word '" << wordToDelete << "' deleted successfully." << std::endl;
}
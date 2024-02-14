#include "dictionary.hpp"
#include <cstdlib> // Pour la fonction rand

std::string Dictionary::fileNames[] = {"technologie.txt", "pays.txt", "nature.txt", "metiers.txt", "cuisine.txt"};

std::string Dictionary::generateRandomFilename()
{
    int index = rand() % 5; // Choix aléatoire d'un index de 0 à 4
    return fileNames[index];
}

std::vector<std::string> Dictionary::readFromFile()
{
    std::string filename = generateRandomFilename();
    selectedFile = filename;
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

std::string Dictionary::getTheme()
{
    if (selectedFile.length() > 0)
    {
        std::vector<std::string> tokens;
        std::string intermediate;
        std::stringstream check1(selectedFile);
        while (getline(check1, intermediate, '.'))
        {
            tokens.push_back(intermediate);
        }
        return tokens[0]; // theme.txt -> theme
    }
    else
    {
        // file was not selected.
        return "";
    }
}

void Dictionary::deleteFromFile(const std::string &wordToDelete)
{

    std::ifstream inputFile(selectedFile);
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

    if (std::remove(selectedFile.c_str()) != 0)
    {
        std::cerr << "Error removing original file." << std::endl;
        std::remove("temp.txt");
        return;
    }

    if (std::rename("temp.txt", selectedFile.c_str()) != 0)
    {
        std::cerr << "Error renaming temporary file." << std::endl;
        return;
    }

    std::cout << "Word '" << wordToDelete << "' deleted successfully." << std::endl;
}

bool Dictionary::isWordInFile(const std::string &wordToCheck)
{
    std::ifstream inFile(selectedFile);
    std::string word;

    if (!inFile.is_open())
    {
        std::cerr << "Error: Unable to open file " << selectedFile << std::endl;
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

void Dictionary::addToFile(const std::string &wordToAdd)
{
    if (isWordInFile(wordToAdd))
    {
        std::cout << "Word '" << wordToAdd << "' already exists in the file." << std::endl;
        return;
    }

    std::ofstream outFile(selectedFile, std::ios_base::app);
    if (!outFile.is_open())
    {
        std::cerr << "Error: Unable to open file " << selectedFile << std::endl;
        return;
    }

    outFile << wordToAdd << std::endl;
    outFile.close();

    std::cout << "Word '" << wordToAdd << "' added to the file successfully." << std::endl;
}
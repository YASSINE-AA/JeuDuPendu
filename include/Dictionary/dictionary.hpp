#ifndef DICTIONARY_H
#define DICTIONARY_H

#include <bits/stdc++.h>
#include <iostream>
#include <fstream>
#include <vector>
#include <cstdlib> // Pour la fonction rand

class Dictionary
{
public:
    std::vector<std::string> allWords;

    Dictionary()
    {
        srand(time(nullptr));
        allWords = readFromFile();
    }
    static std::string generateRandomFilename();

    std::vector<std::string> readFromFile();
    void deleteFromFile(const std::string &wordToDelete);
    bool isWordInFile(const std::string &wordToCheck);
    void addToFile(const std::string &wordToAdd);
    std::string getTheme();

private:
    static std::string fileNames[];
    std::string selectedFile;
};

#endif
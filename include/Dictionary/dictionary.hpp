#include <string>
#include <iostream>
#include <vector>
#include <fstream>
#include <cstdlib>

using namespace std;

class Dictionary
{
public:
    vector<string> allWords;
    Dictionary(string filename)
    {
        srand((unsigned)time(NULL));
        allWords = readFromFile(filename);
    }
    string getRandomWord()
    {
        return allWords[rand() % allWords.size()];
    }

private:
    static vector<string> readFromFile(const string &filename);
};
#include <string>
#include <iostream>
#include <vector>
#include <fstream>
#include <cstdlib>
#include <algorithm>

class Dictionary
{
public:
    std::vector<std::string> allWords;
    Dictionary(std::string filename)
    {
        srand((unsigned)time(NULL));
        allWords = readFromFile(filename);
    }
   
   std::string getRandomWord(int minLength, int maxLength, const std::vector<std::string>& visited)
{
    std::srand(static_cast<unsigned int>(time(nullptr)));

    std::vector<std::string> validWords;
    std::copy_if(allWords.begin(), allWords.end(), std::back_inserter(validWords),
                 [visited, minLength, maxLength](const std::string& word) {
                     return ((word.length() >= minLength && word.length() <= maxLength) && std::find(visited.begin(), visited.end(), word) == visited.end());
                 });

    if (validWords.empty()) {
        return "#"; // dictionnary is now empty.
    }

    int randomIndex = std::rand() % validWords.size();
    std::cout << validWords[randomIndex] << std::endl;
    return validWords[randomIndex];
}


private:
    static std::vector<std::string> readFromFile(const std::string &filename);
};
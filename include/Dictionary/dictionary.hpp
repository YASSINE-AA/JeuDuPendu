#include <string>
#include <iostream>
#include <forward_list>
#include <fstream>

using namespace std;

class Dictionary
{
public:
    static forward_list<string> readFromFile(const string &filename);
};
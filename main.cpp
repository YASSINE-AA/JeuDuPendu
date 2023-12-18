#include <iostream>
#include <iomanip>
#include <vector>
#include "utils/BinaryTreeNode/binary_tree_node.hpp"
#include "utils/BinaryTree/binary_tree.hpp"

using namespace std;

void printTree(BinaryTreeNode *root, int space = 0, int count = 5)
{
    if (!root)
        return;

    space += count;

    printTree(root->FD, space, count);

    std::cout << std::setw(space) << root->value << std::endl;

    printTree(root->FG, space, count);
}

int main()
{
    int lettersFound = 0;
    BinaryTree tree = BinaryTree();
    vector<int> testVec;
    BinaryTreeNode *root = nullptr;
    string testDict[114] = {
        "programming",
        "computer",
        "hangman",
        "cplusplus",
        "developer",
        "algorithm",
        "software",
        "engineering",
        "variable",
        "function",
        "language",
        "inheritance",
        "polymorphism",
        "encapsulation",
        "abstraction",
        "iteration",
        "conditional",
        "pointer",
        "reference",
        "constructor",
        "destructor",
        "template",
        "library",
        "compiler",
        "debugging",
        "array",
        "string",
        "vector",
        "stack",
        "queue",
        "linkedlist",
        "tree",
        "graph",
        "recursion",
        "iteration",
        "algorithm",
        "search",
        "sort",
        "bubble",
        "quick",
        "merge",
        "insertion",
        "selection",
        "binary",
        "linear",
        "hash",
        "database",
        "networking",
        "internet",
        "protocol",
        "tcp",
        "udp",
        "http",
        "html",
        "css",
        "javascript",
        "frontend",
        "backend",
        "framework",
        "database",
        "mysql",
        "mongodb",
        "sqlite",
        "postgresql",
        "authentication",
        "authorization",
        "security",
        "encryption",
        "decryption",
        "design",
        "pattern",
        "model",
        "view",
        "controller",
        "mvc",
        "api",
        "rest",
        "soap",
        "testing",
        "unit",
        "integration",
        "system",
        "agile",
        "scrum",
        "kanban",
        "git",
        "repository",
        "commit",
        "branch",
        "merge",
        "conflict",
        "version",
        "control",
        "debugging",
        "profiling",
        "optimization",
        "memory",
        "leak",
        "pointer",
        "reference",
        "memory",
        "allocation",
        "deallocation",
        "virtual",
        "override",
        "interface",
        "lambda",
        "template",
        "function",
        "object",
        "oriented",
        "procedural",
        "imperative",
        "declarative"};

    root = tree.createBinaryTreeFromDict(testDict, 114);
    // testVec = tree.getLetterPosition(root, 's', (string) "ces");
    cout << tree.isWordInTree(root, "object") << endl;

    //printTree(root);
    return 0;
}
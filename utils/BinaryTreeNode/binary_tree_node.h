#ifndef BINARY_TREE_NODE_H
#define BINARY_TREE_NODE_H

class BinaryTreeNode {
    public:
        char value;
        BinaryTreeNode* FG;
        BinaryTreeNode* FD;
        BinaryTreeNode(char value): value(value), FG(nullptr), FD(nullptr) {}
};

#endif
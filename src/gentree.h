#ifndef GENTREE_H
#define GENTREE_H

#include "btree.h"
#include <string>
#include <algorithm>

#define INTERVAL    (100)
#define TAB         "  "

class genTree: public binaryTree<char> {
    private:
    void generateLeaves(std::vector<char>* letters, Node<char>* node);
    void print(const std::string& prefix, const Node<char>*node, bool isLeft);
    void printTreeCode(Node<char>* node, std::string prefix);

    public:
    genTree(): binaryTree<char>('0'){}
    bool generateMinimal(int height, int* amount);
    bool generate(int height, int amount);
    void print();
    void printCode();

};

#endif
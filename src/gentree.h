#ifndef GENTREE_H
#define GENTREE_H

#include "btree.h"

class genTree: public binaryTree<char> {
    private:
    void generateLeaves(std::vector<char>* letters, Node<char>* node);

    public:
    genTree(): binaryTree<char>('0'){}
    bool generateMinimal(int height, int* amount);
    bool generate(int height, int amount);
};

#endif
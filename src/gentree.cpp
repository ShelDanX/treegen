#include "gentree.h"

/*
    Fast power of 2
*/
int fastPow2(int exp) {
    int result = 1;
    int value = 2;
    while (exp > 0) {
        if (exp % 2) result *= value;
        value *= value;
        exp /= 2;
    }
    return result;
}

/*
    Generates minimal tree with given height and returns remained amount of nodes to complete the tree
*/
bool genTree::generateMinimal(int height, int* amount) {
    if (*amount < height) return false;
    for (int i = 0; i < height-1; i++) {
        insertRandNode(i, '0');
    }
    *amount -= height;
    return true;
}

/*
    Generates leaves with values of random althabet letters
*/
void genTree::generateLeaves(std::vector<char>* letters, Node<char>* node) {
    int randIndex;
    if (node->left == nullptr) {
        randIndex = engine() % letters->size();
        node->left = new Node<char>(letters->at(randIndex));
        letters->erase(letters->cbegin()+randIndex);
    }
    else {
        generateLeaves(letters, node->left);
    }

    if (node->right == nullptr) {
        randIndex = engine() % letters->size();
        node->right = new Node<char>(letters->at(randIndex));
        letters->erase(letters->cbegin()+randIndex);
    }
    else {
        generateLeaves(letters, node->right);
    }
}

/*
    Generates the tree with given height and nodes amount. All nodes will have leaves
with values of althabet
*/
bool genTree::generate(int height, int amount) {
    int remain = amount;
    if (amount >= fastPow2(height) || !generateMinimal(height, &remain)){
        return false;
    }    
    while (remain > 0) {
        int randHeight = engine()%(height-2)+1;
        if (insertRandNode(randHeight, '0')) {
            remain--;
        }
    }

    std::vector<char> letters;
    for (int i = 0; i < amount+1; i++) {
        letters.push_back('A'+i);
    }
    generateLeaves(&letters, root);
    return true;
}
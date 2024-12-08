#ifndef BTREE_H
#define BTREE_H

#include <random>
#include <ctime>
#include <vector>
#include <iostream>

template <typename T>
class Node {
public:
    T data;
    Node<T>* left, * right;

    Node(int key) {
        data = key;
        left = nullptr;
        right = nullptr;
    }
};

template <typename T>
class binaryTree {
    private:
    void printPreorder(Node<T>* node) const;

    protected:
    std::mt19937 engine;
    void freeNodeLevelCheck(int height, std::vector<Node<T>*>* v, Node<T>* node, int level = 0);

    public:
    Node<T>* root;
    binaryTree(T value);
    bool insertRandNode(int height, T value);
    void printPreorderFromRoot() const;
};

template <typename T>
binaryTree<T>::binaryTree(T value) {
    root = new Node<T>(value);
    engine.seed(time(nullptr));
}

/*
    Checks tree level for nodes that have free space for childs
*/
template <typename T>
void binaryTree<T>::freeNodeLevelCheck(int height, std::vector<Node<T>*>* v, Node<T>* node, int level) {
    if (level == height) {
        if (node->left == nullptr || node->right == nullptr) v->push_back(node);
    }
    else if (node->left != nullptr) {
        this->freeNodeLevelCheck(height, v, node->left, level+1);
    }
    else if (node->right != nullptr) {
        this->freeNodeLevelCheck(height, v, node->right, level+1);
    }
}

/*
    Inserts random node on next level relative to given
*/
template <typename T>
bool binaryTree<T>::insertRandNode(int height, T value) {
    Node<T>* freeNode;
    Node<T>* newNode = new Node<T>(value);
    std::vector<Node<T>*> v;
    this->freeNodeLevelCheck(height, &v, root);
    if (!v.empty()) {
        freeNode = v.at(engine() % v.size());
        if (freeNode->left == nullptr && freeNode->right == nullptr) {
            if (engine() % 2) freeNode->left = newNode;
            else freeNode->right = newNode;
        }
        else if (freeNode->left == nullptr) freeNode->left = newNode;
        else freeNode->right = newNode;
        return true;
    }
    return false;
}

template <typename T>
void binaryTree<T>::printPreorder(Node<T>* node) const {
    if (node == nullptr)
        return;

    // Deal with the node
    std::cout << node->data << " ";

    // Recur on left subtree
    printPreorder(node->left);

    // Recur on right subtree
    printPreorder(node->right);
}

template <typename T>
void binaryTree<T>::printPreorderFromRoot() const {
    this->printPreorder(root);
}

#endif
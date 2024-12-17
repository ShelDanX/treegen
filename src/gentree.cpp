#include "gentree.h"
#include <fstream>

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
        int randHeight = engine()%(height-1);
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

void genTree::print(const std::string& prefix, const Node<char>* node, bool isLeft) {
    if (node != nullptr) {
        std::cout << prefix;
        std::cout << (isLeft ? "ÃÄÄ" : "ÀÄÄ");
        std::cout << node->data << std::endl;
        print(prefix + (isLeft ? "|   " : "    "), node->left, true);
        print(prefix + (isLeft ? "|   " : "    "), node->right, false);
    }
}

/*
    Prints generated tree
*/
void genTree::print() {
    print("", root, false);
}

void genTree::printTreeCode(Node<char>* node, std::string prefix, char last) {
    std::vector<char> ranges;

    // Left child tree printing
    getLeaves(&ranges, node->left);
    std::cout << prefix << "if (";
    if (ranges.size() > 1) {
        for (int i = 0; i < ranges.size(); i++) {
            if (ranges[i] != last && ranges[i] != 'A')
                std::cout << "(x >= " << ranges[i] << " && x < " << char(ranges[i]+1) << ")";
            else if (ranges[i] == last)
                std::cout << "(x >= " << ranges[i] << ")";
            else 
                std::cout << "(x < B)";
            if (i != ranges.size()-1)
                std::cout << " or ";
        }
        std::cout << ") {" << std::endl;
        printTreeCode(node->left, prefix+TAB, last);
    }
    else {
        if (ranges[0] != last && ranges[0] != 'A')
            std::cout << "x >= " << ranges[0] << " && x < " << char(ranges[0]+1);
        else if (ranges[0] == last)
            std::cout << "x >= " << ranges[0];
        else 
            std::cout << "x < B";
        std::cout << ") {" << std::endl;
        std::cout << prefix+TAB << "cout << x << \" \" << " << ranges[0] << " << endl;" << std::endl;
    }
    std::cout << prefix << "}" << std::endl;

    // Right child tree printing
    ranges.clear();
    getLeaves(&ranges, node->right);
    std::cout << prefix << "else {" << std::endl;
    if (ranges.size() > 1) {
        printTreeCode(node->right, prefix+TAB, last);
    }
    else {
        std::cout << prefix+TAB << "cout << x << \" \" << " << ranges[0] << " << endl;" << std::endl;
    }
    std::cout << prefix << "}" << std::endl;
    
}

void genTree::printCode() {
    std::cout << "#include <iostream>" << std::endl;
    std::cout << "using namespace std;" << std::endl;
    std::cout << "int main(void) {" << std::endl;
    std::cout << "  const int INTERVAL = " << INTERVAL << ";" << std::endl;
    std::vector<char> ranges;
    getLeaves(&ranges);
    std::sort(ranges.begin(), ranges.end());
    for (int i = 1; i < ranges.size(); i++) {
        int space = (100+1+100)/ranges.size();
        std::cout << "  const int " << ranges[i] << " = " << i*space - 100 << ";" << std::endl;
    }
    std::cout << "  for (int x = " << -INTERVAL;
    std::cout << "; x < " << INTERVAL <<  "; x++) {" << std::endl;
    
    printTreeCode(root, "    ", ranges.back());

    std::cout << "  }" << std::endl;
    std::cout << "  return 0;" << std::endl;
    std::cout << "}" << std::endl;
}